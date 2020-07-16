#include "MapGenerator.h"
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <array>
#include <set>

#include "MapTextureGenerator.h"
#include "TileComponent.h"
#include "HexagonalMap.h"
#include "MapValues.h"

#include <iostream>

namespace map {
	//Check if tile is in between tile1 and tile2
	bool isInBetween(ge::Vector2<int> tile, ge::Vector2<int> tile1, ge::Vector2<int> tile2) {
		return (tile1.x + tile2.x) / 2.0 == static_cast<double>(tile.x) && (tile1.y + tile2.y) / 2.0 == static_cast<double>(tile.y);
	}

	//Find the tile in between the two tile. If no tile is in between, return {0, 0}
	ge::Vector2<int> findInBetween(ge::Vector2<int> tile1, ge::Vector2<int> tile2) {
		if ((tile1.x + tile2.x) % 2 == 0 && (tile1.y + tile2.y) % 2 == 0)
			return { (tile1.x + tile2.x) / 2, (tile1.y + tile2.y) / 2 };
		return { 0, 0 };
	}

	MapGenerator::MapGenerator(int mapSize, unsigned int seed) {
		const int nbrOfTile{ 1 + 3 * mapSize * (mapSize - 1) };
		//To respect the correct map size
		mapSize -= 1;

		//Set the seed for the random number generator
		if (seed != 0)
			srand(seed);
		else {
			seed = static_cast<unsigned int>(time(NULL));
			srand(seed);
		}
		this->seed = seed;

		//The tile already placed
		std::set<ge::Vector2<int>> tilePlaced;
		MapStorage storage;

		//Create the corner tile
		for (int i = 0; i <= 2 * mapSize; i += mapSize) {
			for (int j = 0; j <= 2 * mapSize; j += mapSize) {
				if (i + j >= mapSize && i + j <= 3 * mapSize && i != j) {
					createTileFractal({ j, i }, storage, {});
					tilePlaced.insert({ j, i });
				}
			}
		}
		bool didReplaceImportantTile{ false };
		//While the algorithm didn't finish
		while (tilePlaced.size() != nbrOfTile) {
			//The map that will hold every tile that is in between two or more tile and those tiles too
			std::map<ge::Vector2<int>, std::vector<ge::Vector2<int>>> tilesInBetween;
			//For every tile already placed, the algorithm need to find the tile in between those placed
			for (auto it = tilePlaced.begin(); it != tilePlaced.end(); it++) {
				for (auto jt = it; jt != tilePlaced.end(); jt++) {
					ge::Vector2<int> tileInBetween{ findInBetween(*it, *jt) };
					//If it is not both the same tile, that there is a tile in between them that is not already placed
					if (it != jt && tileInBetween != ge::Vector2<int>{0, 0} && tilePlaced.find(tileInBetween) == tilePlaced.end()) {
						//If we already found a couple of tile for this one
						if (tilesInBetween.find(tileInBetween) != tilesInBetween.end()) {
							//Limit the number of average to do 
							//if (tilesInBetween.find(tileInBetween)->second.size() <= mapSize) {
								tilesInBetween.find(tileInBetween)->second.push_back(*it);
								tilesInBetween.find(tileInBetween)->second.push_back(*jt);
							//}
						}
						//Else create the spot
						else {
							tilesInBetween.insert(std::make_pair(tileInBetween, std::vector<ge::Vector2<int>>{ *it, * jt }));
						}
					}
				}
			}
			//Place all the tile found
			for (auto it = tilesInBetween.begin(); it != tilesInBetween.end(); it++) {
				createTileFractal(it->first, storage, it->second);
				tilePlaced.insert(it->first);
			}
			//Delete the important tile
			if (tilePlaced.size() == nbrOfTile && !didReplaceImportantTile) {
				didReplaceImportantTile = true;
				constexpr int deletePrecision{ 8 };
				for (int i = mapSize / deletePrecision; i <= 2 * mapSize; i += mapSize / deletePrecision) {
					for (int j = mapSize / deletePrecision; j <= 2 * mapSize; j += mapSize / deletePrecision) {
						if (i + j > mapSize && i + j < 3 * mapSize) {
							tilePlaced.erase({ j, i });
							storage.deleteTile({ j, i });
						}
					}
				}
			}

			//For every tile
			/*for (int i = 0; i <= 2 * mapSize; i++) {
				for (int j = 0; j <= 2 * mapSize; j++) {
					//If the tile is in the map and was not placed
					if (i + j >= mapSize && i + j <= 3 * mapSize && tilePlaced.find({ j, i }) == tilePlaced.end()) {
						std::vector<ge::Vector2<int>> tileToAverage;
						//For every tile placed
						for (auto it = tilePlaced.begin(); it != tilePlaced.end(); it++) {
							for (auto jt = it; jt != tilePlaced.end(); jt++) {
								//If the two are not the same tile and the tile is in between the two tile
								if (it != jt && isInBetween({ j, i }, (*it), (*jt))) {
									tileToAverage.push_back((*it));
									tileToAverage.push_back((*jt));
								}
							}
						}
						if (tileToAverage.size() >= 2) {
							createTileFractal({ j, i }, storage, tileToAverage);
							tilePlaced.insert({ j, i });
						}
					}
				}
			}*/
		}

		long averageHeight{ 0 };
		int maxHeight{ 0 };
		int minHeight{ 100 };
		for (auto it = tilePlaced.begin(); it != tilePlaced.end(); it++) {
			int height = storage.getTile(*it).height;
			averageHeight += height;
			if (height > maxHeight)
				maxHeight = height;
			if (height < minHeight)
				minHeight = height;
		}
		averageHeight /= static_cast<int>(tilePlaced.size());
		double variance{ 0 };
		for (auto it = tilePlaced.begin(); it != tilePlaced.end(); it++) {
			int height = storage.getTile(*it).height;
			variance += pow(height - averageHeight, 2);
		}

		std::cout << "average : " << averageHeight << ", standard deviation : " << sqrt(variance / tilePlaced.size()) << ", min : " << minHeight << ", max : " << maxHeight << std::endl;
		/*for (int i = 0; i <= 2 * mapSize; i++) {
			for (int j = 0; j <= 2 * mapSize; j++) {
				if (i + j >= mapSize && i + j <= 3 * mapSize)
					createTile({ j, i }, storage);
			}
		}*/
	}

	void MapGenerator::createTile(ge::Vector2<int> position, MapStorage storage) const {
		//Get the neighbors tile
		std::vector<TileComponent*> neighbors{ HexagonalMap{}.getNeighbors(position) };

		//Make statistics
		int averageHeight{ 0 };
		float averageHumidity{ 0 };
		constexpr int nbrOfSum{ 4 };
		for (int i = 0; i != nbrOfSum; i++) {
			//If there is no more neighbor to check
			if (i >= neighbors.size()) {
				int height{ rand() % mv::maxHeight };
				averageHeight += height;
				//If the tile is too high, there isn't water on top of it
				if (height > 2 * mv::maxHeight / 3)
					averageHumidity += rand() % static_cast<int>((mv::maxHumidity - mv::minWaterLevel) * 100) / 100.0f;
				else
					averageHumidity += rand() % static_cast<int>(mv::maxHumidity * 100) / 100.0f;
			}
			else {
				averageHeight += neighbors[i]->height;
				averageHumidity += neighbors[i]->humidity;
			}
		}
		//Create the tile
		TileComponent tile;
		tile.height = averageHeight / nbrOfSum;
		//tile.humidity = averageHumidity / nbrOfSum;
		tile.humidity = 1.5f;
		storage.addTile({ position.x, position.y }, std::move(tile));
	}

	void MapGenerator::createTileFractal(ge::Vector2<int> position, MapStorage storage, const std::vector<ge::Vector2<int>>& tileToAverage) const {
		int averageHeight{ 0 };
		//Make the average of every tile given
		for (int i = 0; i != tileToAverage.size(); i++) {
			averageHeight += storage.getTile(tileToAverage[i]).height;
		}
		//Add one random height
		averageHeight += rand() % mv::maxHeight;

		//Create the tile
		TileComponent tile;
		if (tileToAverage.size() != 0)
			tile.height = averageHeight / (static_cast<int>(tileToAverage.size()) + 1);
		//More dispersion if it is a fist tile
		else {
			if (rand() % 2 == 0)
				tile.height = rand() % (mv::maxHeight / 10);
			else
				tile.height = mv::maxHeight - rand() % (mv::maxHeight / 10);
		}
		tile.humidity = 0.2f;
		storage.addTile(position, std::move(tile));
	}
}

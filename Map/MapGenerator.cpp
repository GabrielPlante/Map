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
#include "Array2D.h"

#include <iostream>
#include "../GameEngine2D/Clock.h"


namespace map {
	//Simple struct for a cube
	template <typename T = int>
	struct Cube {
		T x;
		T y;
		T z;

		//Default constructor
		Cube<T>(T x, T y, T z) : x{ x }, y{ y }, z{ z } {}

		//Construct a cube from an axial coordinate
		Cube<T>(ge::Vector2<T> axial) : x{ axial.x }, z{ axial.y } {
			y = -x - z;
		}

		//Constuct a cube from an axial integer coordinate
		Cube<T>(ge::Vector2<int> axial) : x{ static_cast<T>(axial.x) }, z{ static_cast<T>(axial.y) }{
			y = -x - z;
		}

		//Get the axial coordinate from the cube
		ge::Vector2<T> toAxial() const {
			return ge::Vector2<T>{x, z};
		}

		ge::Vector2<int> toAxialRound() const {
			return ge::Vector2<int>{static_cast<int>(x), static_cast<int>(z)};
		}
	};

	//Lerp from https://www.redblobgames.com/grids/hexagons/#line-drawing
	float lerp(float a, float b, float t) {
		return a + (b - a) * t;
	}

	Cube<float> cubeLerp(Cube<float> a, Cube<float> b, float t) {
		return Cube<float>{lerp(a.x, b.x, t), lerp(a.y, b.y, t), lerp(a.z, b.z, t)};
	}

	std::vector<ge::Vector2<int>> lineDraw(ge::Vector2<int> a, ge::Vector2<int> b) {
		HexagonalMap hexagonMap;
		const int distance{ hexagonMap.distance(a, b) };
		std::vector<ge::Vector2<int>> tileInBetween;
		for (int i = 0; i <= distance; i++) {
			tileInBetween.push_back(cubeLerp(a, b, 1.0f / distance * i).toAxialRound());
		}
		return tileInBetween;
	}

	//Check if tile is in between tile1 and tile2
	bool isInBetween(ge::Vector2<int> tile, ge::Vector2<int> tile1, ge::Vector2<int> tile2) {
		return (tile1.x + tile2.x) / 2.0 == static_cast<double>(tile.x) && (tile1.y + tile2.y) / 2.0 == static_cast<double>(tile.y);
	}

	//Find the tile on the opposite side of this tile from tile1
	ge::Vector2<int> findOtherTile(ge::Vector2<int> tile, ge::Vector2<int> tile1) {
		return { 2 * tile.x - tile1.x, 2 * tile.y - tile1.y };
	}

	//Find the tile in between the two tile. If no tile is in between, return {0, 0}
	ge::Vector2<int> findInBetween(ge::Vector2<int> tile1, ge::Vector2<int> tile2) {
		if ((tile1.x + tile2.x) % 2 == 0 && (tile1.y + tile2.y) % 2 == 0)
			return { (tile1.x + tile2.x) / 2, (tile1.y + tile2.y) / 2 };
		return { 0, 0 };
	}

	MapGenerator::MapGenerator(int mapSize, unsigned int seed) {
		ge::Clock clock;

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
		Array2D tilePlaced;
		MapStorage storage;

		//Create the corner tile
		for (int i = 0; i <= 2 * mapSize; i += mapSize) {
			for (int j = 0; j <= 2 * mapSize; j += mapSize) {
				if (i + j >= mapSize && i + j <= 3 * mapSize) {
					createTileFractal({ j, i }, storage, {});
					tilePlaced.addPosition({ j, i });
				}
			}
		}

		constexpr int maxTileForAverage{ 1 };
		int mapSizeDivider{ 1 };
		while (mapSizeDivider <= mapSize) {
			//Map that hold the tile to avoid that the tile being built depend on the last one built
			std::map<ge::Vector2<int>, std::vector<ge::Vector2<int>>> tileHolder;
			//Parcour every tile on this subdivision
			for (int i = 0; i <= 2 * mapSize; i += mapSize / mapSizeDivider) {
				for (int j = 0; j <= 2 * mapSize; j += mapSize / mapSizeDivider) {
					//If this tile is valid and isn't already placed
					if (i + j >= mapSize && i + j <= 3 * mapSize && !tilePlaced.positionExist({ j, i })) {
						std::vector<ge::Vector2<int>> tileAround;
						std::array<int, 12> directionFound;
						directionFound.fill(0);
						//Find the nearest already placed tile in each direction
						for (int r = 1; (r + i + j >= mapSize && r + i + j <= 3 * mapSize) || (-r + i + j >= mapSize && -r + i + j <= 3 * mapSize); r++) {
							if (directionFound[0] < maxTileForAverage && tilePlaced.positionExist({ r + j, i })) {
								tileAround.push_back({ r + j, i });
								directionFound[0]++;
							}
							if (directionFound[1] < maxTileForAverage && tilePlaced.positionExist({ -r + j, i })) {
								tileAround.push_back({ -r + j, i });
								directionFound[1]++;
							}
							if (directionFound[2] < maxTileForAverage && tilePlaced.positionExist({ j, r + i })){
								tileAround.push_back({ j, r + i });
								directionFound[2]++;
							}
							if (directionFound[3] < maxTileForAverage && tilePlaced.positionExist({ j, -r + i })){
								tileAround.push_back({ j, -r + i });
								directionFound[3]++;
							}
							if (directionFound[4] < maxTileForAverage && tilePlaced.positionExist({ r + j, -r + i })){
								tileAround.push_back({ r + j, -r + i });
								directionFound[4]++;
							}
							if (directionFound[5] < maxTileForAverage && tilePlaced.positionExist({ -r + j, r + i })){
								tileAround.push_back({ -r + j, r + i });
								directionFound[5]++;
							}
							if (directionFound[6] < maxTileForAverage && tilePlaced.positionExist({ r + j, r + i })){
								tileAround.push_back({ r + j, r + i });
								directionFound[6]++;
							}
							if (directionFound[7] < maxTileForAverage && tilePlaced.positionExist({ -r + j, -r + i })){
								tileAround.push_back({ -r + j, -r + i });
								directionFound[7]++;
							}
							if (directionFound[8] < maxTileForAverage && tilePlaced.positionExist({ r + j, -2 * r + i })){
								tileAround.push_back({ r + j, -2 * r + i });
								directionFound[8]++;
							}
							if (directionFound[9] < maxTileForAverage && tilePlaced.positionExist({ -r + j, 2 * r + i })){
								tileAround.push_back({ -r + j, 2 * r + i });
								directionFound[9]++;
							}
							if (directionFound[10] < maxTileForAverage && tilePlaced.positionExist({ -2 * r + j, r + i })){
								tileAround.push_back({ -2 * r + j, r + i });
								directionFound[10]++;
							}
							if (directionFound[11] < maxTileForAverage && tilePlaced.positionExist({ 2 * r + j, -r + i })){
								tileAround.push_back({ 2 * r + j, -r + i });
								directionFound[11]++;
							}
						}
						//For every tile placed
						/*for (auto it = tilePlaced.begin(); !it.end(); it++) {
							//If the tile has an opposite already placed
							if ((mapSizeDivider <= 4 || it.get().distanceSquared(ge::Vector2<int>{ j, i }) <= maxDistanceForImpact) && tilePlaced.positionExist(findOtherTile({ j, i }, it.get()))) {
								tileAround.push_back(it.get());
								tileAround.push_back(findOtherTile({ j, i }, it.get()));
							}
						}*/
						//Add the tile to the holder
						tileHolder.insert(std::make_pair(ge::Vector2<int>{ j, i }, tileAround));
					}
				}
			}
			//Construct all the tile held
			for (auto it = tileHolder.begin(); it != tileHolder.end(); it++) {
				createTileFractal(it->first, storage, it->second);
				tilePlaced.addPosition(it->first);
			}
			//std::cout << mapSizeDivider << std::endl;
			mapSizeDivider *= 2;
		}

		//Create rivers
		HexagonalMap hexagonalMap;
		//Map with the height as the key and 
		std::vector<std::pair<int, ge::Vector2<int>>> localMinTile;
		//Find all the tile that are local minimum
		for (auto it = storage.getBeginningIterator(); !it.endReached(); it++) {
			//Get the neighbors of this tile
			auto neighbors{ hexagonalMap.getNeighbors(it.getPosition()) };
			int lowestNeighbor{ mv::maxHeight };
			//Find the lowest neighbors
			for (int i = 0; i != neighbors.size(); i++) {
				if (neighbors[i]->height < lowestNeighbor)
					lowestNeighbor = neighbors[i]->height;
			}
			//If the lowest neighbor is still higher than this tile
			if (lowestNeighbor > it->height) {
				if (localMinTile.empty()) {
					localMinTile.push_back(std::make_pair(it->height, it.getPosition()));
				}
				else {
					//Add this tile to the list of local minimum, sorted by the height
					for (auto jt = localMinTile.begin(); jt != localMinTile.end();) {
						//If this tile is lower than our tile, insert our tile right before this one
						if (jt->first <= it->height) {
							localMinTile.insert(jt, std::make_pair(it->height, it.getPosition()));
							break;
						}
						jt++;
						//If it is the end of the list, add the tile at the end
						if (jt == localMinTile.end()) {
							localMinTile.push_back(std::make_pair(it->height, it.getPosition()));
							break;
						}
					}
				}
			}
		}

		const int maxDistanceForRiver{ mapSize };

		//For every local minimum, find the closest one (algorithm in O(n^2) with n the number of local minimum, could maybe be optimised by searching around the tile)
		for (int i = 0; i != localMinTile.size(); i++) {
			int closestDistance{ maxDistanceForRiver };
			int closestId{ 0 };
			//Find the closest tile
			for (int j = i + 1; j < localMinTile.size(); j++) {
				if (hexagonalMap.distance(localMinTile[i].second, localMinTile[j].second) < closestDistance) {
					closestDistance = hexagonalMap.distance(localMinTile[i].second, localMinTile[j].second);
					closestId = j;
				}
			}
			//If there is another local minimum near this one, make a river
			if (closestId != 0) {
				std::vector<ge::Vector2<int>> tileInBetween{ lineDraw(localMinTile[closestId].second, localMinTile[i].second) };
				for (int j = 0; j != tileInBetween.size(); j++) {
					//(a-b)*j/total+b
					storage.modifyTile(tileInBetween[j])->height = (localMinTile[i].first - localMinTile[closestId].first) * j / static_cast<int>(tileInBetween.size()) + localMinTile[closestId].first;
				}
			}
		}


		/*HexagonalMap hexagonalMap;
		std::map<ge::Vector2<int>, int> tileToChange;
		//Smooth the terrain by elevating the height of every tile that is below all his neighbors
		for (auto it = storage.getBeginningIterator(); it != storage.getEndIterator(); it++) {
			//Get the neighbors of this tile
			auto neighbors{ hexagonalMap.getNeighbors(it->first) };
			int lowestNeighbor{ mv::maxHeight };
			//Find the lowest neighbors
			for (int i = 0; i != neighbors.size(); i++) {
				if (neighbors[i]->height < lowestNeighbor)
					lowestNeighbor = neighbors[i]->height;
			}
			//If the lowest neighbor is still higher than this tile
			if (lowestNeighbor > it->second.height) {
				//Add this tile to the list of tile to change
				tileToChange.insert(std::make_pair(it->first, lowestNeighbor));
			}
		}
		//Apply change
		for (auto it = tileToChange.begin(); it != tileToChange.end(); it++) {
			storage.modifyTile(it->first)->height = it->second;
		}*/

		//Make statistics
		long averageHeight{ 0 };
		int maxHeight{ 0 };
		int minHeight{ 100 };
		//The average
		for (auto it = tilePlaced.begin(); !it.end(); it++) {
			int height = storage.getTile(it.get()).height;
			averageHeight += height;
			if (height > maxHeight)
				maxHeight = height;
			if (height < minHeight)
				minHeight = height;
		}
		averageHeight /= static_cast<int>(tilePlaced.size());
		double variance{ 0 };
		//The standard deviation
		for (auto it = tilePlaced.begin(); !it.end(); it++) {
			int height = storage.getTile(it.get()).height;
			variance += pow(height - averageHeight, 2);
		}

		std::cout << "Generated map in " << clock.getTime() / 1000 << " milliseconds, spent " << timeInTileCreation / 1000 << " milliseconds creating tile. Statistics: " << std::endl;
		std::cout << "average: " << averageHeight << ", standard deviation: " << sqrt(variance / tilePlaced.size()) << ", min: " << minHeight << ", max: " << maxHeight << std::endl;
		/*for (int i = 0; i <= 2 * mapSize; i++) {
			for (int j = 0; j <= 2 * mapSize; j++) {
				if (i + j >= mapSize && i + j <= 3 * mapSize)
					createTile({ j, i }, storage);
			}
		}*/
	}

	void MapGenerator::createTileFractal(ge::Vector2<int> position, MapStorage storage, const std::vector<ge::Vector2<int>>& tileToAverage) {
		ge::Clock clock;
		//std::cout << tileToAverage.size() << std::endl;
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
		tile.humidity = 1.2f;
		storage.addTile(position, std::move(tile));

		timeInTileCreation += clock.getTime();
	}
}

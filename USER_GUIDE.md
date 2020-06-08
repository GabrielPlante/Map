# Guide utilisateur

Game Balancer est une librairie d'équillibrage automatique de jeux de type_Tower Défense_ en C++. Elle contient le code de bots utilisant un algorithme génétique pour apprendre à jouer à la plupart des _Tower Défense_ ainsi que plusieurs algorithmes d'équillibrage pour les différents paramètres du jeu.  
L'utilisation de cette librairie se fait à travers une instance de la class **BotManager** qui elle utilise une instance de la class **TowerManager** et se fait comme suit:

1. Créer une instance de la class _**TowerManager**_ :
```Cpp
	TowerManager towerManager = new TowerManager(const vector<array<int, 2>>& pathVector,
												const vector<array<int, 2>>& buildableVector,
												const vector<int>& towersRange);
```
| Paramètre | Description	|
| :-----	| :---------	|
| _pathVector_	| le tableau des coordonnées de chaque case du chemin des ennemies `{[x, y], [x, y], ...}`	|
| _buildableVector_	| le tableau des coordonnées de chaque case sur laquelle il est possible de construire une tour `{[x, y], [x, y], ...}`	|
| _towersRange_	| le tableau des portées de chaque type de tour `{rangeTower1, rangeTower2, ...}`	|

2. Créer une instance de la class _**BotManager**_ :
```Cpp
	BotManager botManager = new BotManager(function<bool()> hasWaveEnded,
										function<void()> startNextWave,
										function<bool()> hasGameEnded,
										function<void()> startNextGame,
										function<int()> getMoney,
										function<void(int, array<int, 2>)> placeTower,
										vector<int> towerCost,
										TowerManager towerManager,
										int moneyGap);
```
| Paramètre | Description	|
| :-----	| :---------	|
| _hasWaveEnded_	| fonction sans paramètre qui retourne un booléen _true_ si aucune vague n'est en cours et renvoie _false_ sinon	|
| _startNextWave_	| fonction sans paramètre qui commence une nouvelle vague et ne renvoie rien	|
| _hasGameEnded_	| fonction sans paramètre qui retourne un booléen _true_ si la partie est terminée et renvoie _false_ sinon	|
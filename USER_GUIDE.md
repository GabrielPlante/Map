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
| _buildableVector_	| le tableau des coordonnées de chaque case sur laquelle il est possible de construire une toure `{[x, y], [x, y], ...}`	|
| _towersRange_	| le tableau des portées de chaque type de toure `{rangeTower1, rangeTower2, ...}`	|



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
| _startNextGame_	| fonction sans paramètre qui commence une nouvelle partie et ne renvoie rien	|
| _getMoney_	| fonction sans paramètre qui renvoie un entier de la valeur de l'argent que possède le joueur actuellement	|
| _placeTower_	| fonction qui prend en paramètre un entier représentant l'index du type de la toure à placer et un tableau de deux entiers représentant les coordonnées _x_ et _y_ où placer la tour qui place la toure indiquée 	|
| _towerCost_	| tableau d'entiers représentant le coût de chaque type de toure	|
| _towerManager_	| l'instance de _TowerManager_ crée précédemment	|
| _moneyGap_	| un entier représentant la valeur minimum de gain d'argent (gain de 10 en 10 / de 100 en 100, de 1 en 1, ...)	|



3. Mettre en place l'équilibrage des tours :
```Cpp
	botManager.setupTowerBalancer(fonction<void(int)> buffAttribute,
								fonction<void(int)> nerfAttribute,
								vector<array<int, 2>> desiredTowerUsageRange);
```
| Paramètre | Description	|
| :-----	| :---------	|
| _buffAttribute_	| fonction qui prend en paramètre un entier correspondant à l'index du type de toure dont on veut augmenter la puissance et qui ne renvoie rien	|
| _nerfAttribute_	| fonction qui prend en paramètre un entier correspondant à l'index du type de toure dont on veut diminuer la puissance et qui ne renvoie rien	|
| _desiredTowerUsageRange_	| tableau de tableau de deux entiers correspondant au taux d'utilisation minimum et maximum désiré pour chaque toure `{[tauxMin, tauxMax], [tauxMin, tauxMax], ...}`	|



4. Mettre en place l'équilibrage des vagues :
```Cpp
	botManager.setupWaveBalancer(function<void(int)> buffWave,
								function<void(int)> nerfWave,
								int nbrOfWave);
```
| Paramètre   | Description |
| :---------- | :---------- |
| _buffWave_  | fonction qui prend en paramètre un entier correspondant au numéro de la vague dont on veut augmenter la puissance et qui ne retourne rien |
| _nerfWave_  | fonction qui prend en paramètre un entier correspondant au numéro de la vaque dont on veut diminuer la puissance et qui ne retourne rien |
| _nbrOfWave_ | entier correspondant au nombre de vague par partie |



5. Actualiser périodiquement  
Pour que le système travaille, appeler la fonction `update()` de l'objet _BotManager_ de façon périodique, idéalement à chaque tour le la boucle principale du jeu.
```Cpp
	botManager.update();
```

#### Accès au graphiques

On peut accéder à des graphiques permettant de visualiser les équilibrages réalisés grâce à notre librairie. Pour visualiser les graphiques d'une éxécution spécifique, il faut se placer dans le répertoire **Statistics** et lancer la commande `python statistics_main.py` suivi de plusieurs arguments. Le premier argument est le **file_id** qui permet de choisir une éxécution spécifique. Il précise la date et l'heure de l'éxécution (Exemple de **file_id**: 12-5-2020_8h47m37s). La liste de tous les **file_id** disponibles est visible en lançant la commande `python statistics_main.py` telle quelle sans argument. Les arguments placés après le **file_id** permettent de choisir quels graphiques vont être affichés. On peut en mettre un seul ou plusieurs à la suite. Les arguments disponibles sont : 
| Argument   | Description |
| :---------- | :---------- |
| af  | affiche la fitness moyenne pour chaque génération et chaque apprentissage |
| bf  | affiche la meilleure fitness pour chaque génération et chaque apprentissage |
| wb | affiche l'équilibrage des vagues |
| tb | affiche l'équilibrage des tours |
| tu | affiche le taux d'utilisation des tours |

Exemple : `python statistics_main.py 12-5-2020_8h47m37s af wb`

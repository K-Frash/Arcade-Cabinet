#ifndef __GAME_H__
#define __GAME_H__
#include <string>
#include <map>
#include "entity.h"
#include "animate.h"
#include "inanimate.h"
#include "tile.h"
#include "hero.h"
#include "enemy.h"
#include "neutral.h"
#include "player.h"
#include "window.h"
#include "level.h"
class Level;

class Game {
	std::map<int, Hero> Races; // resource pool id 0
	std::map<int, Enemy> Enemies; // resource pool id 1
	std::map<int, Neutral> Neutrals; // resource pool id 2
	std::map<int, Inanimate> Items; // resource pool id 3
	std::map<char, std::pair<int, int> > resourceMap;
	
	std::vector<Inanimate*> potionProbabilityList;
	std::vector<Inanimate*> goldProbabilityList;
	std::vector<Enemy*> enemyProbabilityList;
	
	
	Player* player;
	Level* level;
	Window* window;
	std::string customFileName;
	bool useCustomLevels;
	int onLevel;
	int maxLevel;
	int state;
	void loadHero(std::string);
	void loadItem(std::string);
	void loadEnemy(std::string);
	void loadNeutral(std::string);
	void createPlayer();
	void loadAssets();
	void advanceLevel();
	void newLevel();
	void start();
	void restart();
	void quit();
	void restartOrQuit();
	void updateScreen();
	
	public:
		Game(char*, bool);
		Game(bool);
		~Game();
	
		bool loop();
		Hero* getPlayer();
		//Entity GetResource(std::string, std::string);
		Entity* getPC();
		Hero* getPCHero();
		Entity* getResource(char);
		
		Entity* getRandomPotion();
		Entity* getRandomGold();
		Entity* getRandomEnemy();
	
};

#endif
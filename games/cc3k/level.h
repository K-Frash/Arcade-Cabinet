#ifndef __LEVEL_H__
#define __LEVEL_H__
#include <string>
#include <vector>
#include "tile.h"
#include "entity.h"
#include "game.h"
class Game;
class Level {
	//vector<Entity> Entities;
	Game* game;
	int turnNumber;
	int numNPC; 
	int numPotions;
	int numGold;
	int rows;
	int columns;
	std::vector<std::vector<Tile*> > tiles;
	std::vector<std::vector<Tile*> > rooms;
	void readFloorPlan(std::string, int);
	void placeEntities();
	Tile* parse(char);
	Entity* getPC();
	void connectTiles();
	void linkDragonHordes();
	void learnRooms();
	public:
		Level(Game*, std::string);
		Level(Game*, std::string, int);
		~Level();
		//void Generate(std::string);
		std::vector<std::vector<Tile*> > reportLevel();
		void takeTurn();
};

#endif
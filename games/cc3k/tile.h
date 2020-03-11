#ifndef __TILE_H__
#define __TILE_H__
#include <string>
#include "entity.h"

class Entity;

class Tile {
	char symbol;
	Entity *e;
	bool collision;
	Tile** neighbours;
	
	public:
		bool visited; //too lazy to write function to set value and read value
		void setSymbol(char);
		char getSymbol();
		bool getCollision();
		void Register(Tile*, int);
		Entity* getEntity();
		void addEntity(Entity*);
		void deleteEntity();
		void removeEntity();
		void takeTurn(int);
		void levelUp();
		Tile** getNeighbours();
		Tile();
		Tile(char, Entity*, bool);
		~Tile();
};

#endif
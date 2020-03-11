#include <map> 
#include <string>
#include "tile.h"
#include "entity.h"
#include "enemy.h"
#include <iostream>
#include <iostream>

// returns the symbol of the thing on the tile or tile's symbol if nothing on it
char Tile::getSymbol() {
	if (e) { 
		return e->getSymbol();
	}

	return symbol;
}

// returns the collision value of the tile and object on it, if either causes collision then collision returns true.
bool Tile::getCollision() {
	if (e) {
		return (e->getCollision() || collision);
	}
	return collision;
}

Tile** Tile::getNeighbours(){
	return neighbours;
}

// used for making tiles observers of each other
void Tile::Register(Tile *t, int i) {
	neighbours[i] = t;
}

Entity* Tile::getEntity() {
	return e;
}

void Tile::addEntity(Entity* e) {
	this->e = e;
	e->setTile(this);
}

void Tile::deleteEntity() {
	delete e;
	e=NULL;
}

void Tile::removeEntity() {
	e=NULL;
}

// tells entity on it to take it's turn
void Tile::takeTurn(int turnNumber) {
	if (e && e->getName()!="PC") {
		e->takeTurn(turnNumber);
	}
}

Tile::Tile() {
		
}

Tile::Tile(char c, Entity *e, bool collision) : symbol(c), e(e), collision(collision), visited(false) {
	if (e){
		e->setTile(this);
	}
	neighbours = new Tile* [9];
}

Tile::~Tile() {
	if (e && e->getName()!="PC"){
		delete e;
	}
	delete [] neighbours;
}

// used for making a tile into a stair tile atm
void Tile::setSymbol(char c) {
	symbol = c;
}
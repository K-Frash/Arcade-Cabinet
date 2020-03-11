#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "level.h"
#include "tile.h"
#include <iostream>
#include "game.h"
#include <map>
#include <stdlib.h>

// refer to numpad for direction correspondence logic

int translateDirections(std::string direction);

Entity* Level::getPC() {
	return game->getPC();
}


// set each tile to be an observer of its neighbours in a 1 tile radius
void Level::connectTiles() {
	for (int r=0; r < rows; r++) {
		for (int c=0; c < columns; c++) {
			tiles[r][c]->Register(tiles[r][c],translateDirections("he")); //itself
			if (r-1 >= 0) { // there is tiles above
				tiles[r][c]->Register(tiles[r-1][c],translateDirections("no"));
				if (c-1 >= 0) { // there is tile to left
					tiles[r][c]->Register(tiles[r-1][c-1],translateDirections("nw"));
				}
				if (c+1 < columns) { // there is tile to the right 
					tiles[r][c]->Register(tiles[r-1][c+1],translateDirections("ne"));
				}
			}
			if (r+1 < rows) { // there is tiles below
				tiles[r][c]->Register(tiles[r+1][c],translateDirections("so"));
				if (c-1 >= 0) { // there is tile to left
					tiles[r][c]->Register(tiles[r+1][c-1],translateDirections("sw"));
				}
				if (c+1 < columns) { // there is tile to the right 
					tiles[r][c]->Register(tiles[r+1][c+1],translateDirections("se"));
				}
			}
			if (c-1 >= 0) { // there is tile to left
				tiles[r][c]->Register(tiles[r][c-1],translateDirections("we"));
			}
			if (c+1 < columns) { // there is tile to the right 
				tiles[r][c]->Register(tiles[r][c+1],translateDirections("ea"));
			}
		}
	}
}

// takes all dragons and make them own the horde next to them
void Level::linkDragonHordes() {
	for(std::vector<std::vector<Tile*> >::iterator it = tiles.begin(); it != tiles.end(); ++it) {
		for(std::vector<Tile*>::iterator it2 = it->begin(); it2!=it->end(); ++it2) {
			Entity* e = (*it2)->getEntity();
			if (e && e->getId()==10) { 
				Tile** neighbourTiles = (*it2)->getNeighbours();
				for (int i=0; i<9; i++) {
					if (neighbourTiles[i]) {					
						Entity* te = neighbourTiles[i]->getEntity();
						if (te && te->getName()=="Dragon") {
							te->setOwnerOf(e);
						}	
					}
				}
			}
		}
	}
}

// translate infile characters to tiles and entities
Tile* Level::parse(char c) {
	if (c==' ' || c=='-' || c=='|') { // collision true tiles
		Tile* tile = new Tile(c, NULL, true);
		return tile;
	}
	else if (c=='#' || c=='+' || c=='.') { // collision false tiles
		Tile* tile = new Tile(c, NULL, false);	
		return tile;
	}
	else if (c=='/') { // collision false tile with next level property
		Tile* tile = new Tile(c, NULL, false);	
		return tile;
	}
	else if (c=='@') { // player
		Entity* player = getPC();
		Tile* tile = new Tile('.', player, false);	
		return tile;
	}
	else if (c=='M' || c=='N' || c=='X' || c=='D' || c=='T' || c=='V' || c=='W' || c=='0' || c=='1' || c=='2' || c=='3' || c=='4' || c=='5' || c=='6' || c=='7' || c=='8' || c=='9') { // some entity
		// this is hard coded for the requirements of the game but if it was just made to check if the character is inside a mapping, then it would work for any additional character
		Entity* e = game->getResource(c);
		Tile* tile = new Tile('.', e, false);
		return tile;
	}
	else {
		Tile* tile = new Tile(c, NULL, false);	
		return tile;	
	}
}

void Level::readFloorPlan(std::string levelBase, int floorNumber) {
	std::fstream levelBaseFile;
	levelBaseFile.open(levelBase.c_str());
	std::string skipLine;
	
	// skip 25 lines for each floor in file that comes before the floor we want if reading custom file
	for (int i=0; i<floorNumber*rows-25; i++) {
		std::getline(levelBaseFile, skipLine);
	}

	char c; 

	for(std::vector<std::vector<Tile*> >::iterator it = tiles.begin(); it != tiles.end(); ++it) { // generate tiles for each line
		for(std::vector<Tile*>::iterator it2 = it->begin(); it2!=it->end(); ++it2) {
			c = levelBaseFile.get();
			while (c=='\n') {
				c = levelBaseFile.get();
			} 
			*it2 = parse(c);
		}
	}
	levelBaseFile.close();
	connectTiles();
	linkDragonHordes();
}

void Level::placeEntities() {
	// place hero first
	int playerRoomNumber = rand()%rooms.size();
	int playerTileNumber = rand()%rooms[playerRoomNumber].size();
	Tile* tile = rooms[playerRoomNumber][playerTileNumber];
	tile->addEntity(getPC());
	rooms[playerRoomNumber].erase(rooms[playerRoomNumber].begin()+playerTileNumber);
	bool needToAdjustForStairs=true;
	if (rooms[playerRoomNumber].size()==0) {
		rooms.erase(rooms.begin()+playerRoomNumber);
		needToAdjustForStairs=false;
	}
	
	// place stairs next, stairs can't be in same room as hero
	int stairRoomNumber = rand()%(rooms.size()-1);
	if (needToAdjustForStairs && stairRoomNumber>=playerRoomNumber) {
		stairRoomNumber += 1;
	}
	int stairTileNumber = rand()%rooms[stairRoomNumber].size();
	tile = rooms[stairRoomNumber][stairTileNumber];
	tile->setSymbol('\\');
	rooms[stairRoomNumber].erase(rooms[stairRoomNumber].begin()+stairTileNumber);
	if (rooms[stairRoomNumber].size()==0) {
		rooms.erase(rooms.begin()+stairRoomNumber);
	}
	
	// place potions 
	for (int i=0; i<numPotions; i++) {
		int potionRoomNumber = rand()%rooms.size();
		int potionTileNumber = rand()%rooms[potionRoomNumber].size();
		tile = rooms[potionRoomNumber][potionTileNumber];
		tile->addEntity(game->getRandomPotion());	
		rooms[potionRoomNumber].erase(rooms[potionRoomNumber].begin()+potionTileNumber);			
		if (rooms[potionRoomNumber].size()==0) {
			rooms.erase(rooms.begin()+potionRoomNumber);
		}	
	}
	
	// place gold
	for (int i=0; i<numGold; i++) {
		int goldRoomNumber = rand()%rooms.size();
		int goldTileNumber = rand()%rooms[goldRoomNumber].size();
		tile = rooms[goldRoomNumber][goldTileNumber];
		tile->addEntity(game->getRandomGold());	
		rooms[goldRoomNumber].erase(rooms[goldRoomNumber].begin()+goldTileNumber);			
		if (rooms[goldRoomNumber].size()==0) {
			rooms.erase(rooms.begin()+goldRoomNumber);
		}	
	}
	
	// place dragons for dragon hordes 
	int numberOfDragons = 0;
	for (std::vector<std::vector<Tile*> >::iterator it = tiles.begin(); it != tiles.end(); ++it) {
		for(std::vector<Tile*>::iterator it2 = it->begin(); it2!=it->end(); ++it2) {
			Entity* e = (*it2)->getEntity();
			if (e && e->getId()==10) { 
				Tile** neighbourTiles = (*it2)->getNeighbours();
				std::vector<Tile*> v; // vector of tiles where a dragon can spawn around the dragon horde
				for (int i=0; i<9; i++) {
					if (neighbourTiles[i] && neighbourTiles[i]->getSymbol()=='.') {
						v.push_back(neighbourTiles[i]);
					}
				}
				if (v.size()>0) { 	// certain placements of dragon gold will mess up dragon placements
									// such as a horde being placed in room with only 1 unoccupied tile.
									// or a dragon placement for one dragon horde took the only place another
									// dragon horde can have it's dragon
					Entity* dragon = game->getResource('D');				
					v[(rand()%v.size())]->addEntity(dragon); // add dragon to the random picked tile
					dragon->setOwnerOf(e);
					numberOfDragons++;
				}
				
			}
		}
	}
	
	// add remaining monsters
	for (int i=0; i<numNPC-numberOfDragons; i++) {
		int enemyRoomNumber = rand()%rooms.size();
		int enemyTileNumber = rand()%rooms[enemyRoomNumber].size();
		tile = rooms[enemyRoomNumber][enemyTileNumber];
		tile->addEntity(game->getRandomEnemy());	
		rooms[enemyRoomNumber].erase(rooms[enemyRoomNumber].begin()+enemyTileNumber);			
		if (rooms[enemyRoomNumber].size()==0) {
			rooms.erase(rooms.begin()+enemyRoomNumber);
		}	
	}
	
}

std::vector<std::vector<Tile*> > Level::reportLevel() {
	return tiles;
}

// tells each of the entity other than player on the level to take its turn starting from top elft to bottom right going left to right then down
void Level::takeTurn() {
	for(std::vector<std::vector<Tile*> >::iterator it = tiles.begin(); it != tiles.end(); ++it) {
		for(std::vector<Tile*>::iterator it2 = it->begin(); it2!=it->end(); ++it2) {
			(*it2)->takeTurn(turnNumber);
		}
	}
	turnNumber++;
}

// learn the tiles associated with each room in the current floor, used for random generation
void Level::learnRooms() {
	for (std::vector<std::vector<Tile*> >::iterator it = tiles.begin(); it != tiles.end(); ++it) {
		for(std::vector<Tile*>::iterator it2 = it->begin(); it2!=it->end(); ++it2) {
			if (!((*it2)->visited) && (*it2)->getSymbol()=='.')  { // next floor tile that hasn't been visited by this method must be part of a new room not yet found
				(*it2)->visited = true;
				rooms.push_back(std::vector<Tile*>(1, *it2));
				int curRoomSize;
				int oldRoomSize = 1;
				do {
					curRoomSize = rooms[rooms.size()-1].size();
					for (int i=oldRoomSize-1; i<curRoomSize; i++) { // keep adding the neighbour of the new tiles added to the room list since neighbours of room floor tiles are part of the room
						Tile* tile = rooms[rooms.size()-1][i];
						tile->visited = true;
						Tile** neighbourTiles = tile->getNeighbours();
						for (int j=0; j<9; j++) {
							if (neighbourTiles[j] && neighbourTiles[j]->getSymbol()=='.' && !(neighbourTiles[j]->visited)){
								neighbourTiles[j]->visited = true;
								rooms[rooms.size()-1].push_back(neighbourTiles[j]);
							}
						}
					}
					oldRoomSize = curRoomSize;
				} while (curRoomSize!=rooms[rooms.size()-1].size()); // if no new neighbours were added in then we found all tiles for the room
			}
		}
	}
}

// random generation ctor
Level::Level(Game* game, std::string fileName): game(game), turnNumber(1), numNPC(20), numPotions(10), numGold(10), rows(25), columns(79), tiles(25, std::vector<Tile*>(79)){
	readFloorPlan(fileName, 1);
	learnRooms();
	placeEntities();
}

// saved file ctor
Level::Level(Game* game, std::string fileName,int floorNumber): game(game), turnNumber(1), numNPC(20), numPotions(10), numGold(10), rows(25), columns(79), tiles(25, std::vector<Tile*>(79)){
	readFloorPlan(fileName, floorNumber);
}

Level::~Level() {
	// have to delete the tiles in the vector since tile pointers
	for(std::vector<std::vector<Tile*> >::iterator it = tiles.begin(); it != tiles.end(); ++it) {
		for(std::vector<Tile*>::iterator it2 = it->begin(); it2!=it->end(); ++it2) {
			delete *it2;
		}
	}
}
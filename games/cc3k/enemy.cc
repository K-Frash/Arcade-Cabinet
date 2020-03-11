#include "enemy.h"
#include <stdlib.h>
#include <iostream>

Enemy::Enemy(): Animate() {
	// this should never be called by own code but is required for map to work
}

Enemy::Enemy(int hp, int atk, int def, bool collision, bool attackable, bool consumable, bool takable, int id, std::string name, bool mystery, char symbol, bool hostility, bool moveable, bool negateHarmfulEffects, int gold): Animate(hp, atk, def, collision, attackable, consumable, takable, id, name, mystery, symbol, hostility, moveable, negateHarmfulEffects, gold) {
	// ctor for creation from text file input
}

Enemy::Enemy(const Enemy& other): Animate(other) {
	// copy master object for use
}

Enemy::~Enemy() {
	// dtor
}

void Enemy::takeTurn(int turnNumber){ // decision making for an enemy taking a turn
	if (turnNumber==lastMovedTurn) { // ensure it hasn't already moved this turn
		return;
	}
	lastMovedTurn = turnNumber;

	// check for player to attack if hostile
	Tile** neighbourTiles = tile->getNeighbours();
	if (getHostility()) {
		for (int i=0; i<9; i++) {
			Entity* e = neighbourTiles[i]->getEntity();
			if (e && e->getName() == "PC") {
				//attack the pc and end turn
				Animate* pc = dynamic_cast<Animate*>(e);
				pc->Defend(this);
				
				return;
			}
		}	
	}

	// move
	if (getMoveable()) {
		int possibleMoves[9];
		int numPossibleMoves = 0;
		for (int i=0; i<9; i++) { // get list of tiles it can move to
			if (neighbourTiles[i]->getSymbol()=='.')  {
				possibleMoves[numPossibleMoves] = i;
				numPossibleMoves++;
			}
		}
		if (numPossibleMoves>0) { // pick on at random if there is a possible move, else it doesn't move
			Tile* t = neighbourTiles[possibleMoves[rand()%numPossibleMoves]];
			tile->removeEntity();
			t->addEntity(this);
		}	
	}
	
}

bool Enemy::getHostility() {
	if (hostility) { // if hostile return hostile
		return hostility;
	}
	if (ownedEntity) { // if not hostile but player is near an object it owns, return hostile (for the dragon)
		Tile** neighbourTiles = ownedEntity->getTile()->getNeighbours(); // neighbours of the tile the object owned is on
		for (int i=0; i<9; i++) {
			Entity* e = neighbourTiles[i]->getEntity();
			if (e && e->getName() == "PC") { // checking among those objects that a player is there
				//attack the pc and end turn
				return true;
			}
		}	
	}
	return false;
}
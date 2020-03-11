#include "hero.h"
#include <string>
#include <iostream>
#include <sstream>
#include <math.h>
#include <stdlib.h>
#include "entity.h"
#include "animate.h"
#include "inanimate.h"
int translateDirections(std::string direction);

Hero::Hero() {
	
}

Hero::Hero(int hp, int atk, int def, bool collision, bool attackable, bool consumable, bool takable, int id, std::string name, bool mystery, char symbol, bool hostility, bool moveable, float goldMultiplier, float scoreMultiplier, bool negateHarmfulPotions, std::string race): Animate(hp, atk, def, collision, attackable, consumable, takable, id, name, mystery, symbol, hostility, moveable, negateHarmfulPotions, 0/*gold*/), goldMultiplier(goldMultiplier), scoreMultiplier(scoreMultiplier), race(race), onStairs(false), action("PC has spawned.") {
}

Hero::Hero(const Hero& other):  Animate(other), goldMultiplier(other.goldMultiplier), scoreMultiplier(other.scoreMultiplier), race(other.race), onStairs(other.onStairs), action(other.action) {
}

Hero::~Hero() {
	
}


// check if item with mystery flag true is known to hero
bool Hero::itemIsLearned(Entity* e) {
	for (std::vector<std::string>::iterator it = learnedItems.begin(); it!=learnedItems.end(); ++it) {
		if ((*it)==e->getName()) {
			return true;
		}
	}
	return false;
}

// checks to see if there are potions around it and reports what it sees
void Hero::checkSurroundings() {
	Tile** neighbourTiles = tile->getNeighbours();
	for (int i=0; i<9; i++) {
		Entity* e = neighbourTiles[i]->getEntity();
		if (e && e->getMystery()) {
			action += " and sees ";
			if (itemIsLearned(e)) {
					action += "a " + e->getName() + " potion";
			}
			else {
				action += "an unknown potion";
			}
		}
		
	}
}

// more details about Move, attack, defend, consume is found in animate.cc
// there are overrides with additional instructions in them for player action recording 

void Hero::Move(std::string direction) {
	action = "PC attempts to move " + direction + ".";
	Tile** neighbourTiles = tile->getNeighbours();
	if (neighbourTiles[translateDirections(direction)]) { // checking if a tile exists in that direction
		if (!neighbourTiles[translateDirections(direction)]->getCollision()){
		// they don't cause a collision
			tile->removeEntity();	
			Entity* otherTileEntity = neighbourTiles[translateDirections(direction)]->getEntity();
			if (otherTileEntity) { // picks up gold if it is walking to a tile with gold on it
				pickupGold(otherTileEntity);
			} 
			if (neighbourTiles[translateDirections(direction)]->getSymbol()=='\\') { // player is walking to stairs
				onStairs = true;
				action = "PC moves " + direction + " and advances down the stairs.";
			}
			else { // player is walking anywhere else
 				neighbourTiles[translateDirections(direction)]->addEntity(this);		
				action = "PC moves " + direction;
				checkSurroundings();
				action += ". ";
			}
		}
	}
}

void Hero::Attack(std::string direction) {
	action = "";
	Tile** neighbourTiles = tile->getNeighbours();
	if (neighbourTiles[translateDirections(direction)]) { // checking if a tile exists in that direction
		Entity* other = neighbourTiles[translateDirections(direction)]->getEntity();
		if (other && other->getAttackable()){
			Animate* aOther;
			aOther = dynamic_cast<Animate*>(other);
			int eHp = aOther->getHp();
			int damage = aOther->Defend(this);
			eHp = damage>eHp ? 0 : eHp-damage;
			std::stringstream ss;
			ss << "PC deals " << damage << " damage to " << aOther->getSymbol() << "(" << eHp << " HP). ";
			std::getline(ss, action);
		}
	}
}

int Hero::Defend(Animate* other){
	int damage = (int)ceil((100.0/(100+getDef()))*other->getAttack());
	if (rand()%2==0) { //attacks against PC miss half the time
		damage = 0;
	}
	hp -= damage;
	if (hp<=0) {
		Die(other);
	}
	std::stringstream ss;
	ss << other->getSymbol() << " deals " << damage << " to PC. ";
	std::string s;
	std::getline(ss, s);
	action += s;
	return damage;
}

void Hero::learnItem(Entity* mysteryItem) {
	learnedItems.push_back(mysteryItem->getName());
}

void Hero::Consume(std::string direction) {
	action = "";
	Tile** neighbourTiles = tile->getNeighbours();
	if (neighbourTiles[translateDirections(direction)]) { // checking if a tile exists in that direction
		Entity* other = neighbourTiles[translateDirections(direction)]->getEntity();
		if (other && other->getConsumable()){
			learnItem(other);
			Inanimate* iOther;
			iOther = dynamic_cast<Inanimate*>(other);
			addBAtk(iOther->getAttack());
			addBDef(iOther->getDef());
			addBHp(iOther->getHp());
			iOther->Consumed(this);
			action = "PC uses " + iOther->getName();
		}
	}
}

void Hero::takeTurn(int turnNumber){
	// not relevant to the turn taking style of cc3k
}

std::string Hero::getRace() {
	return race;
}

int Hero::getGold() {
	return (int)(goldMultiplier * gold); 
}

void Hero::Die(Animate* other) {
}

bool Hero::isOnStairs() {
	return onStairs;
}

void Hero::getOffStairs() {
	onStairs = false;
}

std::string Hero::getAction() {
	return action;
}

int Hero::getScore() { // for human this would be 50% more than the gold they have
	return (int)getGold() * goldMultiplier;
}

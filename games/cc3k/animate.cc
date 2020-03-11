#include <string>
#include <map>
#include "entity.h"
#include "animate.h"
#include "inanimate.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>

// refer to numpad for direction correspondence logic
int translateDirections(std::string direction) {
	std::map<std::string,int> directionMap;
	directionMap["no"]=8;
	directionMap["so"]=2;
	directionMap["we"]=4;
	directionMap["ea"]=6;
	directionMap["nw"]=7;
	directionMap["ne"]=9;
	directionMap["sw"]=1;
	directionMap["se"]=3;
	directionMap["he"]=5; // square entity is on
	return directionMap[direction]-1; // -1 for array offset starting at 0
}

// get the other entie's gold value and added to itself 
void Animate::pickupGold(Entity* other) {
	gold += other->getGold();
	delete other;
}

// take a string for direction of movement and moves there if possible
void Animate::Move(std::string direction) {
	Tile** neighbourTiles = tile->getNeighbours();
	if (neighbourTiles[translateDirections(direction)]) { // checking if a tile exists in that direction
		if (!neighbourTiles[translateDirections(direction)]->getCollision()){
		// they don't cause a collision
			tile->removeEntity();	
			Entity* otherTileEntity = neighbourTiles[translateDirections(direction)]->getEntity();
			if (otherTileEntity) {
				// pick up gold on the target destination
				pickupGold(otherTileEntity);
			} 
			neighbourTiles[translateDirections(direction)]->addEntity(this);
		}
	}
}

// take a string for direction of attack and attacks attackable entity in that direction
void Animate::Attack(std::string direction) {
	Tile** neighbourTiles = tile->getNeighbours();
	if (neighbourTiles[translateDirections(direction)]) { // checking if a tile exists in that direction
		Entity* other = neighbourTiles[translateDirections(direction)]->getEntity();
		if (other && other->getAttackable()){ // if entity exists and is attackable
			Animate* aOther;
			aOther = dynamic_cast<Animate*>(other); // if it is attackable then it is animate for sure, this could be avoided as mentioned in the design documents 
			aOther->Defend(this);
		}
	}
}

// gain the gold of the other entity without destroying it
void Animate::takeGold(Entity* other) {
	gold += other->getGold();
}

// method that is called when an animate's hp reaches 0 by combat (no other death is possible in cc3k)
void Animate::Die(Animate* killer) {
	if (ownedEntity) { // drgaons make their horde's collision off so player can walk over it and pick it up
		ownedEntity->turnOffCollision();
	}
	killer->takeGold(this);
	tile->deleteEntity();
}

void Animate::setHostile() {
	hostility = true;
}

int Animate::Defend(Animate* other) {
	setHostile(); // dragons become hostile if attacked regardless of standing next to gold anymore
	int damage = (int)ceil((100.0/(100+getDef()))*other->getAttack());
	hp -= damage;
	if (hp<=0) { // condition for death of defender
		Die(other);
	}
	return damage;
}

void Animate::addBAtk(int bonus) { 
	if (bonus>0 || negateHarmfulEffects) { // elf style harmful negation
		bonusPAtk += abs(bonus);
	}
	else {
		bonusNAtk += bonus;
	}
}

void Animate::addBDef(int bonus) {
	if (bonus>0 || negateHarmfulEffects) {  // elf style harmful negation
		bonusPDef += abs(bonus);
	}
	else {
		bonusNDef += bonus;
	}
}

void Animate::addBHp(int bonus) {
	if (negateHarmfulEffects) {  // elf style harmful negation
		bonus = abs(bonus);
	}
	if (getHp()+bonus<0) {
		hp = 1;
	}
	else if (getHp()+bonus>maxHp) {  // elf style harmful negation
		hp = maxHp;
	}
	else {
		hp += bonus;
	}
}

// takes in a direction and consumes a consuamble in that direction if it exists
void Animate::Consume(std::string direction) {
	Tile** neighbourTiles = tile->getNeighbours();
	if (neighbourTiles[translateDirections(direction)]) { // checking if a tile exists in that direction
		Entity* other = neighbourTiles[translateDirections(direction)]->getEntity();
		if (other && other->getConsumable()){ // object exists and is consumable
			Inanimate* iOther;
			iOther = dynamic_cast<Inanimate*>(other); // if it is consumable it is inanimate
			addBAtk(iOther->getAttack()); // add bonuses
			addBDef(iOther->getDef()); // add bonuses
			addBHp(iOther->getHp()); // add bonuses
			iOther->Consumed(this);
		}
	}
}

Animate::Animate(): Entity() {
	// should never be by own code but requried for vector and map
}

Animate::Animate(int hp, int atk, int def, bool collision, bool attackable, bool consumable, bool takable, int id, std::string name, bool mystery, char symbol, bool hostility, bool moveable, bool negateHarmfulEffects, int gold): Entity(hp, atk, def, collision, attackable, consumable, takable, id, name, mystery, symbol, hostility, moveable, gold), negateHarmfulEffects(negateHarmfulEffects) {
	// used to generate from txt file
}

Animate::Animate(const Animate& other): Entity(other), negateHarmfulEffects(other.negateHarmfulEffects) {
	// copies we make from masters
}

Animate::~Animate() {
	// dtor
}
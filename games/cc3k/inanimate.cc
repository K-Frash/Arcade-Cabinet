#include "entity.h"
#include "inanimate.h"
#include <iostream>
#include "tile.h"
Inanimate::Inanimate(): Entity() {
	
}

Inanimate::Inanimate(int hp, int atk, int def, bool collision, bool attackable, bool consumable, bool takable, int id, std::string name, bool mystery, char symbol, bool hostility, bool moveable, int gold): Entity(hp, atk, def, collision, attackable, consumable, takable, id, name, mystery, symbol, hostility, moveable, gold) {
}

Inanimate::Inanimate(const Inanimate& other): Entity(other) {
} 

Inanimate::~Inanimate() {

}

void Inanimate::takeTurn(int turnNumber) {
	// w/e needs to happen to this entity when its t urn is called
	// could be used for things like expiration of temporary objects
	// or objects that change state after a certain amount of time (rotting food)
}

void Inanimate::Consumed(Animate*) { // I thought something more special would occur, guess not
	tile->deleteEntity();
}

int Inanimate::getHp() {
	return hp;
}

int Inanimate::getAttack() {
	return atk;
}

int Inanimate::getDef() {
	return def;
}
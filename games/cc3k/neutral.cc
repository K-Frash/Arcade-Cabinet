#include "neutral.h"
#include "enemy.h"
#include "inanimate.h"
#include <iostream>
Neutral::Neutral() {
}

Neutral::Neutral(int hp, int atk, int def, bool collision, bool attackable, bool consumable, bool takable, int id, std::string name, bool mystery, char symbol, bool hostility, bool moveable, bool negateHarmfulEffects, int gold, Inanimate* treasure): Enemy(hp, atk, def, collision, attackable, consumable, takable, id, name, mystery, symbol, hostility, moveable, negateHarmfulEffects, gold) {
	masterCopy = true;
	globalHostility = new bool;
	*globalHostility = hostility;
	this->treasure = treasure;
}
Neutral::Neutral(const Neutral& other): Enemy(other) {
	treasure = other.treasure;
	globalHostility = other.globalHostility;
	masterCopy = false;
}
Neutral::~Neutral() {
	// WARNING! must call freeSharedResources() when deleting the last Neutral of its kind. copies of an object don't need to, but one of them or the original must call it or you leak memory
}
bool Neutral::getHostility() {
	return *globalHostility;
}

void Neutral::setHostile() {
	*globalHostility = true;
}

void Neutral::freeSharedResources() { // required since map.insert() will call dtor
	delete globalHostility;
	delete treasure;

}

void Neutral::Die(Animate* killer) {
	// drops a copy of the treasure it was holding on to
	Entity* e = new Inanimate(*treasure);
	tile->deleteEntity();
	tile->addEntity(e);
}

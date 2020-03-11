#include <string>
#include "entity.h"
#include <iostream>
Entity::Entity() {
	
}

Entity::Entity(int hp, int atk, int def, bool collision, bool attackable, bool consumable, bool takable, int id, std::string name, bool mystery, char symbol, bool hostility, bool moveable, int gold): hp(hp), maxHp(hp), atk(atk), def(def), collision(collision), attackable(attackable), consumable(consumable), takable(takable), id(id), name(name), mystery(mystery), symbol(symbol), hostility(hostility), moveable(moveable), gold(gold) {
	bonusPAtk = bonusNAtk = bonusPDef = bonusNDef = 0;
}

Entity::Entity(const Entity& other): hp(other.hp), maxHp(other.maxHp), atk(other.atk), def(other.def), collision(other.collision), attackable(other.attackable), consumable(other.consumable), takable(other.takable), id(other.id), name(other.name), mystery(other.mystery), symbol(other.symbol), hostility(other.hostility), moveable(other.moveable), gold(other.gold) {
	bonusPAtk = bonusNAtk = bonusPDef = bonusNDef = 0;
}

Entity::~Entity() {
	
}

bool Entity::getHostility() {
	return hostility;
}

int Entity::getHp() {
	return hp;
}

int Entity::getAttack() {
	int i = atk+bonusPAtk+bonusNAtk; 
	if (i<0) {
		return 0;
	}
	return i;
}

int Entity::getDef() {	

	int i = def+bonusPDef+bonusNDef;
	if (i<0) {
		return 0;
	}
	return i;
}

bool Entity::getMoveable() {
	return moveable;
}

bool Entity::getCollision() {
	return collision;
}

bool Entity::getAttackable() {
	return attackable;
}

bool Entity::getConsumable() {
	return consumable;
}

bool Entity::getTakable() {
	return takable;
}

int Entity::getId() {
	return id;
}

bool Entity::getMystery() {
	return mystery;
}

std::string Entity::getName() {
	return name;
}

char Entity::getSymbol() {
	return symbol;
}

void Entity::setTile(Tile* t) {
	tile = t;
}

Tile* Entity::getTile() {
	return tile;
}

int Entity::getGold() {
	return gold;
}

void Entity::setOwnerOf(Entity* e) { // for the dragon to own a dragon horde
	ownedEntity = e;
}

void Entity::turnOffCollision() {
	collision = false;
}

void Entity::resetBonuses() {
	bonusPAtk = bonusNAtk = bonusPDef = bonusNDef = 0;
}
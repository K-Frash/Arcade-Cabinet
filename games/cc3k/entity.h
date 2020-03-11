#ifndef __ENTITY_H__
#define __ENTITY_H__
#include <string>
#include "tile.h"

class Tile;

class Entity {
	bool collision;
	bool attackable;
	bool consumable;
	bool takable;
	int id;
	bool mystery;
	char symbol;
	
	protected:
	
		Entity* ownedEntity;
		int gold;	
		int maxHp;
		int bonusPAtk;
		int bonusNAtk;
		int bonusPDef;
		int bonusNDef;
		std::string name;
		int hp;
		int atk;
		int def;
		bool hostility;
		bool moveable;
		Tile* tile;
		
	public:
		Entity();
		Entity(int, int, int, bool, bool, bool, bool, int, std::string, bool, char, bool, bool, int);
		Entity(const Entity&);
		~Entity();
		virtual int getHp();
		virtual int getAttack();
		virtual int getDef();
		virtual bool getHostility();
		int getId();
		bool getCollision();
		bool getAttackable();
		bool getConsumable();
		bool getTakable();
		bool getMystery();
		std::string getName();
		char getSymbol();
		Tile* getTile();
		void setTile(Tile*);
		bool getMoveable();
		virtual int getGold();
		virtual void takeTurn(int)=0;
		void setOwnerOf(Entity*);
		void turnOffCollision();
		void resetBonuses();

};

#endif
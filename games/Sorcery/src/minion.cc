#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <string>
#include "CType.h"
#include "AType.h"
#include "minion.h"
#include "card.h"
using namespace std; // remove this if you want im lazy to use std::

// Ctors, Dtors
Minion::Minion(const CardBase &base, Ability &ability): Card{base}, ability{ability},
  attack{base.attack}, health{base.defence}, currhp{base.defence}, moved{false} { 
}

Minion::Minion(Minion &&other): Card{move(other)}, ability{other.ability},
    attack{base.attack}, health{other.health}, currhp{other.currhp}, moved{other.moved} { }

Minion::~Minion(){}

std::unique_ptr<Card> Minion::copy() const{
    return std::make_unique<Minion>(base,ability);//using new for now
}
// Getters
int Minion::getAtt()const{return attack;}
int Minion::getHp() const{return health;}
int Minion::getCurr()const{return currhp;}
bool Minion::getMove()const{return moved;}

bool Minion::isEnchanted() const { return false; }

//inquiry
const CardInquiry Minion::inquiry() const{
    return CardInquiry{base.name, base.desc, CType::Minion, cost, attack, currhp, AType::None };
};

//Setters

void Minion::setAtt(int n){attack = n;}
void Minion::setHp(int n){health = n;} // TODO Why is this mutable??
void Minion::setCurr(int n){currhp = n;}
void Minion::setMove(bool b){moved = b;}

void Minion::reset(){
	setCurr(getHp());
}

unique_ptr<Minion> &Minion::disenchant(){
	throw Minion::MinionNotEnchanted{};
}

unique_ptr<Minion> &Minion::getBaseMinion(){
	throw "Shouldn't be calling getBaseMinion on a base minion!";
}

//Minion Functions:

//P.V. from Card.h:
const CType Minion::getType() const {return CType::Minion;}

void Minion::prettyprint(){
	cout << "Minion: " << base.name;
	cout << ", cost: " << cost;
	cout << ", attack: " << attack;
	cout << ", health: " << health; //is it hp or def?
	cout << endl;
}

void Minion::attackMinion(Minion &m){ //TODO change to Game type
	m.setCurr(m.getCurr() - this->getAtt());
	this->setCurr(this->getCurr() - m.getAtt());
	//TODO minion death check
}

Ability &Minion::getAbility() {
	return ability;
}

/*ostream& operator<<(ostream &o, const Minion &m){
	// Real Cards Body will be utilized to print these cards.
	// This is purely for testing as of the moment!
	if( m.getAb() ){
		o << "--------------------" << endl;
		o << m.getName() << endl;
		o << m.getAtt() << endl;
		o << m.getDef() << endl;
		o << m.getDm() << endl;
		o << "has ability enum" << endl;
		o << "--------------------" << endl;
	}
	else{
		o << "--------------------" << endl;
		o << m.getName() << endl;
		o << m.getAtt() << endl;
		o << m.getDef() << endl;
		o << m.getDm() << endl;
		o << "no ability" << endl;
		o << "--------------------" << endl;
	}
}*/

/*
void Minion::EnchantedMinion(){
	
}

void Minion::Disenchant(){
}
*/
/*
// Ctor based upon handing in a card with a name!
Minion::Minion(string desc){
	istringstream iss{desc};
	string s;
	int n;

	iss>>s; //Skips 'MINION' in card reader

	// Temporary method to read and set a card. Allows for versatile implementation
	// (however a tad crude as of right now, refer to test_minion to see how
	// cards are currently being read in)
	for(int i = 1 ; i < 5 ; ++i){
		if( i == 1 ){
			iss>>s;
			this->setName(s);
		}
		else if( i == 2 ){
			iss>>n;
			this->setAtt(n);
		}
		else if( i == 3){
			iss>>n;
			this->setDef(n);
			this->setDm(n);
		}
		else if( i == 4){
			iss>>s;
			this->setAb(!(s == "d"));
		}
	}
}*/

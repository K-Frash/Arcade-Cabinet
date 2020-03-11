#include <iostream>
#include "enchantment.h"
#include "card.h"
#include "minion.h"
#include "CType.h"

using namespace std;

/*
Enchantment IDs:
eID = 1 : Giant Strength
eID = 2 : Silence
*/

template <typename Derived, typename Base>
std::unique_ptr<Derived> static_unique_ptr_cast(std::unique_ptr<Base> &&ptr) {
	return std::unique_ptr<Derived>(static_cast<Derived*>(ptr.release()));
}

Enchantment::Enchantment(const CardBase &base, Ability &ability): Minion{base,ability} {}  

Enchantment::~Enchantment(){} //shared ptrs dont need to be deallocated!

Enchantment::Enchantment(Enchantment &&other): Minion{move(other)}, basem{move(other.basem)}{}

std::unique_ptr<Card> Enchantment::copy() const{
    auto out = make_unique<Enchantment>(base,ability);
    if (basem){
        out->basem = static_unique_ptr_cast<Minion, Card>(basem->copy()); 
    }
    return std::move(out);//using new for now
}
// Getters
int Enchantment::getAtt() const{
    return (basem.get() == nullptr) ? base.attack: basem->getAtt();
}

int Enchantment::getHp() const{
    return (basem.get() == nullptr) ? health: basem->getHp();
}

int Enchantment::getCost() const{
    return (basem.get() == nullptr) ? cost: basem->getCost();
}

int Enchantment::getCurr() const{return currhp;}
bool Enchantment::getMove() const {return moved;}

bool Enchantment::isEnchanted() const {
	return true;
}

std::unique_ptr<Minion> &Enchantment::disenchant(){
	return basem;
}

std::unique_ptr<Minion> &Enchantment::getBaseMinion(){
	if (!basem->isEnchanted()){
		return basem;
	} else {
		return basem->getBaseMinion();
	}
}

//inquiry
const CardInquiry Enchantment::inquiry() const{
    return CardInquiry{getName(), getDesc(), getType(), getCost(), getAtt(), getHp(), AType::None,
            0, basem.get()};
};

const CardInquiry Enchantment::inquiryBase() const{
    return CardInquiry{base.name, base.desc, CType::Enchantment, base.cost, base.attack, base.defence, AType::None,
            0, basem.get()};
};
// Setters
void Enchantment::setAtt(int n){
	if(eID == 1) basem->setAtt(attack+1);
	else basem->setAtt(attack);
}

void Enchantment::setHp(int n){
	if(eID == 1) basem->setHp(health+1);
	else basem->setHp(health);
}

bool Enchantment::cast(std::unique_ptr<Minion> &min, Player &player, Game &game){
    basem = move(min);
    min = unique_ptr<Minion>(this);
    return true;
}

const std::string &Enchantment::getName() const{
    return (basem.get() == nullptr) ? base.name: basem->getName();
}

const std::string &Enchantment::getDesc() const{ //TODO: figure out proper description
    if (!base.desc.empty()) return base.desc;
    return (basem.get() == nullptr) ? base.desc: basem->getDesc();
}

void Enchantment::setCurr(int n){basem->setCurr(currhp);}
void Enchantment::setMove(bool b){basem->setMove(moved);}

// P.V. functions:

const CType Enchantment::getType() const{
    if (basem.get() == nullptr){
        return CType::Enchantment;
    }else{
        return basem->getType();
    }
}

void Enchantment::prettyprint(){
	cout << "Enchantment: " << base.name;
	cout << ", cost: " << cost;
	cout << ", attack: " << attack;
	cout << ", health: " << health;
	cout << "Description: " << base.desc;
	cout << endl;
}

#include "card.h"
#include "player.h"
#include <memory>
#include <string>

using std::string;


Card::Card(const CardBase &base): base{base},  cost{base.cost} {}

Card::~Card(){
    
}

Card::Card(Card &&other): base{other.base}{
    
}

// __        ___    ____  _   _ ___ _   _  ____ 
// \ \      / / \  |  _ \| \ | |_ _| \ | |/ ___|
//  \ \ /\ / / _ \ | |_) |  \| || ||  \| | |  _ 
//   \ V  V / ___ \|  _ <| |\  || || |\  | |_| |
//    \_/\_/_/   \_\_| \_\_| \_|___|_| \_|\____|
// FIXME(WARNING): You must *TRUE* if the in cast if
// if the ownership changes. Also must throw if error
bool Card::cast(std::unique_ptr<Minion> &min, Player &player, Game &game) {
    throw CardCannotCastOnTarget{*this, *min};
    return false;
}

bool Card::cast(std::unique_ptr<Ritual> &ritual, Player &player, Game &game) {
    throw CardCannotCastOnTarget{*this, *ritual};
    return false;
}

bool Card::cast(Game &game) {
    throw CardCannotCast{*this};
    return false;
}

Card& Card::operator=(const Card &){
   return *this; 
}
Card& Card::operator=(Card &&){
   return *this; 
}

bool Card::requires_target(){
    return false;
}

//Getters
const string &Card::getName() const{return base.name;}
const string &Card::getDesc() const{return base.desc;}
int Card::getCost() const{return cost;}
int Card::getMaster() const{return master;}

//Setters
void Card::setCost(int c){cost = c;} //TODO why is mutable?
void Card::setInplay(bool inplay){this->inplay = inplay;} //TODO used at all?

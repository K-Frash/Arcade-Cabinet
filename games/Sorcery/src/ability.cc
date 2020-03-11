#include "ability.h"
#include "card.h"
#include "minion.h"
#include "ritual.h"

void Ability::activateOnMinion(std::unique_ptr<Minion> &minion,
							   Player &player, Game &game){
    throw CardCannotCastOnTarget{*card, *minion};
}

void Ability::activateOnRitual(std::unique_ptr<Ritual> &ritual,
							   Player &player, Game &game){
    throw CardCannotCastOnTarget{*card, *ritual};
}

int Ability::getCost(){
	return cost;
}

void Ability::activateOnGame(Game &Game){
    throw CardCannotCast{*card};
}

Ability &Ability::caller(Card *card){
	this->card = card;
	return *this;
}

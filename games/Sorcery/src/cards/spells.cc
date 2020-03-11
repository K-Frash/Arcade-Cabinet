#include "spells.h"

#include "minion.h"
#include "ritual.h"
#include "player.h"
#include "game.h"

#include <memory>
#include <string>
#include <iostream>

using std::unique_ptr;

//define copy methods

std::unique_ptr<Card> Banish::copy() const{
	return std::make_unique<Banish>(base);
}

std::unique_ptr<Card> Unsummon::copy() const{
	return std::make_unique<Unsummon>(base);
}

std::unique_ptr<Card> Recharge::copy() const{
	return std::make_unique<Recharge>(base);
}

std::unique_ptr<Card> Disenchant::copy() const{
	return std::make_unique<Disenchant>(base);
}

std::unique_ptr<Card> RaiseDead::copy() const{
	return std::make_unique<RaiseDead>(base);
}

std::unique_ptr<Card> Blizzard::copy() const{
	return std::make_unique<Blizzard>(base);
}

// Note: error throwing for an invalid minion is handled in game

// Destroy target minion or ritual
bool Banish::cast(unique_ptr<Minion> &minion, Player &player, Game &game){
	player.removeMinion(minion);
	return false;
}

bool Banish::cast(unique_ptr<Ritual> &ritual, Player &player, Game &game){
	player.removeRitual();
	return false;
}


// Put target minion on the bottom of its owner's deck
bool Unsummon::cast(unique_ptr<Minion> &minion, Player &player, Game &game){

	if(minion->isEnchanted()){
		player.appendToDeck(minion->getBaseMinion().release());
	} else {
		player.appendToDeck(minion.release());
	}

	return false;
}


// Add 3 charges to your ritual
// Throws an error if you do not have a ritual -> Handled outside of here TODO
bool Recharge::cast(unique_ptr<Ritual> &ritual, Player &player, Game &game){
	
	ritual->addCharges(3);
	return false;

}


// Destroy the top enchantment on target minion
// Throws an error if called on a minion with no enchantments
bool Disenchant::cast(unique_ptr<Minion> &minion, Player &player, Game &game){
	if (!minion->isEnchanted()){
		std::cout << "That minion has no enchantments!" << std::endl;
		throw CardCannotCastOnTarget{*this, *minion}; 
	}

	minion = move(minion->disenchant());
	return false;
}

// Resurrect the top minion in your graveyard (move to board)
// Throws an error if the graveyard is empty
// Throws an error if there is no room for new minions
// Note: you == game.activePlayer
bool RaiseDead::cast(Game &game){
	if(game.getActivePlayer().isMinionsFull()){
		std::cout << "You already have 5 minions!" << std::endl;
		throw CardCannotCast{*this};
	}

	try{
		game.getActivePlayer().addMinion(move(game.getActivePlayer().getGraveyardTopCard()),game);
		
	} catch (NoDeadMinions &e){
		std::cout << "You have no dead minions!" << std::endl;
		throw CardCannotCast{*this};
	}
	 //TODO fix constants maybe
	return false;
}

// Do 2 damage to all minions
bool Blizzard::cast(Game &game){
	for(auto &minion : game.getActivePlayer().getMinions()){
		minion->setCurr(minion->getCurr() - 2);
	}
	for(auto &minion : game.getNonactivePlayer().getMinions()){
		minion->setCurr(minion->getCurr() - 2);
	}
	return false;
}

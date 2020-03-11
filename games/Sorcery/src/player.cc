#include "player.h"

#include "card.h"
#include "game.h"
#include "enchantment.h"
#include "testing.h" 

#include "PRNG.h"

#include <iostream>
#include <algorithm>

#include "testing.h"

using std::string;
using std::deque;
using std::vector;

const int STARTING_MAGIC = 3;
const int STARTING_CARDS = 4;
const int STARTING_LIFE = 20;

const int MAX_HAND_SIZE = 5;
const int MAX_BOARD_MINIONS = 5;

//Lambda function for removing moved pointers
template <typename T>
bool isNull(std::unique_ptr<T> &t){
	return t.get() == nullptr;
}


// Constructor
Player::Player(string name, std::deque<std::unique_ptr<Card>> &&deck)
	: name{name}, magic{STARTING_MAGIC}, life{STARTING_LIFE}, deck{std::move(deck)}, hand{}  {

		// Shuffle the deck, do not shuffle well in testing mode
		if(!Testing::testing){
			std::random_shuffle(this->deck.begin(), this->deck.end(), prng);
		}

		//Draw starting hand
		drawCard(STARTING_CARDS);

	}

// Removes a card from the front of deck and adds it to the hand
void Player::drawCard(int amt){

	if (amt > 1) drawCard(amt - 1);

	// Test for deck empty/hand full
	if(deck.size() == 0 || hand.size() == MAX_HAND_SIZE){
		return;
	}

	hand.push_back(std::move(deck[0]));
	deck.erase(deck.begin());
}

std::unique_ptr<Ritual> &Player::getRitual(){
	return ritual;
}

void Player::discardCard(unsigned int index){
	if (index < 0 || index >= getHand().size()){
		throw CardOutOfRange{index, getName(), CardOutOfRange::Hand};
	}

	getHand().erase(getHand().begin() + index);
}

template <typename Derived, typename Base>
std::unique_ptr<Derived> static_unique_ptr_cast(std::unique_ptr<Base> &&ptr) {
	return std::unique_ptr<Derived>(static_cast<Derived*>(ptr.release()));
}

bool Player::hasEnoughMagic(int cost){
	return this->magic >= cost;
}

std::unique_ptr<Card> &Player::getCardFromHand(unsigned int index){
	if (index >= getHand().size()) throw CardOutOfRange{index, getName(), CardOutOfRange::Hand};
	return getHand()[index];
}

std::unique_ptr<Minion> &Player::getCardFromMinions(unsigned int index){
	if (index >= getMinions().size()) throw CardOutOfRange{index, getName(), CardOutOfRange::Minions};
	return getMinions()[index];
}

std::unique_ptr<Minion> &Player::getGraveyardTopCard(){
	if(graveyard.size() == 0){
		throw NoDeadMinions{};
	}
	return getGraveyard()[graveyard.size() - 1];
}

bool Player::isMinionsFull() const {
	return minions.size() == MAX_BOARD_MINIONS;
}

void Player::removeCardFromHand(uint i){
	hand.erase(hand.begin() + i);
}

void Player::minionAttack(unsigned int i, Player &player, unsigned int j){
	auto &minion1 = getCardFromMinions(i);
	auto &minion2 = player.getCardFromMinions(j);
	if(minion1->getMove()){
		std::cout << "This minion has already attacked this turn!" << std::endl;
		return;
	}
	else{
		minion1->attackMinion(*minion2);
		minion1->setMove(true);
	}
}

void Player::playerAttack(unsigned int i, Player &player2){
	auto &minion = getCardFromMinions(i);
	if(minion->getMove()){
		std::cout << "This minion has already attacked this turn!" << std::endl;
		return;
	}
	else{
		player2.setLife(player2.getLife() - minion->getAtt());
		minion->setMove(true);
	}
}

void Player::addMinion(std::unique_ptr<Minion> &&minion, Game &game){
	Minion &m = *minion; //am assuming move does not copy
	if (minions.size() == MAX_BOARD_MINIONS){
		throw MinionsFull{};
	}
	minions.push_back(move(minion));
	game.triggerMinionPlay(m, *this);
}

void Player::checkForDead(){
	unsigned int dex = 0;
	for(auto &minionToCheck : getMinions()){
		if (minionToCheck->getCurr() <= 0){
			minionToCheck->setMove(false); //resets them to default state of movement;
			this->removeMinion(dex);
		}
		++dex;
	}
}

void Player::removeMinion(unsigned int i){
	auto &deadminion = getCardFromMinions(i);
	deadminion->reset();
	graveyard.emplace_back(std::move(deadminion));
	minions.erase(minions.begin() + i);
}

void Player::resetMinionMoves(){
	for(auto &minionToReset : this->minions){
		minionToReset->setMove(false);
	}
}

void Player::appendToDeck(Card * card){
	deck.emplace_back(std::unique_ptr<Card>(card));
}
void Player::removeMinion(std::unique_ptr<Minion> &card){
	auto it=find(minions.begin(),minions.end(),card);
	if ( it != minions.end()){
		graveyard.emplace_back(std::move(card));
		minions.erase(it);
	}
}

void Player::removeRitual(){
	ritual = nullptr;
}

InquiryableCard *Player::inspect(unsigned int i){
	return getCardFromMinions(i).get();
}

bool Player::hasMinion(const Card &card){
	for (auto &m : minions){
		if (m.get() == &card) return true;
	}
	return false;
}


//-- Getters: --//
// Get Name
std::string Player::getName() const {
	return this->name;
}

// Get Magic
int Player::getMagic() const {
	return this->magic;
}

//Get Life
int Player::getLife() const {
	return this->life;
}

//-- Setters: --//
void Player::setMagic(int n){this->magic = n;}

void Player::setLife(int n){this->life = n;}

void Player::addMagic(int magic){
	if (magic < 0) throw "Stupid programmer";
	this->magic += magic;
}

void Player::removeMagic(int magic){
	if (magic < 0) throw "Stupid programmer";

	if (this->magic - magic < 0){
		if(Testing::testing){
			this->magic = 0;
		} else {
			throw InsufficientMagic{}; //This is checked for, so should only be reached by programmer error
		}
	} else {
		this->magic -= magic;
	}
}

//-- For Display --//
const std::vector<InquiryableCard *> Player::inquiryHand(){
	vector<InquiryableCard *> out;
	for (auto &card: getHand()) out.push_back(card.get());
	return out;
};

const std::vector<InquiryableCard *> Player::inquiryMinions() {
	vector<InquiryableCard *> out;
	for (auto &card: getMinions()) out.push_back(card.get());
	return out;
};

const PlayerInquiry Player::inquiry() {
	return PlayerInquiry{name, magic, life, inquiryHand(),
		inquiryMinions(),(getGraveyard().size() > 0 ? getGraveyard().back().get() : nullptr), ritual.get()};
}

std::vector<std::unique_ptr<Minion>> &Player::getMinions(){
	auto new_end = remove_if(minions.begin(), minions.end(), isNull<Minion>);
	minions.erase(new_end, minions.end());
	return minions;
}

std::vector<std::unique_ptr<Card>> &Player::getHand(){
	auto new_end = remove_if(hand.begin(), hand.end(), isNull<Card>);
	hand.erase(new_end, hand.end());
	return hand;
}

std::vector<std::unique_ptr<Minion>> &Player::getGraveyard(){
	auto new_end = remove_if(graveyard.begin(), graveyard.end(), isNull<Minion>);
	graveyard.erase(new_end, graveyard.end());
	return graveyard;
}

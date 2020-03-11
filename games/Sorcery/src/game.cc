#include "game.h"
#include "testing.h"
#include "inquiry/gameinquiry.h"

#include <utility>

using std::move;

template <typename Derived, typename Base>
std::unique_ptr<Derived> static_unique_ptr_cast(std::unique_ptr<Base> &&ptr) {
	return std::unique_ptr<Derived>(static_cast<Derived*>(ptr.release()));
}

Game::Game(Player player1, Player player2)
	: player1{move(player1)}, player2{move(player2)}, activePlayer{&(this->player1)} {}

Player& Game::getActivePlayer(){
	return *activePlayer;
}

// -- Getters -- //
int Game::getPlayerNumber(Player& player){
    return (&player == &player1) ? 1 : 2;
}

Player& Game::getNonactivePlayer(){
	return (activePlayer == &player1 ? player2 : player1);
}

bool Game::over() const {
	return this->player1.getLife() <= 0 || this->player2.getLife() <= 0;
}

  // invalid to call this is over != true
const Player& Game::getWinner() const {
	if (!over()){
		throw "The game isn't over; Stupid programmer";
	}
	return this->player1.getLife() <= 0 ? player2 : player1;
}

// -- For Display -- //
InquiryableCard *Game::inspect(unsigned int i){
    return activePlayer->inspect(i);
}

const GameInquiry Game::inquiry(){
	return GameInquiry{&player1, &player2};
}

// -- Play -- //
void Game::play(unsigned int i){
	auto &card = activePlayer->getCardFromHand(i); // THIS IS AN ITERATOR, IT FAILS TO BE VALID IF YOU MODIFY THE SOURCE COLLECTION FIXME
	int cost = card->getCost();
	if(!card->requires_target()){

		//Check for sufficient magic
		if( ! (activePlayer->hasEnoughMagic(cost) || Testing::testing)){
			std::cout << "You do not have enough magic to play that card!" << std::endl;
			return;
		}

		switch(card->getType()){
			case CType::Ritual:
				card->setInplay(true);
				activePlayer->getRitual() = static_unique_ptr_cast<Ritual, Card>(move(card));
				//TODO: Probably need to call play on ritual
				break;
			case CType::Spell:
				//TODO: implements spells
				break;
			case CType::Minion:
				activePlayer->addMinion(static_unique_ptr_cast<Minion, Card>(move(card)), *this);
				//TODO: Probably need to call play on card
				break;
			default:
				throw CardCannotCast{*card};
				return;
				//only minions, rituals and spells can be played without target
		}
		//Default returns, so this is only caused if card play is successful
		activePlayer->removeMagic(cost);
		activePlayer->removeCardFromHand(i);
	}
}

void Game::play(unsigned int i, int p, unsigned int j){
    Player &player = (p == 1)? player1 : player2;
    auto &carda = activePlayer->getCardFromHand(i);
    auto &cardb = player.getCardFromMinions(j);

// __        ___    ____  _   _ ___ _   _  ____ 
// \ \      / / \  |  _ \| \ | |_ _| \ | |/ ___|
//  \ \ /\ / / _ \ | |_) |  \| || ||  \| | |  _ 
//   \ V  V / ___ \|  _ <| |\  || || |\  | |_| |
//    \_/\_/_/   \_\_| \_\_| \_|___|_| \_|\____|
// FIXME(WARNING): You must *TRUE* if the in cast if
// if the ownership changes.
    if (carda->cast(cardb, player, *this)){
        carda.release();
    } //assume will throw if invalid
    activePlayer->removeCardFromHand(i);
}

void Game::play(unsigned int i, int p){
	Player &player = (p == 1)? player1 : player2;
	auto &carda = activePlayer->getCardFromHand(i);
	auto &ritual = player.getRitual();

	if(ritual == nullptr){
		std::cout << "Player doesn't have a ritual to cast on!" << std::endl;
		throw CardCannotCast{*carda};
	}

// __        ___    ____  _   _ ___ _   _  ____ 
// \ \      / / \  |  _ \| \ | |_ _| \ | |/ ___|
//  \ \ /\ / / _ \ | |_) |  \| || ||  \| | |  _ 
//   \ V  V / ___ \|  _ <| |\  || || |\  | |_| |
//    \_/\_/_/   \_\_| \_\_| \_|___|_| \_|\____|
// FIXME(WARNING): You must *TRUE* if the in cast if
// if the ownership changes.
    carda->cast(ritual, player, *this);
    activePlayer->removeCardFromHand(i);
}

void Game::useAbility(unsigned int i){
	auto &minion = activePlayer->getCardFromMinions(i);
	minion->getAbility().caller(minion.get()).activateOnGame(*this);
}

void Game::useAbility(unsigned int i, int p){
	Player &player = (p == 1)? player1 : player2;
	auto &minion = activePlayer->getCardFromMinions(i);
	auto &ritual = player.getRitual();
	if(ritual == nullptr){
		std::cout << "Player doesn't have a ritual to cast on!" << std::endl;
		throw CardCannotCast{*minion};
	}

	minion->getAbility().caller(minion.get()).activateOnRitual(ritual,player,*this);
}


void Game::useAbility(unsigned int i, int p, unsigned int j){
	Player &player = (p == 1)? player1 : player2;
	auto &minion1 = activePlayer->getCardFromMinions(i);
	auto &minion2 = player.getCardFromMinions(j);

	minion1->getAbility().caller(minion1.get()).activateOnMinion(minion2,player,*this);
}

void Game::triggerTurnEnd(){
	for(auto &m: getActivePlayer().getMinions()){
		m->getAbility().caller(m.get()).onTurnEnd(*this);
	} 
	if (getActivePlayer().getRitual().get() != nullptr) getActivePlayer().getRitual()->onTurnEnd(*this);
	for(auto &m:getNonactivePlayer().getMinions()){
		m->getAbility().caller(m.get()).onTurnEnd(*this);
	} 
	if (getNonactivePlayer().getRitual().get() != nullptr) getNonactivePlayer().getRitual()->onTurnEnd(*this);
}
void Game::triggerTurnStart(){
	for(auto &m: getActivePlayer().getMinions()){
		m->getAbility().caller(m.get()).onTurnStart(*this);
	} 
	if (getActivePlayer().getRitual().get() != nullptr) getActivePlayer().getRitual()->onTurnStart(*this);
	for(auto &m:getNonactivePlayer().getMinions()){
		m->getAbility().caller(m.get()).onTurnStart(*this);
	} 
	if (getNonactivePlayer().getRitual().get() != nullptr) getNonactivePlayer().getRitual()->onTurnStart(*this);
}
void Game::triggerMinionPlay(Minion &minion, Player &player){
	for(auto &m: getActivePlayer().getMinions()){
		m->getAbility().caller(m.get()).onMinionETB(minion, player, *this);
	} 
	if (getActivePlayer().getRitual().get() != nullptr) getActivePlayer().getRitual()->onMinionETB(minion, player, *this);
	for(auto &m:getNonactivePlayer().getMinions()){
		m->getAbility().caller(m.get()).onMinionETB(minion, player, *this);
	} 
	if (getNonactivePlayer().getRitual().get() != nullptr) getNonactivePlayer().getRitual()->onMinionETB(minion, player, *this);
}
void Game::endTurn(){
	triggerTurnEnd();
	activePlayer->resetMinionMoves();
    activePlayer = &getNonactivePlayer();
    activePlayer->addMagic(1);
    activePlayer->drawCard(1);
	triggerTurnStart();
}

void Game::checkDead(){
	player1.checkForDead();
	player2.checkForDead();
}

//----- Atacks -----

void Game::Attack(unsigned int i, unsigned int j){
	activePlayer->minionAttack(i, this->getNonactivePlayer(),j);
}

void Game::Attack(unsigned int i){
	activePlayer->playerAttack(i, this->getNonactivePlayer());
}

//------------------

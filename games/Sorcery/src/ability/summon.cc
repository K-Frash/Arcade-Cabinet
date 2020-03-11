#include "summon.h"

#include "../game.h"
#include "../cardcatalog.h"

template <typename Derived, typename Base>
std::unique_ptr<Derived> static_unique_ptr_cast(std::unique_ptr<Base> &&ptr) {
	return std::unique_ptr<Derived>(static_cast<Derived*>(ptr.release()));
}

Summon::Summon(int cost, int amount, const std::string &minion)
	:cost{cost}, type{AType::Activated}, amount{amount}, minion{minion}{};

void Summon::activateOnGame(Game &game){
	Player &player = game.getActivePlayer();
	while(!player.isMinionsFull()){
		player.addMinion(static_unique_ptr_cast<Minion,Card>(CARD_CATALOG[minion]->copy()),game);
	}
}

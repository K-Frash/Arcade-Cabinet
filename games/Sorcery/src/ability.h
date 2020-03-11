#ifndef __ABILITY_H_
#define __ABILITY_H_

#include <memory>
#include "triggerobserver.h"
#include "AType.h"

class Ritual;
class Player;
class Game;
class Card;
class Ability: public TriggerObserver{
	protected:
	int cost = 1;
	AType type;
	Card *card;
	public:
	Ability &caller(Card *card);
	int getCost();
	virtual void activateOnMinion(std::unique_ptr<Minion> &minion, Player &player, Game &game);
	virtual void activateOnRitual(std::unique_ptr<Ritual> &ritual, Player &player, Game &game);
	virtual void activateOnGame(Game &Game);
};

#endif // __ABILITY_H_

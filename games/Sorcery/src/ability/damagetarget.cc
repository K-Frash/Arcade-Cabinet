#include "damagetarget.h"
#include "../game.h"

void DamageOnTarget::activateOnMinion(std::unique_ptr<Minion> &minion, Player &player, Game &game){
	minion->setCurr(minion->getCurr() - 1);
}

#include "healonstart.h"
#include "../game.h"

void HealOnStart::onTurnStart(Game &game){
	if (game.getActivePlayer().hasMinion(*card)){
		for (auto &min: game.getActivePlayer().getMinions()){
			min->setCurr(min->getCurr() +1);
		}
	}
}

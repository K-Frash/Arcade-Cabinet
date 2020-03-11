#include "damageonplay.h"
#include "../game.h"


void DamageOnPlay::onMinionETB(Minion &minion, Player &player, Game &game){
	if(!player.hasMinion(*card)){
		minion.setCurr(minion.getCurr() - 1);
	}
}

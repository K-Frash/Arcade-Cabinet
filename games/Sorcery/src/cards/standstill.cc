#include "standstill.h"
#include "game.h"

using namespace std;

StandStill::StandStill(const CardBase &base, int charges, int activationCost)
	:Ritual{base, charges, activationCost}{}

StandStill::StandStill(StandStill &&other): Ritual{move(other)}{}

std::unique_ptr<Card> StandStill::copy() const {
	return std::make_unique<StandStill>(base, charges, activationCost);//using new for now
}

void StandStill::onMinionETB(Minion &minion, Player &player, Game &game){
	if (attemptCast()) minion.setCurr(0);
}

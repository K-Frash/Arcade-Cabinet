#include "darkritual.h"
#include "game.h"

using namespace std;

DarkRitual::DarkRitual(const CardBase &base, int charges, int activationCost)
	:Ritual{base, charges, activationCost}{}

DarkRitual::DarkRitual(DarkRitual &&other): Ritual{move(other)}{}

std::unique_ptr<Card> DarkRitual::copy() const {
	return std::make_unique<DarkRitual>(base, charges, activationCost);//using new for now
}

void DarkRitual::onTurnStart(Game &game){
	if (attemptCast()) game.getActivePlayer().setMagic(1);
}

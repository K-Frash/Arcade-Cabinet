#include "auraofpower.h"
#include "game.h"

using namespace std;

AuraofPower::AuraofPower(const CardBase &base, int charges, int activationCost)
	:Ritual{base, charges, activationCost}{}

AuraofPower::AuraofPower(AuraofPower &&other): Ritual{move(other)}{}

std::unique_ptr<Card> AuraofPower::copy() const {
	return std::make_unique<AuraofPower>(base, charges, activationCost);//using new for now
}

void AuraofPower::onMinionETB(Minion &minion, Player &player, Game &game){
	if (attemptCast()){
		if (player.getRitual().get() == this){
			minion.setAtt(minion.getAtt()+1);
			minion.setCurr(minion.getCurr()+1);
		}
	}
}

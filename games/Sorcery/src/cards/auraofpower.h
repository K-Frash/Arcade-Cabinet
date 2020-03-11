#ifndef __AURAOFPOWER_H_
#define __AURAORPOWER_H_

#include "../ritual.h"

class AuraofPower: public Ritual {
public:
	AuraofPower(const CardBase &base, int charges, int activationCost);
	AuraofPower(AuraofPower &&other); 
	virtual std::unique_ptr<Card> copy() const override;
	virtual void onMinionETB(Minion &minion, Player &player, Game &game) override;
};

#endif // __AURAOFPOWER_H_

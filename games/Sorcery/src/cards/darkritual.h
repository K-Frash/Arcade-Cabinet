#ifndef __DARKRITUAL_H_
#define __DARKRITUAL_H_

#include "../ritual.h"

class DarkRitual: public Ritual {
public:
	DarkRitual(const CardBase &base, int charges, int activationCost);
	DarkRitual(DarkRitual &&other); 
	virtual std::unique_ptr<Card> copy() const override;
	virtual void onTurnStart(Game &game) override;
};

#endif // __DARKRITUAL_H_

#ifndef __RITUAL_H_
#define __RITUAL_H_

#include <string>
#include <memory>
#include "CType.h"
#include "card.h"
#include "cardbase.h"
#include "triggerobserver.h"


class Ritual : public Card, public TriggerObserver {
protected:
	int charges;
	int activationCost; //eventually will be in abilty class
	bool attemptCast();
public:
	// Ctors
	Ritual(const CardBase &base, int charges, int activationCost);
	Ritual(Ritual &&other); 
	virtual ~Ritual();  
	virtual std::unique_ptr<Card> copy() const override;

	//Getters
	virtual int getCharges() const;
	virtual int getActivationCost() const;

	//Setters
	virtual void addCharges(unsigned int charges);

	//inquiry
	virtual const CardInquiry inquiry() const override;

	//Setters

	//Minions interactions
	//	virtual void death(std::shared_ptr<Game> g);
	//	virtual void useAbility(std::shared_ptr<Game> g);
	//	virtual void attackPlayer(std::shared_ptr<Game> g);
	//	virtual void inspect();

	//P.V. from Card.h
	const CType getType() const override;
	void prettyprint() override;
};


#endif // __RITUAL_H_

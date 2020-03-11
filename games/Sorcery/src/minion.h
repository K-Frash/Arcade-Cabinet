#ifndef _MINION_H_
#define _MINION_H_
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <memory>

#include "CType.h"
#include "card.h"
#include "cardbase.h"
#include "ability.h"
#include "triggerobserver.h"

class Minion : public Card, public TriggerObserver{
protected:
	Ability &ability;
	int attack;	//attack value of minion
	int health;	//max hp of minion
	int currhp;	//how much damage the minion has taken
	bool moved;	//bool to see if the minion has attacked

public:
	// Ctors
	Minion(const CardBase &base, Ability &ability);
	Minion(Minion &&other);
	virtual ~Minion();  //since enchant IS-A minion
	virtual std::unique_ptr<Card> copy() const override;
	
	//Getters
	virtual int getAtt() const;
	virtual int getHp() const;
	virtual int getCurr() const;
	virtual bool getMove() const;

	virtual bool isEnchanted() const;

	//inquiry
	virtual const CardInquiry inquiry() const override;

	//Setters
	virtual void setAtt(int n);
	virtual void setHp(int n);
	virtual void setCurr(int n);
	virtual void setMove(bool b);

	// reset curr to Att - use better variable names plskthx
	virtual void reset();

	// disenchant
	struct MinionNotEnchanted{};
	virtual std::unique_ptr<Minion> &disenchant();
	virtual std::unique_ptr<Minion> &getBaseMinion();

	//Minions interactions
	//	virtual void death(std::shared_ptr<Game> g);
	//	virtual void useAbility(std::shared_ptr<Game> g);
	virtual void attackMinion(Minion &m); //change to Game ptr when loops works
	//	virtual void inspect();

	//P.V. from Card.h
	const CType getType() const override;
	void prettyprint() override;
	Ability &getAbility();
};

std::ostream& operator<<(std::ostream &o, const Minion &m);

#endif

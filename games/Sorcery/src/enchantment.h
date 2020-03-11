#ifndef _ENCHANT_H_
#define _ENCHANT_H_

#include <iostream>
#include <string>
#include <memory>
#include "minion.h"
#include "card.h"
class Player;
class Game;

class Enchantment: public Minion{
	int eID = 0; //id to apply enchantment

	std::unique_ptr<Minion> basem; //base Minion
	public:

	Enchantment(const CardBase &base, Ability &ability);
    Enchantment(Enchantment &&other);
	virtual ~Enchantment();
    virtual std::unique_ptr<Card> copy() const override;
 
	//Override Minion getters and setters!
	int getAtt() const override;
	int getHp() const override;
	int getCurr() const override;
	int getCost() const override;
	bool getMove() const override;

	bool isEnchanted() const override;
	
	const std::string &getName() const override;
	const std::string &getDesc() const override;

	virtual bool cast(std::unique_ptr<Minion> &min, Player &player, Game &game) override;

	std::unique_ptr<Minion> &disenchant() override;
	std::unique_ptr<Minion> &getBaseMinion() override;

    //inquiry
    virtual const CardInquiry inquiry() const override;
    const CardInquiry inquiryBase() const override;
	void setAtt(int n) override;
	void setHp(int n) override;
	void setCurr(int n) override;
	void setMove(bool b) override;

	//Override Minion P.V. from Card.h (english is hard to type)
	void prettyprint() override;
	const CType getType() const override;
};

#endif

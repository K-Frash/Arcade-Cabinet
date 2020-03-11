#ifndef _SPELL_H_
#define _SPELL_H_

#include <string>
#include <memory>
#include "card.h"
#include "cardbase.h"
#include "CType.h"
#include "AType.h"

class Spell: public Card{
	int spellID;
	public:

	//Ctor and Dtor
	Spell(const CardBase &base);	      //w-out player ref
	Spell(Spell &&spell);	      //w-out player ref
	virtual ~Spell();
	
	//P.V. from Card
	void prettyprint() override;
	const CType getType() const override;

	//Override Card Actions:
	virtual std::unique_ptr<Card> copy() const override;
	virtual const CardInquiry inquiry() const override;
//	void play(std::shared_ptr<Game> g) override;			TODO
//	void play(std::shared_ptr<Game> g, int i, int j) override;	TODO
};

#endif

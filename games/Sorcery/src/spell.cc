#include "spell.h"
#include "card.h"
#include <iostream>

using namespace std;

/*
Until "play" is solidified, it may be best to treat this card with care
in terms of implementation
*/

Spell::Spell(const CardBase &base) : Card{base} {}

Spell::~Spell(){}

void Spell::prettyprint(){
	cout << "Spell: " << base.name;
	cout << ", cost: " << cost;
	cout << endl;
}

const CType Spell::getType() const {return CType::Spell;}

const CardInquiry Spell::inquiry() const{
	return CardInquiry{base.name, base.desc, CType::Spell, cost, 0, 0, AType::None};
}


Spell::Spell(Spell &&other): Card{move(other)} { }

std::unique_ptr<Card> Spell::copy() const{
	return std::make_unique<Spell>(base);
}

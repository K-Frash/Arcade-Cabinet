#include "ritual.h"

#include <iostream> //just for pretty print can remove

using namespace std;

Ritual::Ritual(const CardBase &base, int charges, int activationCost): Card{base},
  charges{charges}, activationCost{activationCost} { 
}

Ritual::Ritual(Ritual &&other): Card{move(other)},
    charges{other.charges}, activationCost{other.activationCost} { }

Ritual::~Ritual(){}

std::unique_ptr<Card> Ritual::copy() const {
    return std::make_unique<Ritual>(base,charges, activationCost);//using new for now
}
// Getters
int Ritual::getCharges()const {
	return charges;
}

int Ritual::getActivationCost() const {
	return activationCost;
}

// Setters
void Ritual::addCharges(unsigned int charges) {
	this->charges += charges;
}

//inquiry
const CardInquiry Ritual::inquiry() const{//TODO: Refactor inquiry interface to allow for clean
                                          // representation of ritual
    return CardInquiry{base.name, base.desc, CType::Ritual, cost, charges, 0, AType::None,activationCost  };
};

bool Ritual::attemptCast(){
	if (charges < activationCost) return false;
	charges -= activationCost;
	return true;
}

const CType Ritual::getType() const {
    return CType::Ritual;
}
void Ritual::prettyprint(){
	cout << "Ritual: " << base.name;
	cout << ", cost: " << cost;
	cout << ", charges: " << charges;
	cout << ", activate: " << activationCost; //is it hp or def?
	cout << endl;
}

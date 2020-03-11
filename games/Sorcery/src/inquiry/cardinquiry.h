#ifndef __CARDQUERY_H_
#define __CARDQUERY_H_

#include "../CType.h"
#include "../AType.h"
#include <string>

class InquiryableCard;

struct CardInquiry{
   const std::string &name;
   const std::string &desc;
   const CType type;
   const int cost;
   const int attack;
   const int defence;
   const AType abilityType;
   const int abilityCost;
   const InquiryableCard *enchanted_base;
};

#endif // __CARDQUERY_H_

#ifndef __CARDCATALOG_H_
#define __CARDCATALOG_H_

#include "card.h"
#include "cardbase.h"
#include <map>
#include <string>
#include <memory>

//constructs all cards when initlized
//use: cardCata["Card Name"] to get unique_ptr
//     for copying the card from into decks
class CardCatalog {
    std::map<std::string, std::unique_ptr<const Card>> cards;
public:
    CardCatalog();
    std::unique_ptr<const Card> &operator[](const std::string &name); 
};

extern CardCatalog CARD_CATALOG;

#endif // __CARDCATALOG_H_

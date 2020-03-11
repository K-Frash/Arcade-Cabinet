#ifndef __CARDBASE_H_
#define __CARDBASE_H_

#include <string>
struct CardBase {
    const std::string name;
    int cost;
    const std::string desc;
    int attack; //may be undefined for cards types without attack
    int defence;//may be undefined for cards types without defence
};


#endif // __CARDBASE_H_

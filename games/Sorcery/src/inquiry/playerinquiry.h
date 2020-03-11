#ifndef __PLAYERINQUIRY_H_
#define __PLAYERINQUIRY_H_

#include <string>
#include <vector>

#include "inquiryablecard.h"

class InquiryableCard;

struct PlayerInquiry{
   const std::string &name;
   const int magic;
   const int life;
   const std::vector<InquiryableCard *> hand;
   const std::vector<InquiryableCard *> minions;
   const InquiryableCard * graveyard_top;
   const InquiryableCard * ritual;
};


#endif // __PLAYERINQUIRY_H_

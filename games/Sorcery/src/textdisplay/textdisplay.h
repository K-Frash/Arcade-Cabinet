#ifndef __TEXTDISPLAY_H_
#define __TEXTDISPLAY_H_

#include "../inquiry/inquiryablecard.h"
#include "../inquiry/inquiryableplayer.h"
#include "../inquiry/gameinquiry.h"

#include "iostream"

class TextDisplay{
    std::ostream &out;

    void displayRow(const std::vector<std::vector<std::string>> &templated_cards,
                    bool has_border);
        public:
        TextDisplay(std::ostream &out);

        void inspectCard(const InquiryableCard* card);

        void displayHand(const PlayerInquiry& player);
        void displayHand(const std::vector<InquiryableCard *>& cards);

        //Displays full-board output as per the specfications in sorcery.pdf
        //with boarder
        void displayBoard(const GameInquiry& inq);
    };
    #endif // __TEXTDISPLAY_H_

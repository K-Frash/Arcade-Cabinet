#include "textdisplay.h"
#include "ascii_graphics.h"

const int HAND_SIZE = 5;
const int BOARD_SIZE = 165; //without border

TextDisplay::TextDisplay(std::ostream &out): out{out}{}

//Given a CardInquiry produces the respected card Template
card_template_t templateCard(const CardInquiry& inq){
    switch(inq.type){
        case CType::Enchantment:
            return display_enchantment(inq.name, inq.cost, inq.desc);
        case CType::Minion:
            switch(inq.abilityType){
                case AType::Trigger:
                    return  display_minion_triggered_ability(inq.name, inq.cost, inq.attack,
                                                             inq.defence ,inq.desc);
                case AType::Activated:
                    return display_minion_activated_ability(inq.name, inq.cost, inq.attack,
                                                             inq.defence,inq.abilityCost, inq.desc);
                default:
                    return display_minion_no_ability(inq.name, inq.cost, inq.attack, inq.defence );
            }
        case CType::Ritual:
            return display_ritual(inq.name, inq.cost, inq.abilityCost, inq.desc, inq.attack);
	case CType::Spell:
	    return display_spell(inq.name, inq.cost, inq.desc);
        default: //case CType::Spell: (default to supress warnings no return)
            return display_minion_no_ability(inq.name, inq.cost, inq.attack, inq.defence );
    } 
}


//Constructs a vector of templates from a templates of 
//inquiryaable cards and pads the vector with blank cards
std::vector<card_template_t> templateRow(const std::vector<InquiryableCard *>& cards){
    std::vector<std::vector<std::string>> templated_cards;
    for (auto &card: cards){
        templated_cards.push_back(templateCard(card->inquiry()));
    }
    for (auto i = templated_cards.size(); i < HAND_SIZE; ++i){ //Pad Hand with cards
        templated_cards.push_back(CARD_TEMPLATE_BORDER);         //if less then 5
    }
    return templated_cards;
}

//Prints a vectors of card_templates to the display on the same row.
void TextDisplay::displayRow(const std::vector<card_template_t> &templated_cards,
                             bool has_border=false){
    if (templated_cards.size() == 0) return;
    for(std::vector<int>::size_type i  = 0; i != templated_cards[0].size(); i++) {
        if (has_border) out << EXTERNAL_BORDER_CHAR_UP_DOWN;
        for (auto &card_template: templated_cards){
            out << card_template[i]; // Output line
        }
        if (has_border) out << EXTERNAL_BORDER_CHAR_UP_DOWN;
        out << std::endl;
    }
}

const CardInquiry getBaseOfEnchantedCard(const InquiryableCard* card){
    const CardInquiry inq = card->inquiry();
    if (inq.enchanted_base == nullptr) return inq;
    return getBaseOfEnchantedCard(inq.enchanted_base);
}

void TextDisplay::inspectCard(const InquiryableCard* card){
    std::vector<card_template_t> templated_cards;
    templated_cards.push_back(templateCard(getBaseOfEnchantedCard(card)));
    displayRow(templated_cards);
    templated_cards.clear();
    const InquiryableCard *base_card = card->inquiry().enchanted_base;
    while (base_card != nullptr){
        const CardInquiry inq = base_card->inquiryBase(); 
        templated_cards.push_back(templateCard(inq));
        if (templated_cards.size() == 5){
            displayRow(templated_cards);
            templated_cards.clear();
        }
        base_card = inq.enchanted_base;
    }
    if (templated_cards.size() > 0){
        displayRow(templated_cards);
    }
}

//Displays a players hand given a playerInquiry
void TextDisplay::displayHand(const PlayerInquiry& player){
    displayRow(templateRow(player.hand));
}

//Displays a players hand given an vectors of hand
void TextDisplay::displayHand(const std::vector<InquiryableCard *>& cards){
    displayRow(templateRow(cards));
}

//Displays full-board output as per the specfications in sorcery.pdf
//with boarder
void TextDisplay::displayBoard(const GameInquiry& inq){
    out << EXTERNAL_BORDER_CHAR_TOP_LEFT;//Top Border
    for(int i = 0; i < BOARD_SIZE; ++i) out << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    out << EXTERNAL_BORDER_CHAR_TOP_RIGHT << std::endl;
    
    std::vector<card_template_t> row;

    //Player 1(TOP) display
    PlayerInquiry player1 = inq.player1->inquiry();

    row.push_back(player1.ritual //If player1 has ritual place ritual 
                  ? templateCard(player1.ritual->inquiry()) : CARD_TEMPLATE_BORDER);
    
    row.push_back(CARD_TEMPLATE_EMPTY);// part of the layout of the board;
    row.push_back(display_player_card(1, player1.name, player1.life, player1.magic));
    row.push_back(CARD_TEMPLATE_EMPTY);// part of the layout of the board;

    row.push_back(player1.graveyard_top //If player1 has graveyard card place it 
                  ? templateCard(player1.graveyard_top->inquiry()) : CARD_TEMPLATE_BORDER);
    displayRow(row, true);//display row with borders
    row.clear();
    displayRow(templateRow(player1.minions),true); //output players1 minions

    for(auto &line: CENTRE_GRAPHIC) out << line << std::endl; //output Center Graphic

    //Player 2(BOTTOM) display
    PlayerInquiry player2 = inq.player2->inquiry();

    displayRow(templateRow(player2.minions),true); //output players2 minions
    row.push_back(player2.ritual //If player2 has ritual place ritual 
                  ? templateCard(player2.ritual->inquiry()) : CARD_TEMPLATE_BORDER);
    
    row.push_back(CARD_TEMPLATE_EMPTY);// part of the layout of the board;
    row.push_back(display_player_card(2, player2.name, player2.life, player2.magic));
    row.push_back(CARD_TEMPLATE_EMPTY);// part of the layout of the board;

    row.push_back(player2.graveyard_top //If player2 has graveyard card place it 
                  ? templateCard(player2.graveyard_top->inquiry()) : CARD_TEMPLATE_BORDER);
    displayRow(row, true);//display row with borders
    
    out << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;//Bottom Border
    for(int i = 0; i < BOARD_SIZE; ++i) out << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
    out << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT << std::endl;
}

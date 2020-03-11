#ifndef PLAYER_H
#define PLAYER_H

#include "inquiry/inquiryableplayer.h"
#include "minion.h" 
#include "ritual.h" 

#include <string>
#include <deque>
#include <vector>


class Player: public InquiryablePlayer {
	std::string name;
	int magic;
	int life;

	std::deque<std::unique_ptr<Card>> deck;
	std::vector<std::unique_ptr<Card>> hand;
	std::vector<std::unique_ptr<Minion>> minions;
	std::vector<std::unique_ptr<Minion>> graveyard;
	std::unique_ptr<Ritual> ritual;

	//Return if player can expend magic
	//helpful since when testing::testing is true
	//we do not consider the cost.

	public:
	bool hasEnoughMagic(int magic);
	Player(std::string name, std::deque<std::unique_ptr<Card>> &&deck);

	void drawCard(int amt = 0);
	void discardCard(unsigned int index);

	void minionAttack(unsigned int i, Player &player, unsigned int j);
	void playerAttack(unsigned int i, Player &player2); //minion hits player

	void addMinion(std::unique_ptr<Minion> &&minion, Game &game);
	void removeMinion(unsigned int i);
	
	void checkForDead();
	void removeMinion(std::unique_ptr<Minion> &card);
	void removeRitual();
	bool hasMinion(const Card &card);
	void resetMinionMoves();

	std::string getName() const;
	int getMagic() const;
	int getLife() const;
	std::unique_ptr<Ritual> &getRitual();
	bool isMinionsFull() const;
	//Helpers that will throw CardOutOfRange exceptions
	//if the index is out of bounds.
	std::unique_ptr<Card> &getCardFromHand(unsigned int index);
	std::unique_ptr<Minion> &getCardFromMinions(unsigned int index);
	std::unique_ptr<Minion> &getGraveyardTopCard();

	void setLife(int n);
	void setMagic(int n);
	void addMagic(int magic);
	void removeMagic(int magic);

	void appendToDeck(Card * card);
	void removeCardFromHand(uint i);

	const std::vector<InquiryableCard *> inquiryMinions() ;
	const std::vector<InquiryableCard *> inquiryHand() ;
	const PlayerInquiry inquiry() override;
	InquiryableCard *inspect(unsigned int i);

	std::vector<std::unique_ptr<Minion>> &getMinions();
	std::vector<std::unique_ptr<Card>> &getHand();
	std::vector<std::unique_ptr<Minion>> &getGraveyard();
};

//Exceptions
struct MinionsFull{};
struct InsufficientMagic{};
struct NoDeadMinions{};
struct NoRitual{};

struct CardOutOfRange {
	enum CardLocation {
		Hand,
		Ritual,
		Minions,
		GraveYard
	};

	unsigned int index;
	std::string playername;
	CardLocation where;
	std::string location(){
		switch(where){
			case CardLocation::Hand: return "Hand"; 
			case CardLocation::Ritual: return "Ritual"; 
			case CardLocation::Minions: return "Minions"; 
			case CardLocation::GraveYard: return "Grave Yard"; 
			default: return "";
		}
	}
};
#endif

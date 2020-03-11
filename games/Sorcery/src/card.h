#ifndef CARD_H
#define CARD_H
#include <string>
#include <memory>
#include "CType.h"
#include "cardbase.h"
#include "inquiry/inquiryablecard.h"
class Ritual;
class Minion;
class Player;
class Game;

class Card: public InquiryableCard{
	protected:
    const CardBase &base;
    bool inplay;
	int cost;
	int master;

	public:
	Card(const CardBase &base, int master);
    Card(const CardBase &base);
	virtual ~Card();
	Card(const Card &);
    Card(Card &&);

    virtual Card& operator=(Card &&);
    virtual Card& operator=(const Card &);

	//Getters and Setters:
	virtual const std::string &getName() const;
	virtual const std::string &getDesc() const;
	virtual int getCost() const;

    //Returning nullptr means the result card now owns the other card;

    // __        ___    ____  _   _ ___ _   _  ____ 
    // \ \      / / \  |  _ \| \ | |_ _| \ | |/ ___|
    //  \ \ /\ / / _ \ | |_) |  \| || ||  \| | |  _ 
    //   \ V  V / ___ \|  _ <| |\  || || |\  | |_| |
    //    \_/\_/_/   \_\_| \_\_| \_|___|_| \_|\____|
    // FIXME(WARNING): You must *TRUE* if the in cast if
    // if the ownership changes.
    virtual bool cast(std::unique_ptr<Minion> &min, Player &player, Game &game);
    virtual bool cast(std::unique_ptr<Ritual> &ritual, Player &player, Game &game);

    virtual bool cast(Game &game);
	virtual int getMaster() const; //does this need to be virtual?

    //inquiry
    virtual const CardInquiry inquiry() const override =0;

    //Duplication of card
    virtual std::unique_ptr<Card> copy() const = 0;
    
	void setCost(int c);
	void setMaster(int p);
	void setInplay(bool inplay);

    //requires targets to played on the board
    virtual bool requires_target();

	//Pure Virutal Functions for Children:
	virtual void prettyprint() = 0;
	virtual const CType getType() const = 0;    //enum that stores all card info

//	virtual std::string getName() const = 0; //Keeping this P.V. to make Card ABS
};

struct CardCannotCast{
    Card &card;
};

struct CardCannotCastOnTarget{
    Card &card;
    Card &target;
};
#endif

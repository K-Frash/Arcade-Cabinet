#include "spell.h"

#include <memory>
#include <utility>
#include <iostream>

class Minion;
class Player;

// Note: error throwing for an invalid minion is handled in game

// Destroy target minion or ritual
class Banish : public Spell {
public:
	Banish(const CardBase &base) : Spell{base} {}
	
	std::unique_ptr<Card> copy() const override;

	bool cast(std::unique_ptr<Minion> &minion, Player &player, Game &game) override;
	bool cast(std::unique_ptr<Ritual> &ritual, Player &player, Game &game) override;
};

// Put target minion on the bottom of its owner's deck
class Unsummon : public Spell {
public:
	Unsummon(const CardBase &base) : Spell{base} {}	

	std::unique_ptr<Card> copy() const override;

	bool cast(std::unique_ptr<Minion> &minion, Player &player, Game &game) override;
};

// Add 3 charges to your ritual
// Throws an error if you do not have a ritual
class Recharge : public Spell {
public:
	Recharge(const CardBase &base) : Spell{base} {}

	std::unique_ptr<Card> copy() const override;

	bool cast(std::unique_ptr<Ritual> &ritual, Player &player, Game &game) override;
};

// Destroy the top enchantment on target minion
// Throws an error if called on a minion with no enchantments
class Disenchant : public Spell {
public:
	Disenchant(const CardBase &base) : Spell{base} {}

	std::unique_ptr<Card> copy() const override;
	
	bool cast(std::unique_ptr<Minion> &minion, Player &player, Game &game) override;
};

// Resurrect the top minion in your graveyard (std::move to board)
// Throws an error if the graveyard is empty
// Throws an error if there is no room for new minions
// Note: you == game.activePlayer
class RaiseDead : public Spell {
public:
	RaiseDead(const CardBase &base) : Spell{base} {}

	std::unique_ptr<Card> copy() const override;
	
	bool cast(Game &game) override;
};

// Do 2 damage to all minions
class Blizzard : public Spell {
public:
	Blizzard(const CardBase &base) : Spell{base} {}

	std::unique_ptr<Card> copy() const override;
	
	bool cast(Game &game) override;
};

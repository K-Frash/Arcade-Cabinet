#include "cardcatalog.h"
#include "minion.h"
#include "cards/darkritual.h"
#include "cards/auraofpower.h"
#include "cards/standstill.h"
#include "ability/damageonplay.h"
#include "ability/summon.h"
#include "ability/damagetarget.h"
#include "ability/healonstart.h"
#include "ritual.h"
#include "cardloader.h"
#include "enchantment.h"
#include "cards/spells.h"

std::map<std::string, CardBase> cardBase{
	//Minions
	{"Air Elemental", {"Air Elemental", 0, "", 1, 1}},
	{"Earth Elemental",{"Earth Elemental", 3, "", 4, 4}},
	{"Fire Elemental", {"Fire Elemental", 2,
				"Whenever an opponent's minion "
				"enters play, deal 1 damade to it.", 4, 4}},
	{"Potion Seller", {"Potion Seller", 2,
				"At the end of your turn, all your "
				"minions gain +0/+1.", 1, 3}},
	{"Novice Pyromance", {"Novice Pyromance", 1,
				"At the end of your turn, all your "
				"minions gain +0/+1.", 1, 3}},
	{"Apprentice Summoner", {"Apprentice Summoner", 1,
				"Summon a 1/1 air elemental", 1, 1}},
	{"Master Summoner", {"Master Summoner", 3,
				"Summon up to thee 1/1 air elementals", 2, 3}},
		//Spells
	{"Banish", {"Banish", 2, "Destroy target minion or ritual"}},
	{"Unsummon", {"Unsummon", 1,
				"Put target minion on the bottom of its owner's deck"}},
	{"Recharge", {"Recharge", 1,
				"Your ritual gains 3 charges"}},
	{"Disenchant", {"Disenchant", 1,
				"Destroy the top enchantment on target minion"}},
	{"Raise Dead", {"Raise Dead", 1,
				"Ressurect the top minion in your graveyard"}},
	{"Blizzard", {"Blizzard", 3,
				"Deal 2 damage to all minions"}},

		//Enchantments
	{"Giant Strength", {"Giant Strength", 1, "" ,2, 2}},
	{"Magic Fatigue", {"Magic Fatigue", 0,
				"Enchanted minion's activated ability costs 2 more"}},
	{"Silence", {"Silence", 1,
				"Enchanted minion cannot use abilities"}},

		//Rituals
	{"Dark Ritual", {"Dark Ritual", 0,
				"At the start of your turn, gain magic"}},
	{"Aura of Power", {"Aura of Power", 1,
				"Whenever a minion enters play under "
				"your control, it gains +1/+1"}},
	{"Standstill", {"Standstill", 3,
				"Whenever a minion enters play under"
				"destroy it."}},
};

std::unique_ptr<const Card> &CardCatalog::operator[](const std::string &name){
	if (cards.count(name) == 0){
		throw CardLoader::CardNotFoundException{name};
	}
	return cards[name]; 
}

DamageOnPlay fireElementalAbility{};
Ability nullAbility{};
HealOnStart healAbility{};
DamageOnTarget fireBall{};
Summon summon1el{1,1,"Air Elemental"};
Summon summon3el{2,3,"Air Elemental"};

CardCatalog::CardCatalog(){
    #define addcard(name, type, ...) cards.emplace(name, \
		std::make_unique<type>(cardBase[name], ##__VA_ARGS__));
	addcard("Air Elemental", Minion, nullAbility);
	addcard("Fire Elemental", Minion, fireElementalAbility);
	addcard("Potion Seller", Minion, healAbility);
	addcard("Novice Pyromance", Minion, fireBall);
	addcard("Apprentice Summoner", Minion, summon1el);
	addcard("Master Summoner", Minion, summon3el);
	addcard("Master Fatigue", Enchantment,nullAbility);
	addcard("Giant Strength", Enchantment,nullAbility);
	addcard("Silence", Enchantment,nullAbility);
	addcard("Dark Ritual", DarkRitual, 5, 1);
	addcard("Aura of Power", AuraofPower, 4, 1);
	addcard("Standstill", StandStill, 4, 2);
	addcard("Banish", Banish);
	addcard("Unsummon", Unsummon);
	addcard("Recharge", Recharge);
	addcard("Disenchant", Disenchant);
	addcard("Raise Dead", RaiseDead);
	addcard("Blizzard", Blizzard);
}

CardCatalog CARD_CATALOG{};

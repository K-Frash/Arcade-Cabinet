#ifndef CARD_LOADER_H
#define CARD_LOADER_H

#include "card.h"

#include <deque>
#include <string>


namespace CardLoader {

	struct InvalidCardException{
		std::string cardName;
	};

	struct CardNotFoundException{
		std::string cardName;
	};

	struct DeckNotFoundException{
		std::string deckFilePath;
	};

	void loadDefaultDeck(std::deque<std::unique_ptr<Card>> &deck);
	
	void loadDeck(std::deque<std::unique_ptr<Card>> &deck, const std::string &path);

}

#endif

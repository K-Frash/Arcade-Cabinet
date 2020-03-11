#include "cardloader.h"
#include "cardcatalog.h"

#include <deque>
#include <string>
#include <fstream>
#include <memory>
#include <iostream>

using std::deque;
using std::string;
using std::ifstream;
using std::unique_ptr;

const string DEFAULT_DECK_PATH = "assets/default.deck";

void CardLoader::loadDefaultDeck(deque<unique_ptr<Card>> &deck){
	CardLoader::loadDeck(deck, DEFAULT_DECK_PATH);
}

void CardLoader::loadDeck(deque<unique_ptr<Card>> &deck, const string &path){
	deck.clear();
	
	ifstream deckFile{path};
	if(deckFile.fail()){
		throw DeckNotFoundException{path};
	}
	
	string cardName;
	while(getline(deckFile, cardName)){
	        try{
        	    deck.emplace_back(CARD_CATALOG[cardName]->copy());
	        }catch(CardLoader::CardNotFoundException &e){
			//TODO print error            	
       		}
	}

}

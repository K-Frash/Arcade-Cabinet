#include "player.h"
#include "card.h"
#include "cardloader.h"
#include "game.h"

#include <string>
#include <deque>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

#include "PRNG.h"
#include <ctime>

#include "testing.h"

#include "cardcatalog.h"
#include "textdisplay/textdisplay.h"
using namespace std;


ifstream init;

//Reads input from init then cin until it finds a non-empty
// and sets it in line returns false if we hit end of line in cin.
bool getaline(string &line){
	line.clear();
	while(line.empty()){
		if (init){
			getline(init, line);
			if (init) cout << line << endl;
		}else{
			if(cin.eof()){ // EOF can only be sent by cin (file will defer)
				// So this is Ctrl+D or input redirection
				return false;
			}
			// else if(cin.fail()){ // Can this happen?
			//     cout << "Input failed! Exiting..." << endl;
			//     return 1;
			// }
			getline(cin, line); //getline after since getline will
			//trigger eof if eof occours on line of input
		}
	}
	return true;
}

int main(int argc, char** argv){

	//-- Initialize Globals: --//
	//Tempoary Display for now
	TextDisplay tdisplay{cout};

	// Set RNG seed
	uint32_t seed = time(0);
	prng.seed(seed);

	// Parse command line arguments
	deque<unique_ptr<Card>> deck1, deck2;
	bool deck1set = false, deck2set = false;

	for(int i = 0; i < argc; ++i){

		string arg = argv[i];

		// Flags are organized alphabetically
		if (arg == "-deck1" || arg == "-deck2"){

			deque<unique_ptr<Card>> &deckRef = (arg == "-deck1" ? deck1 : deck2);

			// Note: Default decks are set after CL arg parsing using deck<#>set flags

			if(i + 1 == argc){
				cout << "No argument passed to " << arg << "!" << endl;
				break;
			}

			++i;
			string path = argv[i];
			try {
				CardLoader::loadDeck(deckRef, path);
				(arg == "-deck1" ? deck1set : deck2set) = true; //Set deck<#>set flag
			} catch(CardLoader::DeckNotFoundException &dnfe){
				cout << "No deck found at " << dnfe.deckFilePath 
					<< " for " << arg << " argument." << endl;
			}

		} else if (arg == "-init"){

			if (i + 1 == argc){
				cout << "No argument passed to " << arg << "! Reading from stdin..." << endl;
				break;
			}

			++i;
			string path = argv[i];
			init = ifstream{path};
			if(init.fail()){
				cout << "Init file failed immediately: not found or invalid. Reading from stdin..." << endl;
			}

		} else if(arg == "-testing") {

			Testing::testing = true;

		}

	}

	// Load default decks if decks weren't set
	if (!deck1set){
		cout << "Using default deck for Player 1." << endl;
		CardLoader::loadDefaultDeck(deck1);
	}
	if (!deck2set){
		cout << "Using default deck for Player 2." << endl;
		CardLoader::loadDefaultDeck(deck2);
	}

	// Now read the player names

	string name1, name2;
	cout << "What is player 1's name?" << endl;
	getaline(name1);
	cout << "What is player 2's name?" << endl;
	getaline(name2);

	// Create the game (and player) objects
	Game game(Player{name1, move(deck1)},
			Player{name2, move(deck2)});

	// Now Start the gameloop
	string input_line;
	string cmd;
	istringstream line;

	while(!game.over()){
		cout << "┌─[Player" << game.getPlayerNumber(game.getActivePlayer()) << "("
			<< game.getActivePlayer().getName() << ")]" << std::endl; // Prompt
		cout << "└─>";
		if(!getaline(input_line)) return 0;
		istringstream line{input_line};
		line >> cmd;

		if(cmd == "help"){

			//Ideally this would be dynamic, but haven't the time
			cout << "Commands:\n"
				<< "\thelp -- Display this message.\n"
				<< "\tend -- End the current player's turn.\n"
				<< "\tquit -- End the game.\n"
				<< "\tattack minion other-minion -- Orders minion to attack other-minion.\n"
				<< "\tattack minion -- Orders minion to attack the opponent.\n"
				<< "\tplay card [target-player target-card] -- Play card, optionally targeting target-card owned by target-player.\n"
				<< "\tuse minion [target-player target-card] -- Use minion's special ability, optionally targeting target-card owned by target-player.\n"
				<< "\tinspect minion -- View a minion's card and all enchantments on that minion.\n"
				<< "\thand -- Describe all cards in your hand.\n"
				<< "\tboard -- Describe all cards on the board." << endl;
			//Fun fact: endl flushes the buffer, \n doesn't

		} else if (cmd == "end"){
			// ends the current players turn
			game.endTurn();

		} else if (cmd == "quit"){
			// ends the game immediately with no winner (same as EOF)
			return 0;

		} else if (cmd == "draw"){
			if (!Testing::testing) continue;
			game.getActivePlayer().drawCard();

		} else if (cmd == "discard"){
			if (!Testing::testing) continue;
			unsigned int index;

			if(!(line >> index)){
				cout << "Index to discard wasn't a valid number!" << endl;
				continue;
			};

			try {
				game.getActivePlayer().discardCard(index - 1);
			} catch (CardOutOfRange &e){
				cout << "FAILED> Player(" << e.playername << "): Does not have a card in "
					<< e.location() << " at index: " << e.index << std::endl;
			}
		} else if (cmd == "attack"){
			unsigned int i;
			unsigned int j;
			line >> i;
			if(line >> j){
				try{
					game.Attack(i-1,j-1);
				}
				catch(CardOutOfRange &e){
					std::cout << "Player(" << e.playername << "): Does not have a minion in slot " << j << std::endl;
				}
			}
			else{
				game.Attack(i-1);
			}
			game.checkDead();
		} else if (cmd == "play"){
			unsigned int i,p,j;
			char r;
			line >> i;
			try{
				if (line>>p){
					if(line>>j){ //read in an integer
						game.play(i - 1, p ,j -1); //TODO What if target is ritual?: "r"
					}
					else if(line >> r){ //read in a ritual
						if(r == 'r'){
			//				std::cout << "spell on ritual used" << endl; //for testing!
							game.play(i-1,p);
						}
						else std::cout << "invalid input!" << endl;
					}
				}
				else{
					game.play(i - 1);
				}
			}catch(CardOutOfRange &e){
				cout << "FAILED> Player(" << e.playername << "): Does not have a card in "
					<< e.location() << " at index: " << e.index << std::endl;
			}catch(CardCannotCastOnTarget &e){
				cout << "FAILED> " << e.card.getName() << " can not be played on " << e.target.getName()
					<< std::endl;
			}catch(CardCannotCast &e){
				cout << "FAILED> " << e.card.getName() << " can not be played without target."
					<< std::endl;
			}
			game.checkDead();

		} else if (cmd == "use"){
			unsigned int i,p,j;
			char r;
			line >> i;
			try{
				if (line>>p){
					if(line>>j){ //read in an integer
						game.useAbility(i - 1, p ,j -1); //TODO What if target is ritual?: "r"
					}
					else if(line >> r){ //read in a ritual
						if(r == 'r'){
			//				std::cout << "spell on ritual used" << endl; //for testing!
							game.useAbility(i-1,p);
						}
						else std::cout << "invalid input!" << endl;
					}
				}
				else{
					game.useAbility(i - 1);
				}
			}catch(CardOutOfRange &e){
				cout << "FAILED> Player(" << e.playername << "): Does not have a card in "
					<< e.location() << " at index: " << e.index << std::endl;
			}catch(CardCannotCastOnTarget &e){
				cout << "FAILED> " << e.card.getName() << " can not be played on " << e.target.getName()
					<< std::endl;
			}catch(CardCannotCast &e){
				cout << "FAILED> " << e.card.getName() << " can not be played without target."
					<< std::endl;
			}
			game.checkDead();
		} else if (cmd == "inspect"){
			uint i;
			if (line >> i){
				tdisplay.inspectCard(game.inspect(i-1));
			}else{
				cout << "FAILED> " << "invalid inspect";
			}
		} else if (cmd == "hand"){
			tdisplay.displayHand(game.getActivePlayer().inquiry());
		} else if (cmd == "board"){
			tdisplay.displayBoard(game.inquiry());		
		} else {
			cout << "Input not recognized as a valid command." << endl;
		}



	}

	// Someone actually won, the madman
	cout << "Player " << game.getWinner().getName() << " won the game!" << endl;

	return 0;
}






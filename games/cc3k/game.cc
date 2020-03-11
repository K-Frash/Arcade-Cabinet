#include "game.h"
#include <string>
#include <iostream>
#include <map>
#include <limits>
#include <fstream>
#include "entity.h"
#include "animate.h"
#include "tile.h"
#include "hero.h"
#include "enemy.h"
#include "neutral.h"
#include "inanimate.h"
#include "player.h"
#include "window.h"
#include "level.h"
#include <stdlib.h>
#include <sstream>

// converts a char c into an Entity based on mapping defined in txt file
Entity* Game::getResource(char c) {  
	std::pair<int, int> resourceMapping = resourceMap[c];
	Entity* e;
	if (resourceMapping.first==1) {
		e = new Enemy(Enemies[resourceMapping.second]);
	}
	else if (resourceMapping.first==2) {
		e = new Neutral(Neutrals[resourceMapping.second]);
	}
	else if (resourceMapping.first==3) {
		e = new Inanimate(Items[resourceMapping.second]);
	}
	return e;
}

// picks a random enemy (probability distribution is guaranteed based on the ProbabilityList generation method)
Entity* Game::getRandomEnemy() {
	Entity* e;
	Entity* randomChoice = enemyProbabilityList[rand()%enemyProbabilityList.size()];
	if (randomChoice->getName()=="Merchant"){ // Merchants are enemies based on game logic but designed as an inherited class of enemy 
		Neutral* nRandomChoice = dynamic_cast<Neutral*>(randomChoice);
		e = new Neutral(*nRandomChoice);	
	}
	else {
		Enemy* eRandomChoice = dynamic_cast<Enemy*>(randomChoice);
		e = new Enemy(*eRandomChoice);
	}
	
	return e; // the assumption here is that the first 6 items in file were potions and only 6 potions exist

}


// picks a random potion (probability distribution is guaranteed based on the ProbabilityList generation method)
Entity* Game::getRandomPotion() {
	Entity* e;
	e = new Inanimate(*(potionProbabilityList[rand()%potionProbabilityList.size()]));
	return e; // the assumption here is that the first 6 items in file were potions and only 6 potions exist
}


// picks a random gold (probability distribution is guaranteed based on the ProbabilityList generation method)
Entity* Game::getRandomGold() { 
	Entity* e;
	e = new Inanimate(*(goldProbabilityList[rand()%goldProbabilityList.size()]));
	return e; // the assumption here is that the first 6 items in file were potions and only 6 potions exist
}

// parses a txt file to generate  master copies of items (gold and potions)
void Game::loadItem(std::string fName) {
	std::ifstream f;
	f.open(fName.c_str());
	f.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore first line
	std::string resourceName;
	int hp;
	int atk;
	int def;
	bool collision;
	bool attackable;
	bool consumable;
	bool takable;
	int id;
	std::string name;
	bool mystery;
	char rSymbol;
	char dSymbol;
	bool hostility;
	bool moveable;
	int gold;
	int probability; 	// this is how many times for the item to appear in the probability list, so the probability of this object being picked at random is
						// probability / sum(probabilities of objects in same category)
	while(f >> resourceName >> hp >> atk >> def >> collision >> attackable >> consumable >> takable >> id >> name >> mystery >> rSymbol >> dSymbol >> hostility >> moveable >> gold >> probability) {
		Items.insert(std::pair<int, Inanimate>(id, Inanimate(hp, atk, def, collision, attackable, consumable, takable, id, name, mystery, dSymbol, hostility, moveable, gold)));
		resourceMap.insert(std::pair<char, std::pair<int, int> >(rSymbol, std::pair<int, int>(3, id)));
		if (Items[id].getName()!="Gold") {
			for (int i=0; i<probability; i++) {
				potionProbabilityList.push_back(&Items[id]);
			}
		}
		else {
			for (int i=0; i<probability; i++) {
				goldProbabilityList.push_back(&Items[id]);
			}
		}
	}
}

// parses a txt file to generate  master copies of enemies excluding merchant
void Game::loadEnemy(std::string fName) {
	std::ifstream f;
	f.open(fName.c_str());
	f.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore first line
	std::string resourceName;
	int hp;
	int atk;
	int def;
	bool collision;
	bool attackable;
	bool consumable;
	bool takable;
	int id;
	std::string name;
	bool mystery;
	char rSymbol;
	char dSymbol;
	bool hostility;
	bool moveable;
	bool negateHarmfulPotions;
	int gold;
	int probability;
	while(f >> resourceName >> hp >> atk >> def >> collision >> attackable >> consumable >> takable >> id >> name >> mystery >> rSymbol >> dSymbol >> hostility >> moveable >> negateHarmfulPotions >> gold >> probability) {
		Enemies.insert(std::pair<int, Enemy>(id, Enemy(hp, atk, def, collision, attackable, consumable, takable, id, name, mystery, dSymbol, hostility, moveable, negateHarmfulPotions, gold)));
		resourceMap.insert(std::pair<char, std::pair<int, int> >(rSymbol, std::pair<int, int>(1, id)));
		for (int i=0; i<probability; i++) {
			enemyProbabilityList.push_back(&Enemies[id]);
		}
	}
}

// same as above but for Neutrals (merchant)
void Game::loadNeutral(std::string fName) {
	std::ifstream f;
	f.open(fName.c_str());
	f.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore first line
	std::string resourceName;
	int hp;
	int atk;
	int def;
	bool collision;
	bool attackable;
	bool consumable;
	bool takable;
	int id;
	std::string name;
	bool mystery;
	char rSymbol;
	char dSymbol;
	bool hostility;
	bool moveable;
	bool negateHarmfulPotions;
	int gold;
	int probability;
	while(f >> resourceName >> hp >> atk >> def >> collision >> attackable >> consumable >> takable >> id >> name >> mystery >> rSymbol >> dSymbol >> hostility >> moveable >> negateHarmfulPotions >> gold >> probability) {
		Inanimate* i = new Inanimate(0, 0, 0, false, false, false, true, 999, "Merchant Horde", false, 'G', 0, 0, gold);
		Neutrals.insert(std::pair<int, Neutral>(id, Neutral(hp, atk, def, collision, attackable, consumable, takable, id, name, mystery, dSymbol, hostility, moveable, negateHarmfulPotions, 0/*gold*/, i/*the gold it will drop*/)));
		resourceMap.insert(std::pair<char, std::pair<int, int> >(rSymbol, std::pair<int, int>(2, id)));
		for (int i=0; i<probability; i++) {
			enemyProbabilityList.push_back(&Neutrals[id]);
		}
	}
}

// same as above but for races (Hero class)
void Game::loadHero(std::string fName) {
	std::ifstream f;
	f.open(fName.c_str());
	f.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore first line
	std::string resourceName;
	int hp;
	int atk;
	int def;
	bool collision;
	bool attackable;
	bool consumable;
	bool takable;
	int id;
	std::string name;
	bool mystery;
	char rSymbol;
	char dSymbol;
	bool hostility;
	bool moveable;
	float goldMultiplier;
	float scoreMultiplier;
	bool negateHarmfulPotions;
	while(f >> resourceName >> hp >> atk >> def >> collision >> attackable >> consumable >> takable >> id >> name >> mystery >> rSymbol >> dSymbol >> hostility >> moveable >> goldMultiplier >> scoreMultiplier >> negateHarmfulPotions) {
		Races.insert(std::pair<int, Hero>(id, Hero(hp, atk, def, collision, attackable, consumable, takable, id, name, mystery, dSymbol, hostility, moveable, goldMultiplier, scoreMultiplier, negateHarmfulPotions, resourceName)));
		resourceMap.insert(std::pair<char, std::pair<int, int> >(rSymbol, std::pair<int, int>(0, id)));
	}
}

// determines what needs to be loaded
void Game::loadAssets() {
	loadEnemy("enemy.txt");
	loadItem("item.txt");
	loadHero("hero.txt");
	loadNeutral("neutral.txt");

}

// ctor when using saved game
Game::Game(char* customFileName, bool useGraphics): useCustomLevels(true), player(NULL), level(NULL), onLevel(1), maxLevel(5), state(0) {
	this->customFileName = std::string(customFileName);
	// graphics is done with xwindow, no graphics is printed to standard out, never finished so both are console windows
	window = useGraphics ? new ConsoleWindow(): new ConsoleWindow();
	loadAssets();
}

// ctor when random generation is going to be used
Game::Game(bool useGraphics): useCustomLevels(false), player(NULL), level(NULL), onLevel(1), maxLevel(5), state(0) {
	// graphics is done with xwindow, no graphics is printed to standard out, never finished so both are consolewindows
	window = useGraphics ? new ConsoleWindow(): new ConsoleWindow();
	loadAssets();
}

Game::~Game() {
	delete window;
	delete level;
	delete player;
	Neutrals[1].freeSharedResources(); // release the shared treasure and hostility boolean of merchant, if it was more than just merchant we would need to iterate through the map and do this for each
}


// player picks a race to start game or quit
void Game::createPlayer() {
	std::string message = "Select a race:\n";
	int messageLength = 1;
	for (std::map<int, Hero>::iterator it=Races.begin(); it!=Races.end(); ++it) {
		std::stringstream ss;
		std::string temp;
		ss << "(" << (char)tolower(it->second.getRace()[0]) << ")" << it->second.getRace() << "\n";
		std::getline(ss, temp);
		message += temp + "\n";
		messageLength++;
	}
	message += "or (q) quit\n";
	messageLength++;
    window->drawSpecialMessageScreen(message, messageLength); // window output displays choices for player to pick from
	char PCRaceChoice;
	std::cin >> PCRaceChoice;
	if (PCRaceChoice!='q' && std::cin.good()) { // undefined behaviour when picking a race that doesn't exist
		std::pair<int, int> resourceMapping = resourceMap[PCRaceChoice];
		Hero* h = new Hero(Races[resourceMapping.second]);
		player = new Player(h);
	}
	else { // q or EOF
		quit();
	}
}

Entity* Game::getPC() {
	return player->getHero();
}

Hero* Game::getPCHero(){
	return player->getHero();
}

void Game::newLevel() {
	if (useCustomLevels) {
		level = new Level(this, customFileName ,onLevel);
	}
	else {
		level = new Level(this, "genericfloor.txt");
	}
}

void Game::advanceLevel() {
	onLevel++;
	if (onLevel > maxLevel) { // game completed
		std::stringstream ss;
		std::string message;
		ss << "Game completed with score of " << player->getScore();
		std::getline(ss, message);
		message += ".\n (r)estart or (q)uit\n";
		window->drawSpecialMessageScreen(message, 2);
		state = 3;
	}
	else {
		delete level;
		getPCHero()->resetBonuses();
		getPCHero()->getOffStairs(); 
		newLevel();
	}
}

void Game::start() {
	createPlayer();
	if (state==4) { // state becomes 4 if user decides to quit
		return;
	}
	newLevel();
	state = 1;
}

void Game::restart() {
	delete level;
	level = NULL;
	delete player;
	player = NULL;
	state = 0;
}

void Game::quit() {
	state = 4;
}

void Game::restartOrQuit() {
	std::string playerDecision;
	std::cin >> playerDecision;
	if (playerDecision=="r") {
		state = 5;
	}
	else { // q and invalid input
		state = 4;
	}
}

void Game::updateScreen() {
	WindowUpdateMessage m;
	m.hp = getPCHero()->getHp();
	m.atk = getPCHero()->getAttack();
	m.def = getPCHero()->getDef();
	m.race = getPCHero()->getRace();
	m.action = getPCHero()->getAction();
	m.floorNum = onLevel;
	m.gold = getPCHero()->getGold();
	window->draw(level->reportLevel(), m); // tell window to display information
}

// determine action based on game's sate
bool Game::loop() {
	std::string moved;
	std::string command;
	switch (state) {
		case 0: // player set up needs to occur and start game
			srand(48754); // placement of seed here ensures same action even when restarting
			start();
			if (state==4){
				break;
			}
			updateScreen();
			break;
		case 1: // player is playing on a level, normal game state
			std::cin>>command;
			if (command=="u"){
				player->consume();
			}
			else if (command=="a"){
				player->attack();
			}
			else if (command=="r") {
				state = 5;
				break;
			}
			else if (command=="q") {
				state = 4;
				break;
			}
			else {
				player->move(command);
			}
			if (getPCHero()->isOnStairs()) {
				state = 2;	
				break;
			}
			level->takeTurn();
			if (player->isDead()) { // end of each turn check if player is dead
				state = 3;
				std::stringstream ss;
				std::string message;
				ss << "Game over with score of " << player->getScore();
				std::getline(ss, message);
				message += ".\n (r)estart or (q)uit\n";
				window->drawSpecialMessageScreen(message, 2);
				break;
			}
			updateScreen();
			break;
		case 2: // player completes a level
			state = 1;
			advanceLevel(); // can change state to 4/5
			if (state==1){
				updateScreen();
			}
			break;
		case 3: // PC dies or completes game
			restartOrQuit();
			break;
		case 4: // quit
			quit();
			return false;
			break;
		case 5: // restart
			restart();
			break;
		default :
			break;
	}
	return true;
}
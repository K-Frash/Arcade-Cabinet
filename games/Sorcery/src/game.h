#ifndef GAME_H
#define GAME_H

#include "player.h"

struct GameInquiry;

class Game{
	//TODO: Game TODO evaluate whether this comment is still necessary?

	Player player1;
	Player player2;
	Player* activePlayer;

	void triggerTurnEnd();
	void triggerTurnStart();
	public:
	Game(Player player1, Player player2);

	Player& getActivePlayer();	
	Player& getNonactivePlayer();

	int getPlayerNumber(Player& player);

	InquiryableCard *inspect(unsigned int i);
	void play(unsigned int i);
	void play(unsigned int i, int player, unsigned int j);
	void play(unsigned int i, int player);

	void useAbility(unsigned int i);
	void useAbility(unsigned int i, int player);
	void useAbility(unsigned int i, int player, unsigned int j);

	void endTurn();

	const GameInquiry inquiry();
	
	bool over() const;
	const Player& getWinner() const; //Invalid to call if over() == false

	void checkDead();

	void triggerMinionPlay(Minion &minion, Player &player);
	//-----ATTACKS------
	void Attack(unsigned int i, unsigned int j);
	void Attack(unsigned int i);

};

#endif

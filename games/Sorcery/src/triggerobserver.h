#ifndef __TRIGGEROBSERVER_H_
#define __TRIGGEROBSERVER_H_

class Game;
class Player;
class Minion;
class TriggerObserver{
public:
	virtual void onMinionETB(Minion &minion, Player &player, Game &game);
	virtual void onTurnStart(Game &game);
	virtual void onTurnEnd(Game &game);
};

#endif // __TRIGGEROBSERVER_H_

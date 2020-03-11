#ifndef __WINDOW_H__
#define __WINDOW_H__
#include <vector>
#include <string>
#include "tile.h"

struct WindowUpdateMessage {
		std::string race;
		int gold;
		int hp;
		int atk;
		int def;
		std::string action;
		int floorNum;
};

class Window {
	virtual void drawTile(Tile*)=0;
	virtual void drawStatus(WindowUpdateMessage)=0;
	public:
		void draw(std::vector<std::vector<Tile*> >, WindowUpdateMessage);
		virtual void drawSpecialMessageScreen(std::string, int)=0;
};

class ConsoleWindow : public Window {
	void drawTile(Tile*);
	void drawStatus(WindowUpdateMessage);
	public:
		virtual void drawSpecialMessageScreen(std::string, int);
};
#endif
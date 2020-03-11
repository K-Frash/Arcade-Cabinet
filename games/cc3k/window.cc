#include <iostream>
#include <vector>
#include "window.h"
#include "level.h"
#include "tile.h"

// draw each tile and the status mesage
void Window::draw(std::vector<std::vector<Tile*> > tiles, WindowUpdateMessage m) {
	for(std::vector<std::vector<Tile*> >::iterator it = tiles.begin(); it != tiles.end(); ++it) {
		for(std::vector<Tile*>::iterator it2 = it->begin(); it2!=it->end(); ++it2) {
			drawTile(*it2);
		}
		std::cout << std::endl;
	}
	drawStatus(m);
}

// ConsoleWindow implementation of drawing a tile
void ConsoleWindow::drawTile(Tile* t) {
	std::cout << t->getSymbol();
}

// ConsoleWindow implementation of drawing the message
void ConsoleWindow::drawStatus(WindowUpdateMessage m) {
	std::cout << "Race: " << m.race << " " << "Gold: " << m.gold << "               " << "Floor: " << m.floorNum << std::endl;
	std::cout << "HP: " << m.hp << std::endl;
	std::cout << "ATK: " << m.atk << std::endl;
	std::cout << "DEF: " << m.def << std::endl;
	std::cout << "Action: " << m.action << std::endl; 
}


// use to print a block fo text to the screen, capable of making messages larger than "dimensions" of screen
void ConsoleWindow::drawSpecialMessageScreen(std::string s, int numLines) {
	int firstHalf = numLines/2;
	int lastHalf = numLines/2;
	if (numLines%2==1) {
		lastHalf++;
	}
	for (int i=0; i<15 - firstHalf; i++) {
		std::cout << std::endl;
	}
	std::cout << s;
	for (int i=0; i<15 - lastHalf; i++) {
		std::cout << std::endl;
	}
}
#include "game.h"

using namespace std;

int main(int argc, char *argv[]) {
	Game* game;
	if (argc==2) { // assume only file name should be passed as CL argument
		 game = new Game( argv[1], false); // uses pre-generated level file.
		// file must contain at least 5 correctly formatted levels (only first 5 will be used)
		// game will crash if file does not exist or there is not enough levels.
	}
	else {
		game = new Game(false); // uses random generation based on static file.
	}
	while(game->loop()) {
		// game input handled in Game class.
	}
	delete game;
	return 0;
}
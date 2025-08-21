#include <Game.h>


int main() {
	
	Game g;
	
	GameState state;

	do {
		state = g.run();

		if (state == GameState::RESTART) {
			g.reset();
		}


	} while (state == GameState::RESTART);


	return 0;
}

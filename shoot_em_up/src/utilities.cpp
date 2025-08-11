#include "utilities.h"
#include "Player.h"

WINDOW* create_window(int height, int width, int posy, int posx) {

	WINDOW* local_win = newwin(height, width, posy, posx);

	box(local_win, 0, 0);
	wrefresh(local_win);

	return local_win;
}

void destroy_window(WINDOW* local_win) {

	wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
	wrefresh(local_win);
	delwin(local_win);
}

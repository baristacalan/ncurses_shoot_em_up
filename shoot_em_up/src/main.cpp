#include <Game.h>


int main() {
	
	Game g;

	g.run();


	return 0;
}


//TEST
//int main() {
//    initscr();
//    keypad(stdscr, TRUE);
//    nodelay(stdscr, TRUE);   // or: timeout(50);
//    cbreak();
//    noecho();
//    curs_set(FALSE);
//
//    int height = 5, width = 10;
//    int posy = (LINES - height) / 2, posx = (COLS - width) / 2;
//
//    WINDOW* ship = newwin(height, width, posy, posx);
//    box(ship, 0, 0);
//    wrefresh(ship);
//
//    int ch = 0;
//    int last_key = -1;
//
//    while ((ch = getch()) != 27) {    // ESC to quit
//        if (ch != ERR) {              // only on actual keypress
//            last_key = ch;
//            switch (ch) {
//            case KEY_LEFT:
//
//                if (posx >= 0) {
//                    wborder(ship, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
//                    wrefresh(ship);
//                    delwin(ship);
//                    ship = newwin(height, width, posy, --posx);
//                    box(ship, 0, 0);
//                    wrefresh(ship);
//
//                }
//
//                break;
//            case KEY_RIGHT:
//
//                if (posx + width < COLS) {
//                    wborder(ship, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
//                    wrefresh(ship);
//                    delwin(ship);
//                    ship = newwin(height, width, posy, ++posx);
//                    box(ship, 0, 0);
//                    wrefresh(ship);
//
//                }
//                break;
//            }
//        }
//
//        mvprintw(0, 0, "Key Pressed: %d, X: %d, Y: %d   ", last_key, posx, posy);
//        refresh();
//    }
//
//    endwin();
//    return 0;
//}


// Old, working code.

//#include <curses.h>
//#include <iostream>
//#include <vector>
//
//void destroy_window(WINDOW* local_win);
//WINDOW* create_window(int height, int width, int posy, int posx);
//
//struct Bullet {
//	int y, x;
//	Bullet(int y_, int x_) : y(y_), x(x_) {}
//};
//
//
//
//std::vector<Bullet> bullets;
//
//struct Player
//{
//
//	int height{}, width, posy, posx;
//
//	bool is_alive{};
//
//	int score{};
//
//	WINDOW* ship{};
//
//	void fire() {
//		// one cell above the ship
//		bullets.emplace_back(posy - 1, posx + 0);
//		bullets.emplace_back(posy - 1, posx + width - 1);
//	}
//
//	void move_left() {
//
//		destroy_window(ship);
//		--this->posx;
//		ship = create_window(this->height, this->width, this->posy, this->posx);
//	}
//
//	void move_right()
//	{
//
//		destroy_window(ship);
//		++this->posx;
//		ship = create_window(height, width, posy, posx);
//	}
//
//
//	Player(int h, int w, int y, int x)
//		: height(h), width(w), posy(y), posx(x), score(0), is_alive(true)
//	{
//		ship = create_window(height, width, posy, posx);
//	}
//
//
//	~Player() {
//
//		destroy_window(ship);
//
//	}
//
//};
//
//
//
//
//void destroy_ship(Player* player);
//
//
//int main() 
//{
//
//	
//	int posx{}, posy{}, width{}, height{};
//	int ch{};
//
//	
//	initscr();
//	noecho();
//	curs_set(0);
//
//	cbreak(); 
//	
//	keypad(stdscr, true); 
//	
//	height = 5;
//	width = 10;
//	posy = LINES - height - 3;
//	posx = (COLS - width) / 2;
//
//	
//
//	Player* player = new Player(height, width, posy, posx);
//
//	
//	mvprintw(LINES/2, COLS/2, "Press F1 or ESC to exit");
//	refresh();
//	napms(2000);
//
//	clear();     
//	refresh();
//	box(player->ship, 0, 0);
//	wrefresh(player->ship);
//
//	
//
//	while (true) {
//		nodelay(stdscr, TRUE);
//		timeout(75);
//
//		int ch = getch();
//		if (ch == KEY_F(1) || ch == 27) break;
//
//		switch (ch) {
//		case KEY_LEFT:  player->move_left();  break;
//		case KEY_RIGHT: player->move_right(); break;
//		case ' ':       player->fire();       break;
//		}
//
//		for (auto it = bullets.begin(); it != bullets.end(); ) {
//			mvaddch(it->y, it->x, ' ');
//			--(it->y);
//			if (it->y < 0) {
//				it = bullets.erase(it);
//			}
//			else {
//				mvaddch(it->y, it->x, '|');
//				++it;
//			}
//		}
//
//		box(player->ship, 0, 0);
//		wrefresh(player->ship);
//		refresh();
//	}
//
//
//	delete player;
//
//	endwin();
//	return 0;
//}
//
//
//WINDOW* create_window(int height, int width, int posy, int posx) {
//	
//	WINDOW* local_win = newwin(height, width, posy, posx);
//	
//	box(local_win, 0, 0);
//	wrefresh(local_win);
//	
//	return local_win;
//}
//
//void destroy_window(WINDOW* local_win) {
//
//	wborder(local_win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
//	wrefresh(local_win);
//	delwin(local_win);
//}
//
//void destroy_ship(Player* player) {
//
//	destroy_window(player->ship);
//
//}
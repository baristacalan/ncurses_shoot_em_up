//Game::Game() : is_running{ true } {
//
//	// Buraya ayarlar vs eklenecek
//	initscr();
//    if (has_colors()) { start_color(); use_default_colors(); init_pair(1, COLOR_CYAN, -1); }
//	keypad(stdscr, true);
//	noecho();
//    cbreak();
//    nodelay(stdscr, true);
//    curs_set(0);
//
//    napms(350);
//
//    refresh();
//}
//
////void Game::run() {
////
////	napms(250);
////
////	int greet_length = mvprintw(LINES / 2, COLS / 2 - 10, "Press any button to start...");
////
////	refresh();
////
////	mvgetch(LINES / 2, COLS / 2 - 10 + greet_length);
////	move(LINES / 2, COLS / 2 - 11);
////
////
////	size = { 5, 10 };
////	position = { (LINES - (size.y + 3)) , (COLS - size.x) / 2 };
////
////	Player player(size.y, size.x, position.y, position.x);
////		
////	char c{};
////
////	clrtoeol();
////	//curs_set(0);
////	//nodelay(stdscr, true);
////	refresh();
////
////	while (is_running && ((c = getch()) != 27)) {
////
////		switch (c)
////		{
////
////		case KEY_LEFT:
////			player.move_left();
////			break;
////		case KEY_RIGHT:
////			player.move_right();
////			break;
////
////		}
////
////	}
////	refresh();
////
////}
//
//void Game::run() {
//    
//    int height = 5, width = 10;
//    int posy = LINES - (height + 3), posx = (COLS - width) / 2;
//
//    Player player(height, width, posy, posx);
//
//    int ch = 0;
//    int last_key = -1;
//
//    Points player_pos{};
//
//    while (((ch = getch()) != 27) && is_running) {
//        if (ch != ERR) {
//            last_key = ch;
//            switch (last_key) {
//            case KEY_LEFT:  player.move_left();  break;
//            case KEY_RIGHT: player.move_right(); break;
//            case ' ':       player.fire();       break;
//            }
//        }
//
//        update(player, 0);           
//        mvprintw(0, 0, "X:%d Y:%d  ",
//            player.get_position().x, player.get_position().y);
//        refresh();
//        napms(16);
//    }
//
//}
//
//
//void Game::update(Player& player, float dt) {
//    player.update_bullets();   // move and cull bullets every tick
//    // move enemies
//    // check bullet–enemy and enemy–player collisions
//    // clamp player position to screen
//    // handle cooldowns, animations, scores
//}
//
//
//
//
//Game::~Game() 
//{
//	is_running = false;
//	endwin();
//}

#include "Game.h"
#include <string.h>

namespace {
    void init_curses() {
        initscr();
        napms(300);
        if (has_colors()) { start_color(); use_default_colors(); init_pair(1, COLOR_CYAN, -1); }
        keypad(stdscr, true);
        noecho();
        cbreak();
        nodelay(stdscr, true);
        curs_set(0);
        refresh();
    }

    void handle_input(int ch, Player& p) {
        switch (ch) {
        case KEY_LEFT:  p.move_left();  break;
        case KEY_RIGHT: p.move_right(); break;
        case ' ':       p.fire();       break;
        default: break;
        }
    }

    void draw_hud(const Player& p) {
        auto pos = p.get_position();
        int shot_count = p.get_shoot_count();

        mvprintw(0, 0, "X:%d Y:%d  ", pos.x, pos.y);
        const char* shoot_count_str = "Shots count: ";
        size_t t = strlen(shoot_count_str);
        mvprintw(0, COLS - t - 10, "Shots count: %d", shot_count);
    }
} // namespace

Game::Game() : is_running(true) { init_curses(); }

void Game::run() {
    const int kFrameMs = 16;           // ~60 FPS
    const int h = 5, w = 10;
    const int y = LINES - (h + 3);
    const int x = (COLS - w) / 2;

    Player player(h, w, y, x);

    while (is_running) {
        int ch = getch();
        if (ch == 27) break;           // ESC
        if (ch != ERR) handle_input(ch, player);

        update(player, 0.0f);
        draw_hud(player);
        refresh();                     // HUD flush
        napms(kFrameMs);
    }
}

void Game::update(Player& player, float) {
    player.update_bullets();
}

Game::~Game() {
    is_running = false;
    endwin();
}



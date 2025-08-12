#include "Game.h"

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
        mvprintw(0, COLS - 23, "Shots count: %d", shot_count);
    }
} // namespace

Game::Game() : is_running(true) { init_curses(); }

void Game::run() {
    const int kFrameMs = 16;
    const int h = 5, w = 10;
    const int y = LINES - (h + 3);
    const int x = (COLS - w) / 2;

    Player player(h, w, y, x);

    while (is_running) {
        int ch = getch();
        if (ch == 27) break;
        if (ch != ERR) handle_input(ch, player);

        update(player, 0.0f);
        draw_hud(player);
        refresh();                     // HUD flush
        napms(kFrameMs);
    }
}

void Game::update(Player& player, float dt) {
    player.update_bullets();
}

Game::~Game() {
    is_running = false;
    endwin();
}

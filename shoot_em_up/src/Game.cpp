#include "Game.h"
#include <limits>

namespace {
    void init_curses() {
        
        initscr();
        napms(400);
        
        if (has_colors()) { 
            start_color(); 
            use_default_colors(); 
            init_pair(1, COLOR_CYAN, -1); 
            init_pair(2, COLOR_BLACK, COLOR_WHITE);
            init_pair(3, COLOR_RED, -1);
        }

        keypad(stdscr, true);
        noecho();
        cbreak();
        nodelay(stdscr, true);
        curs_set(0);
        refresh();
    }

    void process_input(int ch, Player& p) {
        switch (ch) {
        case KEY_LEFT:  p.move_left(4);  break;
        case KEY_RIGHT: p.move_right(4); break;
        case ' ':       p.fire();       break;
        default: break;
        }
    }

    void draw_hud(const Player& p) {
        auto pos = p.get_position();
        int shot_count = p.get_shoot_count();


        attron(COLOR_PAIR(2));
        mvprintw(0, 0, "X:%d Y:%d  ", pos.x, pos.y);
        attroff(COLOR_PAIR(2));

        attron(COLOR_PAIR(3));
        
        mvprintw(0, COLS - 23, "Shots count: %d", shot_count);
        attroff(COLOR_PAIR(3));
        
    }
    
    int rand_x(int w) {
        static std::mt19937 rng{ std::random_device{}() };
        std::uniform_int_distribution<int> dist(1, COLS - w - 1);
        return dist(rng);
    }

    bool check_collision(const Points& pos1, const Points& size1, const Points& pos2, const Points& size2) {
        // AABB collision detection
        // Check for overlap on both X and Y axes
        return (pos1.x < pos2.x + size2.x && pos1.x + size1.x > pos2.x &&
            pos1.y < pos2.y + size2.y && pos1.y + size1.y > pos2.y);
    }




} // namespace

void Game::process_collisions() {

    auto& bullets = player->get_bullets();

    for (auto it_enemy = enemies.begin(); it_enemy != enemies.end(); ) {
        bool enemy_destroyed = false;
        for (auto it_bullet = bullets.begin(); it_bullet != bullets.end(); ) {
            if (check_collision((*it_enemy)->get_position(), (*it_enemy)->get_size(), it_bullet->position_b, { 1, 1 })) {
                mvaddch(it_bullet->position_b.y, it_bullet->position_b.x, ' ');
                it_bullet = bullets.erase(it_bullet);
                it_enemy = enemies.erase(it_enemy);
                enemy_destroyed = true;
                break;
            }
            else {
                ++it_bullet;
            }
        }

        if (enemy_destroyed) continue;
 
        if (check_collision(player->get_position(), player->get_size(), (*it_enemy)->get_position(), (*it_enemy)->get_size())) {
            is_running = false; // Game Over!
            break; // Exit the loop, no need to check other enemies.
        }
        ++it_enemy;
    }



}

Game::Game() : is_running(true) { init_curses(); }

void Game::run() {
    const int kFrameMs = 16;
    const int h = 4, w = 8;
    const int y = LINES - (h + 1);
    const int x = (COLS - w) / 2;

    //Player player(h, w, y, x);
    this->player = std::make_unique<Player>(h, w, y, x, 1, 1);

    while (is_running) {
        int ch = getch();
        if (ch == 27) break;
        if (ch != ERR) process_input(ch, *player);

        update();
        draw_hud(*player);
        refresh();
        napms(kFrameMs);
    }
}

void Game::update() {


    player->update_bullets();
    //enemy.fall();
    //if ((frame % 60) == 0) enemies.emplace_back(std::make_unique<Enemy>(3, 6, 1, rand_x(6), 3));
    //Enemy::UpdateAll(enemies, 1);


    if ((frame % 30) == 0) {
        int ew = 3, eh = 3;
        enemies.emplace_back(std::make_unique<Enemy>(eh, ew, 1, rand_x(ew), 3, 0, 0));
    }

    // move enemies every 2 frames (slower fall). set to 1 for every frame.
    if ((frame % 3) == 0)
        Enemy::update_enemy(enemies, 2);

    process_collisions();

    ++frame;

    if (frame == INT32_MAX) frame = 0;

    doupdate();

}

Game::~Game() {
    is_running = false;
    player.reset();
    enemies.clear();
    endwin();
}

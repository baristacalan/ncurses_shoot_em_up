#include "Game.h"
#include <limits>

namespace {


    void init_curses() {
        
        initscr();
        napms(400);
        
        if (has_colors()) { 
            start_color(); 
            use_default_colors(); 
            init_pair(CYAN, COLOR_CYAN, -1); 
            init_pair(BLACK, COLOR_BLACK, COLOR_WHITE);
            init_pair(RED, COLOR_RED, -1);
            init_pair(GREEN, COLOR_GREEN, -1);
            init_pair(YELLOW, COLOR_YELLOW, -1);
            init_pair(BLUE, COLOR_BLUE, -1);
        }

        keypad(stdscr, true);
        noecho();
        cbreak();
        nodelay(stdscr, true);
        curs_set(0);

        leaveok(stdscr, true);
        refresh();
    }

    void process_input(int ch, Player& p) {
        switch (ch) {
        case KEY_LEFT:  p.move_left(PLAYER_MOVE_SPEED); break;
        case KEY_RIGHT: p.move_right(PLAYER_MOVE_SPEED); break;
        case ' ':       p.fire();       break;
        default: break;
        }
    }

    void draw_hud(const Player& p) {
        auto pos = p.get_position();
        int shot_count = p.get_shoot_count();


        attron(COLOR_PAIR(CYAN) | A_BOLD);
        mvprintw(0, 0, "X:%d Y:%d  ", pos.x, pos.y);
        attroff(COLOR_PAIR(CYAN) | A_BOLD);
        
        attron(COLOR_PAIR(RED) | A_BOLD);
        mvprintw(0, COLS - 23, "SHOTS COUNT: %d", shot_count);
        attroff(COLOR_PAIR(RED) | A_BOLD);
        
        attron(COLOR_PAIR(GREEN) | A_BOLD);
        mvprintw(1, COLS - 23, "SCORE: %d", p.get_score());
        attroff(COLOR_PAIR(GREEN) | A_BOLD);

    }
    



    int rand_point() {

        static std::mt19937 rng{ std::random_device{}() };
        std::uniform_int_distribution<int> dist(1, 10);

        return dist(rng);
    }

    bool check_collision(const Points& pos1, const Points& size1, const Points& pos2, const Points& size2) {
        return (pos1.x < pos2.x + size2.x && pos1.x + size1.x > pos2.x &&
            pos1.y < pos2.y + size2.y && pos1.y + size1.y > pos2.y);
    }

} // namespace

void Game::process_collisions() {

    std::vector<Bullet>& bullets = player->get_bullets();

    int score = player->get_score();

    for (auto it_enemy = enemies.begin(); it_enemy != enemies.end(); ) {
        bool enemy_destroyed = false;
        for (auto it_bullet = bullets.begin(); it_bullet != bullets.end(); ) {
            if (check_collision((*it_enemy)->get_position(), (*it_enemy)->get_size(), it_bullet->position_b, { 1, 1 })) {

                Points enemy_pos = (*it_enemy)->get_position();
                Points enemy_size = (*it_enemy)->get_size();

                int explosion_x = enemy_pos.x + enemy_size.x / 2;
                int explosion_y = enemy_pos.y + enemy_size.y / 2;


                it_bullet = bullets.erase(it_bullet);
                it_enemy = enemies.erase(it_enemy);
                enemy_destroyed = true;
                //player->set_score(++score);
                int gained_point = rand_point();
                score += gained_point;
                player->set_score(score);
                
                explosions.emplace_back(std::make_unique<Explosion>(explosion_y, explosion_x, RED, gained_point));

                break;
            }
            else {
                ++it_bullet;
            }
        }

        if (enemy_destroyed) continue;
 
        if (check_collision(player->get_position(), player->get_size(), (*it_enemy)->get_position(), (*it_enemy)->get_size())) {
            is_running = false;
            player->set_alive_status(false);
            break;
        }
        ++it_enemy;
    }
}

void Game::game_over() {
    if (!player->is_alive()) {
        erase();

        const char* msg = "GAME OVER!";
        int y = LINES / 2;
        int x = (COLS - strlen(msg)) / 2;

        attron(COLOR_PAIR(YELLOW) | A_BOLD);
        mvprintw(y, x, msg);
        attroff(COLOR_PAIR(YELLOW) | A_BOLD);

        nodelay(stdscr, false);

        mvprintw(y + 2, (COLS - 25) / 2, "Press any key to exit...");
        refresh();
        getch();
        //getch();
    }
}

Game::Game() : is_running(true) { init_curses(); }

void Game::run() {
    const int FRAME_MS = 17;
    const int h = 3, w = 6;
    const int y = LINES - (h + 3);
    const int x = (COLS - w) / 2;

    this->player = std::make_unique<Player>(h, w, y, x, 5, 5);

    while (is_running) {
        int ch = getch();
        if (ch == 27) break;
        if (ch != ERR) process_input(ch, *player);

        update();

        render();

        napms(FRAME_MS);
    }

    game_over();
    
}

void Game::update() {

    player->update_bullets();
    
    //Spawn frequency
    Enemy::spawn_enemy(enemies, frame);

    Enemy::update_enemy(enemies, frame, ENEMY_FALL_SPEED);

    process_collisions();

    for (auto it = explosions.begin(); it != explosions.end();) {

        if (!(*it)->update()) it = explosions.erase(it);
        else ++it;
    }


    ++frame;

    if (frame == INT32_MAX) frame = 0;

}

//Clears screen, draws player, enemies, bullets and explosions every time it is called.

void Game::render() {

    erase(); 
 
    player->redraw(5, 5);


    //Loops through enemies vector and draws.
    for (const auto& enemy : enemies) {
        enemy->redraw(0, 0);
    }



    player->draw_bullets();

    for (const auto& explosion : explosions) {
        explosion->draw();
    }

    draw_hud(*player);

    doupdate();
}

Game::~Game() {
    is_running = false;
    player.reset();
    enemies.clear();
    endwin();
}

#include "Game.h"
#include <limits>

namespace {

    //Initializes curses and sets up necessary attributes.
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
            init_pair(BKG_YELLOW, COLOR_YELLOW, COLOR_YELLOW);
            init_pair(BKG_RED, COLOR_RED, COLOR_RED);
            init_pair(BKG_BLUE, COLOR_BLACK, COLOR_BLUE);
            init_pair(WHITE, COLOR_WHITE, -1);
        }

        keypad(stdscr, true); //Enables whole keyboard
        noecho();
        cbreak(); //Gets input immediately, without pressing enter.
        nodelay(stdscr, true); // Allows asynchronous
        curs_set(0); //Turns off cursor.
        //bkgd(COLOR_PAIR(BKG_YELLOW));

        leaveok(stdscr, true);
        refresh();
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


Game::Game() : is_running(true), is_paused(false), frame(0) { init_curses(); } //Game class ctor.

void Game::run() {

    GameState current_state = GameState::MAIN_MENU;

    while (current_state != GameState::EXIT) {

        if (current_state == GameState::MAIN_MENU) {
            current_state = main_menu_loop();
        }

        else if (current_state == GameState::PLAYING) {

            current_state = game_loop();
        }
        else if (current_state == GameState::RESTART) {
            this->reset();
            timer.reset();
            current_state = GameState::PLAYING;
        }

    }

}

void Game::handle_input(int ch) {

    if (is_paused && ch != 112 && ch != 27) {
        ch = ERR;
        return;
    }

    switch (ch) {
    
    case KEY_LEFT:  player->move_left(PLAYER_MOVE_SPEED);  break;
    
    case KEY_RIGHT: player->move_right(PLAYER_MOVE_SPEED); break;
    
    case ' ':       player->fire();                        break;
    
    case 27:        is_running = false;                    break; // 27 = ESC

    case 112:      toggle_pause(); break; // 112 = 'p'

    default: break;

    }
}

void Game::process_collisions() {

    std::vector<Bullet>& bullets = player->get_bullets(); // Get bullets vector

    int score = player->get_score();

    int success_shots = player->get_successful_shots();

    //Iterate on enemies vector.
    for (auto it_enemy = enemies.begin(); it_enemy != enemies.end(); ) {
        bool enemy_destroyed = false;
        //Start iterating on bullets vector
        for (auto it_bullet = bullets.begin(); it_bullet != bullets.end(); ) {

            //Check any existing collisions with the iterated objects.
            if (check_collision((*it_enemy)->get_position(), (*it_enemy)->get_size(), it_bullet->position_b, { 1, 1 })) {


                //If a red enemy will be hit, player will die.
                if ((*it_enemy)->get_color() == BKG_RED) {

                    this->is_running = false;
                    player->set_alive_status(false);
                    it_enemy = enemies.erase(it_enemy);
                    it_bullet = bullets.erase(it_bullet);
                    break;
                }

                //May change this into Rect struct later on.
                Points enemy_pos = (*it_enemy)->get_position();
                Points enemy_size = (*it_enemy)->get_size();

                int explosion_x = enemy_pos.x + enemy_size.x / 2;
                int explosion_y = enemy_pos.y + enemy_size.y / 2;

                //Erase the collided objects(Enemy and )
                it_bullet = bullets.erase(it_bullet);
                it_enemy = enemies.erase(it_enemy);
                enemy_destroyed = true;
                
                int gained_point = rand_point();
                score += gained_point;
                player->set_successful_shots(++success_shots);
                player->set_score(score);

                explosions.emplace_back(Explosion(explosion_y, explosion_x, YELLOW, gained_point));

                beep();

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

//Checks if the player alive. If so, clears screen and prints game over. Asks if you want to quit or restart.
GameState Game::game_over() {
    
    if (!player->is_alive()) {
        erase();

        int ch{};

        const char* msg = "GAME OVER!";
        int y = LINES / 2;
        int x = (COLS - 10) / 2;

        attron(COLOR_PAIR(YELLOW) | A_BOLD);
        mvprintw(y, x, msg);
        attroff(COLOR_PAIR(YELLOW) | A_BOLD);

        mvprintw(y + 3, (COLS - 40) / 2, "Press 'R' to Restart or ESC to exit...");
        mvprintw(y + 5, (COLS - 7) / 2, "SCORE: %d", player->get_score());
        refresh();
       
        nodelay(stdscr, false);
        do {
            ch = getch();
        } while ((ch != 'R') && (ch != 'r') && (ch != 27));
        nodelay(stdscr, true);

        if (ch == 'R' || ch == 'r') return GameState::RESTART;
    }

    return GameState::EXIT;
}

void Game::toggle_pause() { is_paused = !is_paused; }

void Game::display_pause_menu() {

    int mh{ 15 }, mw{40};

    WINDOW* menu_box = newwin(mh, mw, (LINES - mh) / 2, (COLS - mw) / 2);
    wbkgd(menu_box, COLOR_PAIR(BLACK));

    attron(COLOR_PAIR(BLACK) | A_BOLD);
    mvwprintw(menu_box, (mh) / 2, (mw - 6) /2, "PAUSED");
    mvwprintw(menu_box, mh / 2 + 2, (mw - 23) / 2, "PRESS P TO CONTINUE...");
    attroff(COLOR_PAIR(BLACK) | A_BOLD);

    wnoutrefresh(menu_box);

    delwin(menu_box);
}

void Game::display_start_menu(const int& current_selection) {
    
    const int mh = 15, mw = 40;
    WINDOW* start_menu = newwin(mh, mw, (LINES - mh) / 2, (COLS - mw) / 2);
    box(start_menu, 0, 0);

    WINDOW* play_bar = derwin(start_menu, 3, mw - 4, 3, 2);
    WINDOW* exit_bar = derwin(start_menu, 3, mw - 4, 7, 2);

    if (current_selection == 0) {
        wbkgd(play_bar, COLOR_PAIR(BLACK)); // Highlighted
        wbkgd(exit_bar, 0);                 // Not highlighted
    }
    else { 
        wbkgd(play_bar, 0); //Highlight exit bar                 
        wbkgd(exit_bar, COLOR_PAIR(BLACK)); 
    }
    
    box(play_bar, 0, 0);
    mvwprintw(play_bar, 1, (mw - 4 - 4) / 2, "PLAY");

    box(exit_bar, 0, 0);
    mvwprintw(exit_bar, 1, (mw - 4 - 4) / 2, "EXIT");

    wnoutrefresh(start_menu);
    wnoutrefresh(play_bar);
    wnoutrefresh(exit_bar);

    delwin(exit_bar);
    delwin(start_menu);
    delwin(play_bar);

}

GameState Game::main_menu_loop() {

    nodelay(stdscr, false); //Block until user input

    int current_selection = 0;
    int key_pressed{};

    while (true) {

        display_start_menu(current_selection);
        doupdate();

        key_pressed = getch();
        
        switch (key_pressed) {

        case KEY_UP:
            if (current_selection == 1) {
                current_selection = 0; //Toggle to PLAY.
            }
            break;
        case KEY_DOWN:
            if (current_selection == 0) {
                current_selection = 1; //Toggle to EXIT.
            }
            break;

        case ' ':
        case '\n':
            if (current_selection == 0) {
                nodelay(stdscr, true);
                return GameState::PLAYING;
            }
            else if (current_selection == 1) {
                return GameState::EXIT;
            }
            break;
        case 27: //ESC
            return GameState::EXIT;
        }

    }

}

void Game::draw_hud() {

    Points pos = player->get_position();
    int shot_count = player->get_total_shot_count();

    int score = player->get_score();
    int success_shots = player->get_successful_shots();

    attron(COLOR_PAIR(CYAN) | A_BOLD);
    mvprintw(0, 0, "X:%d Y:%d  ", pos.x, pos.y);
    attroff(COLOR_PAIR(CYAN) | A_BOLD);

    attron(COLOR_PAIR(RED) | A_BOLD);
    mvprintw(0, COLS - 23, "SHOTS COUNT: %d", shot_count);
    attroff(COLOR_PAIR(RED) | A_BOLD);

    attron(COLOR_PAIR(GREEN) | A_BOLD);
    mvprintw(1, COLS - 23, "SCORE: %d", score);
    attroff(COLOR_PAIR(GREEN) | A_BOLD);
    
    attron(COLOR_PAIR(BLUE) | A_BOLD);
    mvprintw(2, COLS - 23, "SUCCESSFUL SHOTS: %d", success_shots);
    attroff(COLOR_PAIR(BLUE) | A_BOLD);
    
    attron(COLOR_PAIR(WHITE) | A_BOLD);
    timer.draw();
    attroff(COLOR_PAIR(WHITE) | A_BOLD);



}

GameState Game::game_loop() {
    
   
    const int FRAME_MS = 16; //30 fps
    const int PLAYER_HEIGHT = 3, PLAYER_WIDTH = 6;
    const int PLAYER_POSY = LINES - (PLAYER_HEIGHT + 3);
    const int PLAYER_POSX = (COLS - PLAYER_WIDTH) / 2;
    const int DRAW_TYPE = 5;

    timer.start();
    this->player = std::make_unique<Player>(PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_POSY, PLAYER_POSX, DRAW_TYPE, DRAW_TYPE, BKG_BLUE);


    while (this->is_running) {

        int ch = getch();

        if (ch != ERR) handle_input(ch);

        update();

        render();

        napms(FRAME_MS);
    }

    return game_over();
    
}

void Game::reset() {

    explosions.clear();
    enemies.clear();

    player->set_alive_status(true);
    player->set_score(0);

    is_running = true;
    frame = 0;

}

//Updates the game flow.

void Game::update() {

    if (this->is_paused) return;

    player->update_bullets();
    
    //Spawn frequency
    Enemy::spawn_enemy(enemies, frame);

    Enemy::update_enemy(enemies, frame, ENEMY_FALL_SPEED);

    process_collisions();

    for (auto it = explosions.begin(); it != explosions.end();) {

        if (!it->update()) it = explosions.erase(it);
        else ++it;
    }


    ++frame;

    if (frame == INT32_MAX) frame = 0;

}

//Clears screen, draws player, enemies, bullets and explosions every time it is called.

void Game::render() {


    if(!is_paused) erase();
    
    player->draw_bullets();

    for (const auto& explosion : explosions) {
        explosion.draw();
    }

    draw_hud();

    wnoutrefresh(stdscr);
    
    player->redraw(5, 5);

    //Loops through enemies vector and draws.
    for (const auto& enemy : enemies) {
        enemy->redraw(0, 0);
    }

    if (is_paused) display_pause_menu();


    doupdate();

}

Game::~Game() {
    is_running = false;
    player.reset();
    enemies.clear();
    timer.reset();
    endwin();
}
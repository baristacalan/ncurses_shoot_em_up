#pragma once
#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Enemy.h"
#include "Explosion.h"


enum class GameState {
    
    MAIN_MENU,
    PLAYING,
    RESTART,
    EXIT,
};


class Game {
    
    //Objects
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<Explosion>> explosions;



    //Functions
    void update();
    void render();
    void process_collisions();
    void handle_input(int ch);


    //Variables
    bool is_running;
    int frame;
    bool is_paused;


    GameState game_loop();
    GameState main_menu_loop();
    GameState game_over();

    GameState test();

    void toggle_pause();
    void display_pause_menu();
    void display_start_menu(int option);

    void draw_hud();


public:
    Game();

    void run();

    void reset();

    ~Game();
};

#endif // GAME_H

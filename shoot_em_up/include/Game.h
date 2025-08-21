#pragma once
#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Enemy.h"
#include "Explosion.h"


enum class GameState {

    PLAYING,
    RESTART,
    EXIT,
    PAUSE
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

    GameState game_over();
    void toggle_pause();
    void display_pause_menu();
    void draw_hud();


public:
    Game();

    GameState run();
    void reset();

    ~Game();
};

#endif // GAME_H

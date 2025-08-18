#pragma once
#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Enemy.h"
#include "Explosion.h"


class Game {
    
    //Objects
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::unique_ptr<Player> player;
    std::vector<std::unique_ptr<Explosion>> explosions;

    
    //Functions
    void update();
    void render();
    void process_collisions();


    //Variables
    bool is_running{ true };
    int frame{ 0 };


    void game_over();


public:
    Game();

    void run();

    ~Game();
};

#endif // GAME_H

#pragma once
#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Enemy.h"


class Game {
    bool is_running{ true };
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::unique_ptr<Player> player;

    int frame{ 0 };
    void process_collisions();

public:
    Game();
    void run();
    void update();

    ~Game();
};

#endif // GAME_H

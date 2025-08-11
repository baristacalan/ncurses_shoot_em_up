#pragma once
#ifndef GAME_H
#define GAME_H

#include "Player.h"


class Game {
    bool is_running{ true };

public:
    Game();
    void run();
    void update(Player& player, float dt = 0.0f);
    ~Game();
};

#endif // GAME_H

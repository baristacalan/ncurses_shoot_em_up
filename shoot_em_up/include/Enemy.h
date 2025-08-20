#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include <utilities.h>
#include "Entity.h"

class Enemy : public Entity {

public:
    Enemy(int h = 6, int w = 3, int y = 1, int x = COLS / 2, int cp = BKG_RED, chtype chr1 = 0, chtype chr2 = 0);

    // Fall down
    bool fall(int speed = 1);

    static void update_enemy(std::vector<std::unique_ptr<Enemy>>& enemies, int& frame, int speed = 1);
    static void spawn_enemy(std::vector<std::unique_ptr<Enemy>>& enemies, int& frame);

    Enemy(const Enemy&) = delete; // Copy ctor'i siler.
    Enemy& operator=(const Enemy&) = delete; // operator= 'i siler

    ~Enemy() override = default;
};

#endif

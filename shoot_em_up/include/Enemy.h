#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include <utilities.h>
#include "Entity.h"

class Enemy : public Entity {
public:
    Enemy(int h = 6, int w = 3, int y = 1, int x = COLS / 2, int cp = 3, chtype chr1 = 0, chtype chr2 = 0);

    // Aþaðý düþürme
    bool fall(int step = 1);
    //static void UpdateAll(std::vector<std::unique_ptr<Enemy>>& v, int step = 1);

    static void update_enemy(std::vector<std::unique_ptr<Enemy>>& enemies, int step = 1);

    Enemy(const Enemy&) = delete; // Copy ctor'i siler.
    Enemy& operator=(const Enemy&) = delete; // operator= 'i siler
    //Enemy(Enemy&&) noexcept;
    //Enemy& operator=(Enemy&&) noexcept;

    ~Enemy() override = default;
};

#endif

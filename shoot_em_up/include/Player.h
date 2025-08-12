#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "utilities.h"
#include "Entity.h"

struct Bullet { Points position_b; Bullet(int y, int x) : position_b{ y,x } {} };

class Player : public Entity {

    std::vector<Bullet> bullets;
    int score{ 0 };
    int shoot_count{};
public:
    Player(int height, int width, int posy, int posx);
    void move_left();
    void move_right();
    void fire();
    void update_bullets();

    int get_shoot_count() const;

    ~Player() override = default;
};
#endif //!PLAYER_H
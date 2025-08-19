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
    //bool has_moved{};


public:
    
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

    Player(int height, int width, int posy, int posx, chtype chr1, chtype chr2, int color_pair);

    std::vector<Bullet>& get_bullets();


    void move_left(int speed);
    void move_right(int speed);
    void fire();
    void draw_bullets() const;
    void update_bullets();

    int get_shoot_count() const;

    int get_score() const;
    void set_score(int new_score);


    //int is_moved() const { return this->has_moved; }
    //void set_moved(bool move_status) { this->has_moved = move_status; }


    ~Player() override = default;
};
#endif //!PLAYER_H
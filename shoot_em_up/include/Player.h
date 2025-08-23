#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "utilities.h"
#include "Entity.h"
#include "Timer.h"

constexpr milliseconds FIRE_COOLDOWN_MS{ 300 };

struct Bullet { Points position_b; Bullet(int y, int x) : position_b{ y,x } {} };

class Player : public Entity {
    
    std::vector<Bullet> bullets;
    int score{ 0 };
    int total_shoot_count{0};
    int successful_shots{0};

    steady_clock::time_point last_shot{}; //Last shot time point



public:

    Player(int height, int width, int posy, int posx, chtype chr1, chtype chr2, int color_pair);

    std::vector<Bullet>& get_bullets();


    void move_left(int speed);
    void move_right(int speed);
    void fire();
    void draw_bullets() const;
    void update_bullets();

    int get_total_shot_count() const;
    int get_successful_shots() const { return this->successful_shots; };
    void set_successful_shots(int shots) { this->successful_shots = shots; };


    int get_score() const;
    void set_score(int new_score);

    ~Player() override = default;
};
#endif //!PLAYER_H
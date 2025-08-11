#pragma once
#include "Player.h"

Player::Player(int h, int w, int y, int x)
    : Entity(h, w, y, x, /*color_pair*/1) {
    draw(h, w, y, x);
}

//void Player::move_left() { erase(); Entity::move_left();  draw(size.y, size.x, position.y, position.x); }
//void Player::move_right() { erase(); Entity::move_right(); draw(size.y, size.x, position.y, position.x); }

void Player::move_left() { erase(); Entity::move_left();  redraw(); }
void Player::move_right() { erase(); Entity::move_right(); redraw(); }

void Player::fire() {
    auto p = get_position(), s = get_size();
    bullets.push_back({ p.y - 1, p.x + s.x / 2 });
    shoot_count++;
}

void Player::update_bullets() {
    for (auto it = bullets.begin(); it != bullets.end(); ) {
        
        if (it->position_b.y >= 0 && it->position_b.y < LINES &&
            it->position_b.x >= 0 && it->position_b.x < COLS)
            
            mvaddch(it->position_b.y, it->position_b.x, ' ');
        
        --it->position_b.y;
        
        if (it->position_b.y < 0) { it = bullets.erase(it); continue; }
        
        attron(A_BOLD);
        mvaddch(it->position_b.y, it->position_b.x, '|');
        attroff(A_BOLD);
        
        ++it;
    }
}

int Player::get_shoot_count() const {
    return shoot_count;
}

Player::~Player() { erase(); delwin(object); object = nullptr; }

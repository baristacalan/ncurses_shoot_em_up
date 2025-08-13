#pragma once
#include "Player.h"

Player::Player(int h, int w, int y, int x, chtype chr1, chtype chr2)
    : Entity(h, w, y, x, /*color_pair*/1) {
    draw(h, w, y, x, chr1, chr2);
}

//void Player::move_left() { erase(); Entity::move_left();  draw(size.y, size.x, position.y, position.x); }
//void Player::move_right() { erase(); Entity::move_right(); draw(size.y, size.x, position.y, position.x); }

void Player::move_left(int speed) { erase(); Entity::move_left(speed);  redraw(1, 1); }
void Player::move_right(int speed) { erase(); Entity::move_right(speed); redraw(1, 1); }

void Player::fire() {
    auto position_player = get_position(), size_player = get_size();
    bullets.push_back({ position_player.y - 1, position_player.x + size_player.x / 2 });
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

std::vector<Bullet>& Player::get_bullets() {
    return bullets;
}


int Player::get_shoot_count() const {
    return shoot_count;
}


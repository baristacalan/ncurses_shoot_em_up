#pragma once
#include "Player.h"

Player::Player(int h, int w, int y, int x, chtype chr1, chtype chr2, int color_pair)
    : Entity(h, w, y, x, color_pair){
    draw(/*h, w, y, x,*/ chr1, chr2);
}

void Player::move_left(int speed) { Entity::move_left(speed); }

void Player::move_right(int speed) { Entity::move_right(speed); }

void Player::fire() {
    
    auto now = steady_clock::now(); //�imdiye i�aret koyar


    //E�er last_shot zaman noktas� ba�lang��tan beri de�i�tiyse VE at�� �zerinden ge�en s�re cooldowndan azsa metod durur. 
    // Yoksa �imdiki at��� son at�� yapar
    if (last_shot.time_since_epoch().count() != 0 && now - last_shot < FIRE_COOLDOWN_MS) {

        return;
    }

    last_shot = now;


    auto position_player = get_position(), size_player = get_size();

    bullets.push_back({ position_player.y - 1, position_player.x + size_player.x / 2 });

    total_shoot_count++;
}

void Player::draw_bullets() const {

    attron(A_BOLD | COLOR_PAIR(BLUE));
    for (const auto& bullet : bullets) {
        mvaddch(bullet.position_b.y, bullet.position_b.x, '|');
    }
    attroff(A_BOLD | COLOR_PAIR(BLUE));
}

void Player::update_bullets() {
    for (auto it = bullets.begin(); it != bullets.end(); ) {

        //mvaddch(it->position_b.y, it->position_b.x, ' ');
        --it->position_b.y;
        if (it->position_b.y < 0) {
            it = bullets.erase(it);
        }
        else {
            ++it;
        }
    }
}

std::vector<Bullet>& Player::get_bullets() { return bullets; }

int Player::get_total_shot_count() const { return total_shoot_count;}

int Player::get_score() const { return this->score;}

void Player::set_score(int new_score) {

    this->score = new_score;
}


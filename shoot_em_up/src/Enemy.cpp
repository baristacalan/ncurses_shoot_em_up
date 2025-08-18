#include "Enemy.h"


Enemy::Enemy(int h, int w, int y, int x, int cp, chtype chr1, chtype chr2)
    : Entity(h, w, y, x, cp) {
    draw(/*h, w, y, x,*/ chr1, chr2);
}

bool Enemy::fall(int step) {
    move_down(step);
    //this->erase();
    Points p = get_position(), s = get_size();
    return (p.y + s.y) < (LINES - 1); // If it's in bounds.
}


void Enemy::update_enemy(std::vector<std::unique_ptr<Enemy>>& enemies, int step) {


    for (auto it = enemies.begin(); it != enemies.end(); ) {
        if (!(*it)->fall(step)) it = enemies.erase(it);
        else ++it;
    }
}

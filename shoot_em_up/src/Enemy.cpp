#include "Enemy.h"


Enemy::Enemy(int h, int w, int y, int x, int cp, chtype chr1, chtype chr2)
    : Entity(h, w, y, x, cp) {
    draw(h, w, y, x, chr1, chr2);
}

bool Enemy::fall(int step) {
    move_down(step);
    Points p = get_position(), s = get_size();
    return (p.y + s.y) < (LINES - 1); // If it's in bounds.
}


void Enemy::update_enemy(std::vector<std::unique_ptr<Enemy>>& enemies, int step) {
    for (auto it = enemies.begin(); it != enemies.end(); ) {
        if (!(*it)->fall(step)) it = enemies.erase(it);
        else ++it;
    }
}

//
//void Enemy::UpdateAll(std::vector<std::unique_ptr<Enemy>>& v, int step) {
//    v.erase(std::remove_if(v.begin(), v.end(),
//        [step](std::unique_ptr<Enemy>& e) { return !e->fall(step); }),
//        v.end());
//}

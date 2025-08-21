#include "Enemy.h"

//Helper functions

int rand_x(int w) {
    static std::mt19937 rng{ std::random_device{}() };
    std::uniform_int_distribution<int> dist(1, COLS - w - 1);
    return dist(rng);
}


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

void Enemy::update_enemy(std::vector<std::unique_ptr<Enemy>>& enemies, int& frame, int speed) {

    
    //Controls the movement frequency
    if ((frame % ENEMY_MOVE_INTERVAL) == 0) {

        for (auto it = enemies.begin(); it != enemies.end(); ) {
            if (!(*it)->fall(speed)) it = enemies.erase(it);
            else ++it;
        }

    }
}

void Enemy::spawn_enemy(std::vector<std::unique_ptr<Enemy>>& enemies, int& frame) {


    //Controls spawn frequency
    if (frame % ENEMY_SPAWN_INTERVAL == 0) {
        int ew = 4, eh = 3;
        enemies.emplace_back(std::make_unique<Enemy>(eh, ew, 0, rand_x(ew), BKG_YELLOW, 0, 0));
    }


    if (frame % 100 == 0) {

        int ew = 4, eh = 3;
        enemies.emplace_back(std::make_unique<Enemy>(eh, ew, 0, rand_x(ew), BKG_RED, 0, 0));
    }
}



#include "Enemy.h"

Enemy::Enemy(int start_x, int speed_, int color_pair_, chtype glyph_)
    : Entity(1, 1, 0, start_x, color_pair_), speed(speed_), glyph(glyph_) {
    draw(1, 1, 0, start_x);
    //redraw();
    paint();
}


void Enemy::paint() {
    if (!object) return;
    if (color_pair > 0) wattron(object, COLOR_PAIR(color_pair));
    mvwaddch(object, 0, 0, glyph);
    if (color_pair > 0) wattroff(object, COLOR_PAIR(color_pair));
    wrefresh(object);
}

void Enemy::fall() {
    move_by(speed, 0);
    draw(1, 1, position.y, position.x);
    paint();
}

bool Enemy::at_bottom() const {
    int rows, cols; getmaxyx(stdscr, rows, cols);
    return position.y >= rows - 1 - size.y;
}

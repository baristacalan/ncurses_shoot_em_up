#include "Entity.h"

Entity::Entity(int h, int w, int y, int x, int color)
    : size{ h,w }, position{ y,x }, color_pair{ color } {
}

Entity::~Entity() { erase(); }

void Entity::draw(int h, int w, int y, int x) {
    size = { h,w };
    position = { y,x };
    adjust_to_screen();

    if (!object) object = newwin(size.y, size.x, position.y, position.x);
    if (!object) return;

    if (color_pair > 0) wbkgd(object, COLOR_PAIR(color_pair));
    box(object, 1, 1);
    wrefresh(object);
}

void Entity::redraw() {
    if (!object) return;
    adjust_to_screen();
    if (color_pair > 0) wbkgd(object, COLOR_PAIR(color_pair));
    mvwin(object, position.y, position.x);
    box(object, 1, 1);
    wrefresh(object);
}

void Entity::erase() {
    if (!object) return;
    wcolor_set(object, 0, nullptr);
    wattrset(object, A_NORMAL);
    wbkgd(object, A_NORMAL);
    werase(object);
    wrefresh(object);
    //delwin(object);
    //object = nullptr;
}

void Entity::set_position(int y, int x) {
    position = { y,x };
    adjust_to_screen();
}

void Entity::move_by(int dy, int dx) {
    position.y += dy;
    position.x += dx;
    adjust_to_screen();
}

void Entity::adjust_to_screen() {
    int rows, cols; getmaxyx(stdscr, rows, cols);
    if (position.x < 1) position.x = 1;
    if (position.y < 1) position.y = 1;
    if (position.x + size.x > cols - 1) position.x = cols - 1 - size.x;
    if (position.y + size.y > rows - 1) position.y = rows - 1 - size.y;
}

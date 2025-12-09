#include "Entity.h"

Entity::Entity(int h, int w, int y, int x, int color)
    : size{ h,w }, position{ y,x }, color_pair{ color } {
}

void Entity::draw(int h, int w, int y, int x, chtype chr1, chtype chr2) {
    //size = { h,w };
    //position = { y,x };
    adjust_to_screen();

    if (!object) object = newwin(h, w, y, x);
    //if (!object) object = newwin(rect.height, rect.width, rect.posy, rect.posy);
    if (!object) return;

    if (color_pair > 0) wbkgd(object, COLOR_PAIR(color_pair));
    box(object, chr1, chr2);
    wnoutrefresh(object);
}

void Entity::redraw(int h, int w, int y, int x, chtype chr1, chtype chr2) {
    if (!object) return;
    adjust_to_screen();
    //if (color_pair > 0) wbkgd(object, COLOR_PAIR(color_pair));
    mvwin(object, position.y, position.x);
    //mvwin(object, rect.posy, rect.posx);
    box(object, chr1, chr2);
    wnoutrefresh(object);
}


void Entity::set_position(int y, int x) {
    position = { y,x };
    //rect.posy = y;
    //rect.posx = x;
    adjust_to_screen();
}

void Entity::move_by(int dy, int dx) {
    position.y += dy;
    position.x += dx;
    //rect.posy += dy;
    //rect.posx += dx;

    adjust_to_screen();
}

void Entity::adjust_to_screen() {
    int rows, cols; getmaxyx(stdscr, rows, cols);

    if (position.x < 1) position.x = 1;
    if (position.y < 1) position.y = 1;
    if (position.x + size.x > cols - 1) position.x = cols - 1 - size.x;
    if (position.y + size.y > rows - 1) position.y = rows - 1 - size.y;

    /*if (rect.posx < 1) rect.posx = 1;
    if (rect.posy < 1) rect.posy = 1;
    if (rect.posx + rect.width > cols - 1) rect.posx = cols - 1 - rect.width;
    if (rect.posy + rect.height > rows - 1) rect.posy = rows - 1 - rect.height;*/

}

Entity::~Entity() { delwin(object); object = nullptr; }
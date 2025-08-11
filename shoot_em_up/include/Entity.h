#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <utilities.h>

class Entity {
protected:
    WINDOW* object{ nullptr };
    Points  size{ 0,0 };
    Points  position{ 0,0 };
    int     color_pair{ 0 };
    bool    alive{ true };

    void adjust_to_screen();

public:
    Entity() = default;
    Entity(int h, int w, int y, int x, int color = 0);
    virtual ~Entity();

    // window lifecycle + drawing
    void draw(int h, int w, int y, int x);
    void redraw();                  
    void erase();

    // movement
    void set_position(int y, int x);
    void move_by(int dy, int dx);
    void move_left(int step = 2) { move_by(0, -step); }
    void move_right(int step = 2) { move_by(0, step); }

    // access
    Points get_position() const { return position; }
    Points get_size()     const { return size; }
    bool   is_alive()     const { return alive; }
    void   set_color(int pair) { color_pair = pair; }
};




#endif // !ENTITY_H

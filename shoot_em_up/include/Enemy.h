#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include <utilities.h>

#include "Entity.h"

class Enemy : public Entity {
    int   speed{ 1 };
    chtype glyph{ 'V' | A_BOLD };

public:
    Enemy(int start_x, int speed_ = 1, int color_pair_ = 2, chtype glyph_ = 'V' | A_BOLD);

    // advance one step downward and redraw
    void fall();

    // reached bottom?
    bool at_bottom() const;

private:
    void paint();  // put glyph into the 1x1 window
};



#endif // !ENEMY_H

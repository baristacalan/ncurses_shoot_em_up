#pragma once
#ifndef UTILITIES_H
#define UTILITIES_H

#include <curses.h>
#include <vector>
#include <utility>
#include <memory>
#include <random>

struct Points { int y, x;};

struct Rect {

	int posy, posx;
	int height, width;

};


enum COLORS : short {

    CYAN = 1,
    BLACK = 2,
    RED = 3,
    GREEN = 4,
    YELLOW = 5

};

#endif // !UTILITIES_H

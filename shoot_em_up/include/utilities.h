#pragma once
#ifndef UTILITIES_H
#define UTILITIES_H

#include <curses.h>
#include <vector>
#include <utility>
#include <memory>
#include <random>
//#include <list>
//#include <iostream>
//#include <chrono>

struct Points { int y, x;};

struct Rect {

	int posy, posx;
	int height, width;

};


#endif // !UTILITIES_H

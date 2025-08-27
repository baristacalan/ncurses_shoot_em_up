#pragma once
#ifndef UTILITIES_H
#define UTILITIES_H

#include <curses.h>
#include <vector>
#include <memory>
#include <random>
#include <chrono>

struct Points { int y, x;};

//struct Rect {
//
//	int posy, posx;
//	int height, width;
//
//};


enum COLORS : short {

    CYAN = 1,
    BLACK = 2,
    RED = 3,
    GREEN = 4,
    YELLOW = 5,
    BLUE= 6,
    BKG_YELLOW = 7,
    BKG_RED = 8,
    BKG_BLUE = 9,
    WHITE = 10
};


constexpr int PLAYER_MOVE_SPEED = 3;
constexpr int ENEMY_SPAWN_INTERVAL = 30; // in frames
constexpr int ENEMY_MOVE_INTERVAL = 4;   // in frames
constexpr int ENEMY_FALL_SPEED = 1;
constexpr std::chrono::milliseconds FIRE_COOLDOWN_MS{ 200 };
constexpr int FRAME_MS = 16; //60 fps

#endif // !UTILITIES_H

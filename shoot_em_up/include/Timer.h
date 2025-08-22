#pragma once
#ifndef TIMER_H
#define TIMER_H
#include "utilities.h"

using namespace std::chrono;


class Timer {

private:
	steady_clock::time_point start_tp;


public:

	void start();

	void reset();

	void draw() const;


	Timer()=default;
	~Timer() = default;

};




#endif // !TIMER_H

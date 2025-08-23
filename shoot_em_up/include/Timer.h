#pragma once
#ifndef TIMER_H
#define TIMER_H
#include "utilities.h"

using namespace std::chrono;


class Timer {

private:
	steady_clock::time_point start_tp{}; //Time points work like a checkpoint. 
	steady_clock::time_point pause_tp{}; //Pause check_point
	milliseconds paused_total{0};		// Total time in pause.
	bool paused{ true };

public:

	void start();
	void stop();
	void reset();

	void draw() const;


	Timer() = default;
	~Timer() = default;

};




#endif // !TIMER_H

#include "Timer.h"

void Timer::reset() {
	start_tp = steady_clock::now();
}

void Timer::draw() const {

	auto now = steady_clock::now(); //returns time_point
	auto elapsed = duration_cast<seconds>(now - start_tp).count(); //Returns long long

	int minutes = static_cast<int>(elapsed / 60);
	int seconds = static_cast<int>(elapsed % 60);

	mvprintw(1, (COLS - 23) / 2, "TIME: %02d:%02d", minutes, seconds);
}

Timer::Timer() {

	start_tp = steady_clock::now();
}

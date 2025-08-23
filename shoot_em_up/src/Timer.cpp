#include "Timer.h"

void Timer::start() {
	
	if (!paused) return; //Cannot start if already running.
	auto now = steady_clock::now(); //Check point on start

	if (pause_tp.time_since_epoch().count() != 0) {
		paused_total += duration_cast<milliseconds>(now - pause_tp);
	}
	else {
		start_tp = now;
		paused_total = milliseconds{ 0 };
	}
	paused = false;

}

void Timer::stop() {

	if (paused) return;

	pause_tp = steady_clock::now();
	paused = true;

}

void Timer::reset() {
	paused = true;
	paused_total = milliseconds{ 0 };
	start_tp = steady_clock::now();
	pause_tp = {};
}


void Timer::draw() const {
	auto base = paused ? pause_tp : steady_clock::now();
	if (start_tp.time_since_epoch().count() == 0) return;

	auto ms = duration_cast<milliseconds>(base - start_tp) - paused_total;
	if (ms.count() < 0) ms = milliseconds{ 0 };

	auto total_s = duration_cast<seconds>(ms).count();
	int mm = static_cast<int>(total_s / 60);
	int ss = static_cast<int>(total_s % 60);

	mvprintw(0, (COLS - 17) / 2, "TIME: %02d:%02d", mm, ss);
}

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


void Timer::draw(int y, int x) const {
	auto base = paused ? pause_tp : steady_clock::now();
	if (start_tp.time_since_epoch().count() == 0) return;

	auto ms = duration_cast<milliseconds>(base - start_tp) - paused_total;
	if (ms.count() < 0) ms = milliseconds{ 0 };

	auto total_s = duration_cast<seconds>(ms).count();
	int mm = static_cast<int>(total_s / 60);
	int ss = static_cast<int>(total_s % 60);

	mvprintw(y, x, "TIME: %02d:%02d", mm, ss);
}

int Timer::total_time_seconds() {

   if (start_tp.time_since_epoch().count() == 0) return 0;
   auto now = paused ? pause_tp : steady_clock::now(); // Use pause_tp if paused, otherwise current time.  
   auto elapsed = duration_cast<seconds>(now - start_tp - paused_total);  
   return static_cast<int>(elapsed.count());  
}

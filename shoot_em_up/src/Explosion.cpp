#include "Explosion.h"


Explosion::Explosion(int start_y, int start_x, int color, int& score) :  lifetime(4), frame_counter(0), recent_score_gain(score){

	particles.push_back({ {start_y, start_x}, {1, 1}, {color} });
	particles.push_back({ {start_y, start_x}, {1, -1}, {color} });
	particles.push_back({ {start_y, start_x}, {-1, 1}, {color} });
	particles.push_back({ {start_y, start_x}, {-1, -1}, {color} });
	
	score_position = {start_y, start_x };
	beep();
}

bool Explosion::update() {
	
	if (frame_counter == INT32_MAX) frame_counter = 0;


	if (frame_counter % 4 == 0) {

		for (auto& p : particles) {

			p.position.x += p.velocity.x;
			p.position.y += p.velocity.y;
		}
		
		lifetime--;
		
	}

	++frame_counter;

	return lifetime > 0;

}


void Explosion::draw() const {
	if (particles.empty()) {
		return;
	}
	attron(COLOR_PAIR(particles[0].color) | A_BOLD);
	for (const auto& p : particles) {
		
		
		mvaddch(p.position.y, p.position.x, '*');

	}
	attroff(COLOR_PAIR(particles[0].color) | A_BOLD);

	attron(COLOR_PAIR(GREEN) | A_BOLD);
	mvprintw(score_position.y, score_position.x, "%d", recent_score_gain);
	attroff(COLOR_PAIR(GREEN) | A_BOLD);
	
}
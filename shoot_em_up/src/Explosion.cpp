#include "Explosion.h"

Explosion::Explosion(int start_y, int start_x, int color) :  lifetime(8), frame_counter(0){

	particles.push_back({ {start_y, start_x}, {1, 1}, {color} });
	particles.push_back({ {start_y, start_x}, {1, -1}, {color} });
	particles.push_back({ {start_y, start_x}, {-1, 1}, {color} });
	particles.push_back({ {start_y, start_x}, {-1, -1}, {color} });
}

bool Explosion::update() {
	
	if (frame_counter == INT32_MAX) frame_counter = 0;


	if (frame_counter % 3 == 0) {

		for (auto& p : particles) {

			p.position.x += p.velocity.x;
			p.position.y += p.velocity.y;
		}
	}


	++frame_counter;
	lifetime--;

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
}

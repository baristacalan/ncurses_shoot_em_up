#pragma once
#ifndef EXPLOSION_H
#define EXPLOSION_H
#include "utilities.h"

struct Particle {

	Points position;
	Points velocity;
	int color;

};


class Explosion {

private:

	std::vector<Particle> particles;
	int lifetime;
	int frame_counter;
	Points score_position;
	int recent_score_gain;

public:

	Explosion(int start_y, int start_x, int color, int& score);

	bool update();

	void draw() const;


	~Explosion() = default;


};

#endif // !EXPLOSION_H

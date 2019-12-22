#pragma once
#include "Animation.h"

class Boom :
	public Animation
{
protected:
	const Animation_Name name = _Boom;

	float* spark_pos;
	float* spark_vel;
	float* spark_col;
	float* spark_fade;
	int num_sparks;
	float flare_pos;
	float flare_vel;

	int sparkle;
	bool reversed;

	long next_flare;

	float gravity = -.004; // m/s/s
	float dying_gravity;

public:
	Boom(LED_Group* new_group);

	~Boom();

	// Only define the functions you need the animation to use.
	// Otherwise the default functions in the Animation class are used.
	//void run();
	//void erase_prev_frame();
	void update_vars();
	void calculate_frame();

	void start_flare();
	void flare();
	void explode();
	void wait();
};


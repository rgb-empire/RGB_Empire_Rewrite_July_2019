#pragma once
#include "Animation.h"

class Boom_2 :
	public Animation
{
protected:
	const Animation_Name name = _Boom_2;

	float* spark_pos;
	float* spark_vel;
	float* spark_col;
	int num_sparks;

	float speed_dampening;

	long next_flare;

public:
	Boom_2(LED_Group* new_group);

	~Boom_2();

	// Only define the functions you need the animation to use.
	// Otherwise the default functions in the Animation class are used.
	//void run();
	//void erase_prev_frame();
	void update_vars();
	void calculate_frame();

	void explode();
	void wait();
};


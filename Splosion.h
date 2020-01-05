#pragma once
#include "Animation.h"

class Splosion :
	public Animation
{
protected:
	const Animation_Name name = _Splosion;

	float* spark_pos;
	float* spark_vel;
	float* spark_col;
	float* spark_fade;
	int num_sparks;

	int sparkle;

	long next_flare;

	float gravity = -.004; // m/s/s
	float dying_gravity;

public:
	Splosion(LED_Group* new_group);
	~Splosion();

	void erase_previous_frame();
	void calculate_frame();
};


#pragma once
#include "Animation.h"
class Rapid_Boom :
	public Animation
{
protected:
	const Animation_Name name = _Rapid_Boom;

public:
	Rapid_Boom(LED_Group* new_group);

	// Only define the functions you need the animation to use.
	// Otherwise the default functions in the Animation class are used.
	//void run();
	//void erase_prev_frame();
	//void update_vars();
	//void calculate_frame();
};



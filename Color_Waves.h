#pragma once

// 4 steps to seemless animation integration.

// Create a new animation using this template.
// Include this file in "Animations/All_Animations.h"
// Add the Animation_Name to the enum in "My_Enums.h"
// Add an entry in Animation::create(new_animation_name)

#include "Animation.h"

// These files are all included in Animation.h
//#include <vector>
//#include <typeinfo>
//#include <FastLED.h>
//#include "Oscillator.h"
//#include "My_Enums.h"
//#include "LED_Fixture.h"
//#include "Bug.h"

class Color_Waves :
	public Animation
{
protected:
	const Animation_Name name = _Color_Waves;

public:
	Color_Waves(LED_Group* new_group);

	// Only define the functions you need the animation to use.
	// Otherwise the default functions in the Animation class are used.
	//void run();
	//void erase_previous_frame();
	//void update_vars();
	void calculate_frame();
};


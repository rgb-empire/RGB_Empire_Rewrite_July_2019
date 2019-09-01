#pragma once

#include "Animation.h"
#include "arduino.h"
#include <vector>
#include <typeinfo>
#include <FastLED.h>
#include "Oscillator.h"
#include "My_Enums.h"
#include "LED_Fixture.h"
#include "Animation_Controller.h"

//extern std::vector<Animation_Class_And_Name> animation_list;

class Rainbow_Wave :
	public Animation
{
protected:
	const Animation_Name name = _Rainbow_Wave;

public:
	Rainbow_Wave();

	void draw_next_frame();
};

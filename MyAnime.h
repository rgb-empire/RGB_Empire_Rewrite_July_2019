#pragma once

#include "Animation.h"

// These files are all included in Animation.h
//#include <vector>
//#include <typeinfo>
//#include <FastLED.h>
//#include "Oscillator.h"
//#include "My_Enums.h"
//#include "LED_Fixture.h"
//#include "Bug.h"

class MyAnime :
	public Animation
{
protected:
	const Animation_Name name = _MyAnime;

	float start;
	float end;
	float backHue,startHue,deltaHue;
	uint8_t SizeCounter;

public:
	MyAnime(LED_Group *new_group);

	void update_vars();

	/*void erase_previous_frame();*/
	void calculate_frame();
};

#pragma once

// This class should contain all variables required to calculate an animation an how it changes over time.
// Floats are used to ensure smooth transitions, slow movements, and antialiasing are possible.
//constexpr int num_palettes = 10; // TODO: actually implement palettes

#include "Animation_Variable.h"
#include "My_Enums.h"
#include <vector>

class Animation_Variables
{
protected:
	

public:
	float range_start = 0.0;
	float range_end = 0.0;

	std::vector<Animation_Variable> vars;

	// TODO: maybe make a struct to handle an animation's palettes
	CRGBPalette16 palette_current = CRGBPalette16(CRGB::Black);
	CRGBPalette16 palette_next = CRGBPalette16(RainbowColors_p);
	int palette_current_ID = 0;
	int palette_next_ID = 0;
	int palette_cycle = 6000;	// =0 means palette does not cycle, >0 signifies the amount of time between palette changes in millis
	int palette_cycle_speed = 6;	// Speed at which to blend current palette to new palette. Usually beteen 1 and 48
	unsigned long palette_last_time = 0;// The time the palette last switched.

	// TODO: implement palettes
	// The palettes that are currently available for the animation to pick between.
	//bool palette_mask[num_palettes] = { true, false, true, false, true, true, true, false, true, true };

	int stage = 0;				// =0 means it has not started and must be initialized, >0 can be used to keep track of various stages

	Strip_Display_Mode strip_display_mode;

	float operator()(Variable_Name new_var_name);

	Bounded_Variable* operator()(Variable_Name new_var_name, Animation_Variable_Name new_ani_var_name);

	//Animation_Variables(float new_range_start, float new_range_end, float new_brightness, float new_position, float new_hue, float new_size, float density, float new_tFade);
	Animation_Variables(float new_range_start, float new_range_end);

	int random_palette();

	int random_palette_fade();
};


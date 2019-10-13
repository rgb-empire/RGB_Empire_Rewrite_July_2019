#include "Sinelon.h"

Sinelon::Sinelon(LED_Group* new_group)
	:Animation(new_group)
{
	START;

	vars.range_end = num_leds - 1;

	END;
}


void Sinelon::update_vars()
{
	START;

	Animation::update_vars();
	
	float new_start = vars(position) - vars(size) / 2;
	float new_end = vars(position) + vars(size) / 2;
	
	if (new_start < vars.range_start)
	{
		vars(position, a_speed)->make_positive();
	}
	if (new_end > vars.range_end - 1)
	{
		vars(position, a_speed)->make_negative();
	}

	if (new_start < 0)
	{
		new_start = 0;
	}
	if (new_end > num_leds - 1)
	{
		new_end = num_leds - 1;
	}

	start = new_start;
	end = new_end;

	END;
}


// Use calculate_frame to assign values the animation's pixel array
// by using the variables in the struct Animation_Variables vars.
// This example is from the Glitter class.

void Sinelon::calculate_frame()
{
	START;
	
	leds[(int)start] += CHSV(vars(hue), 255, vars(brightness) * (1 - (start - (int)start)));

	if (start < end) {
		for (int i = start + 1; i < end - 1; i++) {
			leds[i] = CHSV(vars(hue), 255, vars(brightness));
		}
	}
	else {
		for (int i = start; i <= vars.range_end; i++) {
			leds[i] += CHSV(vars(hue), 255, vars(brightness));
		}
		for (int i = end; i >= (int)vars.range_start && end > 1; i--) {
			leds[i] += CHSV(vars(hue), 255, vars(brightness));
		}
	}

	leds[(int)end] += CHSV(vars(hue), 255, vars(brightness) * (end - (int)end));

	//MEM;
	END;
}
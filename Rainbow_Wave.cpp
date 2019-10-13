#include "Rainbow_Wave.h"


Rainbow_Wave::Rainbow_Wave(LED_Group* new_group)
	:Animation(new_group)
{
	START;
	
	END;
}

void Rainbow_Wave::calculate_frame()
{
	START;

	led_set->fill_rainbow(vars(hue), vars(hue, a_offset)->value);
	//fill_rainbow(leds, num_leds, vars.hue, vars.hue_offset);

	END;
}

#include "Wave.h"

Wave::Wave(LED_Group* new_group)
	:Animation(new_group)
{
	START;

	vars(position, a_value)->eor = _eor_Loop;
	vars(fade, a_value)->value = 2;
	vars(size, a_value)->value = 70;
	vars(position, a_speed)->value = 1;

	END;
}

void Wave::erase_previous_frame()
{
	led_set->fadeToBlackBy(vars(fade));
}

void Wave::calculate_frame()
{
	for (int i = vars(position); i < vars(position) + vars(size); i++)
	{
		if (i < num_leds - 1)
		{
			leds[i] = CHSV(vars(hue), 255, vars(brightness) - i * (vars(brightness) / vars(size)));
		}
	}
}

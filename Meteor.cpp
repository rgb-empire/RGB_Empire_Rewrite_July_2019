#include "Meteor.h"

Meteor::Meteor(LED_Group* new_group)
	:Animation(new_group)
{
	START;

	name = _Meteor;

	vars(position, a_value)->eor = _eor_Loop;
	vars(position, a_speed)->value = float(random8(100,255)) / 200.0;
	vars(fade, a_value)->value = 3;
	vars(hue, a_speed)->value = 0;

	END;
}

void Meteor::erase_previous_frame()
{
	for (auto& pixel : *led_set)
	{
		if (random8(100) > 90) {
			pixel.fadeToBlackBy(vars(fade) * 30 * speed_scale_factor);
		}
		else
		{
			pixel.fadeToBlackBy(vars(fade) * speed_scale_factor);
		}
	}
}

void Meteor::calculate_frame()
{
	if (vars(position) == 0)
	{
		vars(hue, a_value)->value = random8();
		vars(position, a_speed)->value = float(random8(100,255)) / 200.0;
	}

	if (vars(position) < num_leds + vars(size))
	{
		leds[(int)vars(position)] = CHSV(vars(hue), 255, vars(brightness) * ((vars(position) - (int)vars(position))));

		for (int i = 1; i < vars(size); i++)
		{
			if (vars(position) - i > 0 && vars(position) - i < num_leds)
			{
				leds[(int)vars(position) - i] = CHSV(vars(hue), 255, vars(brightness));
			}
		}
	}
}

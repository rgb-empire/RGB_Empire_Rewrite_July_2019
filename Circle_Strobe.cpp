#include "Circle_Strobe.h"

Circle_Strobe::Circle_Strobe(LED_Group* new_group)
	:Animation(new_group)
{
	START;

	vars(fade, a_value)->value = 100;

	END;
}

void Circle_Strobe::erase_previous_frame()
{
	START;

	led_set->fadeToBlackBy(
		(vars(fade) * speed_scale_factor * speed_scale_factor_modifier) > 255 ? 255 :
		vars(fade) * speed_scale_factor * speed_scale_factor_modifier
	);

	END;
}

void Circle_Strobe::calculate_frame()
{
	START;

	for (auto& pixel : *led_set)
	{
		if (random(1000) < vars(density) * speed_scale_factor)
		{
			pixel = CRGB::White;
			pixel.fadeToBlackBy(255 - vars(brightness));
		}
	}

	END;
}
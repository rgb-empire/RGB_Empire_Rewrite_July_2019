#include "Drip_Splosion.h"

Drip_Splosion::Drip_Splosion(LED_Group* new_group)
	:Animation(new_group)
{
	START;

	vars(fade, a_value)->value = 100;

	END;
}

void Drip_Splosion::erase_previous_frame()
{
	START;

	led_set->fadeToBlackBy(
		(vars(fade) * speed_scale_factor * speed_scale_factor_modifier) > 255 ? 255 :
		vars(fade) * speed_scale_factor * speed_scale_factor_modifier
	);

	END;
}

void Drip_Splosion::calculate_frame()
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
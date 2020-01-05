#include "Strobe.h"

Strobe::Strobe(LED_Group* new_group)
	:Animation(new_group)
{
	START;

	vars(fade, a_value)->value = 100;

	offset = 0;
	next_strobe = millis() + speed_scale_factor_modifier * 150;

	END;
}

void Strobe::set_offset(int new_offset)
{
	offset = new_offset;
	next_strobe = millis() + speed_scale_factor_modifier * 150 + offset;
}

void Strobe::erase_previous_frame()
{
	START;

	led_set->fill_solid(CRGB::Black);

	END;
}

void Strobe::calculate_frame()
{
	START;

	long now = millis();

	if (now > next_strobe)
	{
		led_set->fill_solid(CRGB::White);

		if (speed_scale_factor_modifier == 0 || Animation_Controller::autoplay == true)
		{
			set_offset(random8());
		}
		else
		{
			next_strobe = now + (1000 - speed_scale_factor_modifier * 150);
		}
	}

	END;
}
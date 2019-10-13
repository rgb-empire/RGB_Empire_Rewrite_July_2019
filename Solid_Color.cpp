#include "Solid_Color.h"

Solid_Color::Solid_Color(LED_Group* new_group)
	:Animation(new_group)
{
	START;

	END;
}

void Solid_Color::calculate_frame()
{
	START;

	led_set->fill_solid(CHSV(vars(hue), 255, vars(brightness)));

	END;
}
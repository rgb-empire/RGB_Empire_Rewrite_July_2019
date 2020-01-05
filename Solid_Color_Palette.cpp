#include "Solid_Color_Palette.h"

Solid_Color_Palette::Solid_Color_Palette(LED_Group* new_group)
	:Animation(new_group)
{
	START;

	END;
}

void Solid_Color_Palette::calculate_frame()
{
	START;

	for (int i = 0; i < num_leds; i++)
	{
		leds[i] = ColorFromPalette(vars.palette_current, vars(hue), vars(brightness));
	}

	END;
}
#include "Confetti.h"

Confetti::Confetti(LED_Group* new_group)
	:Animation(new_group)
{
	START;

	vars(fade, a_value)->value = 5;

	END;
}


// Use erase_previous_frame to define how the animation resets itself after each frame.
// This example is the default function in the Animation base class.

void Confetti::erase_previous_frame()
{
	START;

	led_set->fadeToBlackBy(vars(fade) * speed_scale_factor);

	END;
}

// Use calculate_frame to assign values the animation's pixel array
// by using the variables in the struct Animation_Variables vars.
// This example is from the Glitter class.

void Confetti::calculate_frame()
{
	START;

	// random colored speckles that blink in and fade smoothly
	int pos = random16(num_leds);
	if (random8(10) < 5 * speed_scale_factor * speed_scale_factor_modifier)
	{
		leds[pos] += CHSV(vars(hue) + random8(64), 200, 255);
	}

	END;
}
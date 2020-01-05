#include "Dripper.h"


Dripper::Dripper(LED_Group* new_group)
	:Animation(new_group)
{
	START;

	vars(position, a_value)->value = 0;
	vars(position, a_value)->eor = _eor_Stop;
	vars(position, a_speed)->value = 0;
	vars(position, a_acceleration)->value = 0.001;
	vars(position, a_speed)->max = 2.0;

	END;
}

void Dripper::erase_previous_frame()
{
	led_set->fadeToBlackBy(40);
}

void Dripper::calculate_frame()
{
	START;

	//MEM;
	int tankSize = beatsin8(15 * speed_scale_factor_modifier / 3.0, num_leds / 75, num_leds * 0.3, 0);
	int dripSize = 2;
	//MEM;

	if (vars(position) >= num_leds - 2)
	{
		Serial.println("SET IT TO ZERO");
		vars(position, a_speed)->value = 0.2;
		splosion_trigger = true;
	}

	for (int i = 1; i < tankSize; i++)
	{
		leds[num_leds - i] = CHSV(vars(hue) + i * 2, 255, vars(brightness));
	}

		dripSize *= vars(position, a_speed)->value * speed_scale_factor_modifier;

		if (vars(position) + dripSize < num_leds)
		{
			for (int i = vars(position); i < vars(position) + dripSize; i++)
			{
				leds[num_leds - i - 1] = CHSV(vars(hue), 255, vars(brightness));
			}
		}
		else if (vars(position) < num_leds)
		{
			for (int i = 0; i < vars(position); i++)
			{
				leds[i] = CHSV(vars(hue), 255, vars(brightness));
			}

			Serial.println("SET IT TO ZERO 3");
			vars(position, a_value)->value = tankSize - 1;
			vars(position, a_speed)->value = 0;

			splosion_trigger = true;
		}
		else
		{
			Serial.println("SET IT TO ZERO 2");
			vars(position, a_value)->value = tankSize - 1;
			vars(position, a_speed)->value = 0;
		}

	END;
}
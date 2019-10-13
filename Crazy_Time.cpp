#include "Crazy_Time.h"

//Crazy_Time::Crazy_Time(LED_Fixture* new_fixture)
//	:Animation(new_fixture)
//{
//	START;
//
//	vars(position, a_value)->eor = _eor_Bounce;
//	vars(position, a_speed)->eor = _eor_Bounce;
//	vars(position, a_acceleration)->eor = _eor_Bounce;
//
//	vars(position, a_acceleration)->value = 0.02;
//
//	vars(position, a_speed)->min = -2;
//	vars(position, a_speed)->max = 2;
//
//	vars(size, a_value)->eor = _eor_Bounce;
//	vars(size, a_speed)->eor = _eor_Bounce;
//	vars(size, a_acceleration)->eor = _eor_Bounce;
//
//	vars(size, a_acceleration)->value = 0.01;
//	vars(size, a_value)->max = num_leds / 2.5;
//
//	vars(size, a_speed)->min = -2;
//	vars(size, a_speed)->max = 2;
//
//	vars(hue, a_value)->eor = _eor_Loop;
//	vars(hue, a_speed)->eor = _eor_Bounce;
//	vars(hue, a_acceleration)->eor = _eor_Bounce;
//
//	vars(hue, a_speed)->min = -1;
//	vars(hue, a_speed)->max = 1;
//
//	vars(hue, a_acceleration)->value = 0.01;
//
//	vars(fade, a_value)->max = 120;
//	vars(fade, a_value)->value = 40;
//
//	END;
//}

Crazy_Time::Crazy_Time(LED_Group* new_group)
	:Animation(new_group)
{
	START;

	vars(position, a_value)->eor = _eor_Bounce;
	vars(position, a_speed)->eor = _eor_Bounce;
	vars(position, a_acceleration)->eor = _eor_Bounce;

	vars(position, a_acceleration)->value = 0.02;

	vars(position, a_value)->value = random16(0, num_leds - 1);
	vars(position, a_speed)->min = -2;
	vars(position, a_speed)->max = 2;

	vars(size, a_value)->eor = _eor_Bounce;
	vars(size, a_speed)->eor = _eor_Bounce;
	vars(size, a_acceleration)->eor = _eor_Bounce;

	vars(size, a_acceleration)->value = 0.01;
	vars(size, a_value)->max = num_leds / 2.5;

	vars(size, a_speed)->min = -2;
	vars(size, a_speed)->max = 2;

	vars(hue, a_value)->eor = _eor_Loop;
	vars(hue, a_speed)->eor = _eor_Bounce;
	vars(hue, a_acceleration)->eor = _eor_Bounce;

	vars(hue, a_value)->value = random8();
	vars(hue, a_speed)->min = -1;
	vars(hue, a_speed)->max = 1;

	vars(hue, a_acceleration)->value = 0.01;

	vars(fade, a_value)->max = 120;
	vars(fade, a_value)->value = 40;

	modifier = (float)random8() / 64.0 - 2.0;

	END;
}

void Crazy_Time::erase_previous_frame()
{
	fadeToBlackBy(leds, num_leds, vars(fade) * speed_scale_factor);
}

void Crazy_Time::calculate_frame()
{
	START;

	EVERY_N_SECONDS(10)
	{
		modifier = (float)random(255) / 64.0 - 2.0;
	}

	vars(position, a_acceleration)->value = (float(beatsin16(10,0,1000) + beatsin16(13,0,1000) + beatsin16(1,0,500) + beatsin16(40,0,500))/ 6000.0 - 0.25) * modifier;

	vars(fade, a_value)->value = (float(beatsin16(10, 500, 1000) + beatsin16(13, 500, 1000) + beatsin16(1, 200, 500) + beatsin16(40, 50, 500)) / 216.0) * modifier;

	float new_start = vars(position) - vars(size) / 2;
	float new_end = vars(position) + vars(size) / 2;

	if (new_start < 0)
	{
		new_start = 0;
	}
	if (new_end > num_leds-1)
	{
		new_end = num_leds-1;
	}

	float start = new_start;
	float end = new_end;

	leds[(int)start] += CHSV(vars(hue), 255, vars(brightness) * (1.0 - (start - (int)start)));

	if (start < end) {
		for (int i = start + 1; i < end; i++) {
			leds[i] += CHSV(vars(hue), 255, vars(brightness));
		}
	}
	else {
		for (int i = start; i <= vars.range_end; i++) {
			leds[i] += CHSV(vars(hue), 255, vars(brightness));
		}
		for (int i = end; i >= (int)vars.range_start && end > 1; i--) {
			leds[i] += CHSV(vars(hue), 255, vars(brightness));
		}
	}

	leds[(int)end] += CHSV(vars(hue), 255, vars(brightness) * (1.0 - end - (int)end));

	END;
}

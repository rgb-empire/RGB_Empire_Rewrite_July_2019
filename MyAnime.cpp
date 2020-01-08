#include "MyAnime.h"



MyAnime::MyAnime(LED_Group *new_group)
	:Animation(new_group)
{
	START;

	vars.range_end = num_leds - 1;
	backHue,startHue = vars(hue);
	SizeCounter = 0;

	END;
}

void MyAnime::update_vars()
{
	START;

	Animation::update_vars();

	deltaHue = vars(hue) - startHue;

	float new_start = vars(position) - vars(size) / 2;
	float new_end = vars(position) + vars(size) / 2;

	if (new_start < vars.range_start)
	{
		vars(position, a_speed)->make_positive();
	}
	if (new_end > vars.range_end - 1)
	{
		vars(position, a_speed)->make_negative();
	}
	//if (random(250) > 249)
	//{
	//	vars(position, a_speed)->make_positive();
	//	//if (random(250) < 2){
	//	//	vars(size, a_speed)->value += vars(size);
	//	//}
	//}
	//if (random(250) < 1)
	//{
	//	vars(position, a_speed)->make_negative();
	//	if (random(250) > 248) {
	//		vars(size, a_speed)->value -= vars(size);
	//	}
	//}
	led_set->fill_solid(CRGB(0x222222));

		if (SizeCounter <= 20) 
		{
			if (random(100) < 2)
			{
				vars(size, a_speed)->value += 1;
				SizeCounter++;
			}
		}
		if(SizeCounter <= 0)
		{
			if (random(100) < 2)
			{
				vars(size, a_speed)->value -= 1;
				SizeCounter--;
			}
		}

	if (new_start < 0)
	{
		new_start = 0;
	}
	if (new_end > num_leds - 1)
	{
		new_end = num_leds - 1;
	}

	start = new_start;
	end = new_end;
	backHue = startHue - deltaHue;

	END;
}

void MyAnime::calculate_frame()
{
	START;

	leds[(int)start] += CHSV(vars(hue), 255, vars(brightness) * (1 - (start - (int)start)));

	if (start < end) {
		for (int i = start + 1; i < end - 1; i++) {
			leds[i] = CHSV(vars(hue), 255, vars(brightness));
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

	leds[(int)end] += CHSV(vars(hue), 255, vars(brightness) * (end - (int)end));

	END;
}

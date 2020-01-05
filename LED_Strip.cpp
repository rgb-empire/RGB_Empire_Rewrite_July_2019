// 
// 
// 

#include "LED_Strip.h"

void LED_Strip::print_info()
{
	Serial.print("Strip #");
	Serial.print(strip_index);
	Serial.println(" Information:");

	Serial.print("   ");
	Serial.print(strip_parameters.num_leds);
	Serial.println(" LEDs");

	Serial.print("   ");
	Serial.print(strip_parameters.leds_per_meter);
	Serial.println(" LEDs / meter");
}


LED_Strip::LED_Strip(int new_strip_index, CRGBSet* new_leds, Strip_Parameters new_strip_parameters)
	:strip_index(new_strip_index),
	leds(new_leds),
	strip_parameters(new_strip_parameters),
	strip_display_mode(_sdm_Default)
{
	START;

	arrangements = LED_Arrangement::create_strip_arrangements(new_leds, strip_parameters);

	MEM;

	END;
}

LED_Strip::~LED_Strip()
{
	
}

LED_Arrangement* LED_Strip::get_led_arrangement(Strip_Display_Mode new_strip_display_mode)
{
	START;

	for (auto& arrangement : arrangements)
	{
		if (arrangement->strip_display_mode == new_strip_display_mode)
		{
			END;
			return arrangement;
		}
	}

	END;

	return arrangements[_sdm_Default];
}

LED_Arrangement* LED_Strip::arrangement()
{
	START;

	END;

	return arrangements[strip_display_mode];
}

LED_Arrangement* LED_Strip::operator[](Strip_Display_Mode new_strip_display_mode)
{
	START;

	END;

	return arrangements[new_strip_display_mode];
}

void LED_Strip::print_arrangement_info(Strip_Display_Mode new_display_mode)
{
	START;

	Serial.println("LED Arrangement Info for Strip #" + (String)strip_index);
	
	for (auto& arrangement : arrangements)
	{
		arrangement->print_info();
	}


	END;
}

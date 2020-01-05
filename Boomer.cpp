#include "Boomer.h"

Boomer::Boomer(LED_Group* new_group)
	:Animation(new_group)
{
	START;

	int num_booms = num_leds / 100;

	for (int i = 0; i < num_booms; i++)
	{
		MEM;
		animations.emplace_back(Animation::create(_Boom, new_group));
		MEM;
	}

	END;
}
#include "Rapid_Boom.h"

Rapid_Boom::Rapid_Boom(LED_Group* new_group)
	:Animation(new_group)
{
	START;

	int num_booms = 2;

	animations.reserve(num_booms + 1);

	for (int i = 0; i < num_booms; i++)
	{
		animations.push_back(Animation::create(_Boom_2, new_group));
	}

	END;
}
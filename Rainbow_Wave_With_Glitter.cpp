#include "Rainbow_Wave_With_Glitter.h"

Rainbow_Wave_With_Glitter::Rainbow_Wave_With_Glitter(LED_Group* new_group)
	:Animation(new_group)
{
	START;

	animations.push_back(Animation::create(_Rainbow_Wave, new_group));
	animations.push_back(Animation::create(_Glitter, new_group));

	END;
}
#pragma once

#include "Animation.h"

class Rainbow_Wave_With_Glitter :
	public Animation
{
protected:
	const Animation_Name name = _Rainbow_Wave_With_Glitter;

public:
	Rainbow_Wave_With_Glitter(LED_Group* new_group);
};


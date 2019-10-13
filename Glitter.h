#pragma once

#include "Animation.h"

class Glitter :
	public Animation
{
protected:
	const Animation_Name name = _Glitter;

public:
	Glitter(LED_Group* new_group);

	void erase_previous_frame();

	void calculate_frame();

};


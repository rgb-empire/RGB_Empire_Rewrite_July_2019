#pragma once
#include "Animation.h"

class Circle_Strobe :
	public Animation
{
protected:
	const Animation_Name name = _Circle_Strobe;

public:
	Circle_Strobe(LED_Group* new_group);

	void erase_previous_frame();

	void calculate_frame();

};


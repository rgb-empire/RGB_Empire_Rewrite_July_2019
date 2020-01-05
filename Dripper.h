#pragma once
#include "Animation.h"
class Dripper :
	public Animation
{
protected:
	const Animation_Name name = _Dripper;

public:
	Dripper(LED_Group* new_group);

	void erase_previous_frame();
	void calculate_frame();
};


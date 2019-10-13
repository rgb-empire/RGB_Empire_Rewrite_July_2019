#pragma once
#include "Animation.h"
class Solid_Color :
	public Animation
{

protected:
	const Animation_Name name = _Solid_Color;

public:
	Solid_Color(LED_Group* new_group);


	void calculate_frame();
};


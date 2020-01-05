#pragma once
#include "Animation.h"
class Solid_Color_Palette :
	public Animation
{

protected:
	const Animation_Name name = _Solid_Color_Palette;

public:
	Solid_Color_Palette(LED_Group* new_group);


	void calculate_frame();
};


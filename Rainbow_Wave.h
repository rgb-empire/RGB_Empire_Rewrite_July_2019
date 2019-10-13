#pragma once

#include "Animation.h"

//extern std::vector<Animation_Class_And_Name> animation_list;

class Rainbow_Wave :
	public Animation
{
protected:
	const Animation_Name name = _Rainbow_Wave;

public:
	Rainbow_Wave(LED_Group* new_group);

	void calculate_frame();
};


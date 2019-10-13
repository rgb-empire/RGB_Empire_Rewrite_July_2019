#pragma once
#include "Animation.h"
class Crazy_Time :
	public Animation
{
protected:
	const Animation_Name name = _Crazy_Time;

	float modifier;

public:
	//Crazy_Time(LED_Fixture* new_fixture);
	Crazy_Time(LED_Group* new_group);

	void erase_previous_frame();

	void calculate_frame();
};


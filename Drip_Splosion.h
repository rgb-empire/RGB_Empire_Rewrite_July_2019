#pragma once
#include "Animation.h"

class Drip_Splosion :
	public Animation
{
protected:
	const Animation_Name name = _Drip_Splosion;

public:
	Drip_Splosion(LED_Group* new_group);

	void erase_previous_frame();

	void calculate_frame();

};


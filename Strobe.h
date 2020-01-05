#pragma once
#include "Animation.h"

class Strobe :
	public Animation
{
protected:
	const Animation_Name name = _Strobe;

	long next_strobe;
	int offset;

public:
	Strobe(LED_Group* new_group);

	void set_offset(int new_offset);

	void erase_previous_frame();

	void calculate_frame();

};


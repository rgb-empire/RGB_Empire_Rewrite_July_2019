#pragma once

// TODO: OMG I NEED TO FIGURE OUT HOW TO MAKE THE SPARKS FALL WITH THE MAIN METEOR BODY!!!

#include "Animation.h"
class Meteor :
	public Animation
{
protected:

public:
	Meteor(LED_Group* new_group);

	void erase_previous_frame();
	void calculate_frame();
};


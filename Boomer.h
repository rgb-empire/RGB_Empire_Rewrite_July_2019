#pragma once
#include "Animation.h"
class Boomer :
	public Animation
{
protected:
	const Animation_Name name = _Boomer;

public:
	Boomer(LED_Group* new_group);
};


#pragma once

#include "Bug.h"
#include "LED_Fixture.h"
#include "My_Enums.h"
#include "Animation.h"

class Transition
{
protected:
	Animation* current_animation;
	CRGB* cur_animation_frame;
	CRGBSet cur_animation_frame_set;
	
	Transition_Type type;
	Transition_Type temp_type;

	bool active;
	int total_time;
	long start_time;

	int num_leds;
	bool* mask;
	//float ratio;
	int num_transitioned;
	int new_num_transitioned;

	fract16 ratio;
	fract16 eased_ratio;

	Animation* next_animation;
	CRGB* next_animation_frame;
	CRGBSet next_animation_frame_set;

	Transition(Animation* new_current_animation);
	~Transition();

	void set_ratio();
	void start(Animation* new_next_animation);
	void finish();
	void show();

	void none();
	void fade();
	void wipe();
	void dissolve();

	friend class Animation_Controller;
	friend class Wifi_Class;
};


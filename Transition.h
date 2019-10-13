#pragma once

#include "Bug.h"
#include "LED_Fixture.h"
#include "My_Enums.h"
#include "Animation.h"

class Transition
{
protected:
	static Transition_Type type;
	static Transition_Type temp_type;

	static bool active;
	static int total_time;
	static long start_time;

	static bool* mask;
	static float ratio;
	static int num_transitioned;
	static int new_num_transitioned;
	static int num_leds;

	static void set_ratio();
	static void set_eased_ratio();
	static void start();
	static void reset();

	static void none(Animation* current_animation);
	static void fade(Animation* current_animation, Animation* next_animation);
	static void wipe(Animation* current_animation, Animation* next_animation);
	static void dissolve(Animation* current_animation, Animation* next_animation);

	friend class Animation_Controller;
	friend class Wifi_Class;
};


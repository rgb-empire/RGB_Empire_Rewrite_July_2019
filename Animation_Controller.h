#pragma once

#include "arduino.h"
#include <vector>
#include <typeinfo>
#include "FastLED.h"
#include "Oscillator.h"
#include "My_Enums.h"
#include "LED_Fixture.h"
#include "Animation.h"
#include "Transition.h"

// Factory method gets rid of all of this.
// Would still like a dynamically built list of animations, however.
// for some insight on how to maybe do this, visit
// https://www.reddit.com/r/Cplusplus/comments/cxli09/help_creating_a_vector_of_derived_classes/

// Define Animation_Class as a pointer to an animation object.
//typedef Animation* Animation_Class;

// Combine the pointer with an identifiable name.
//typedef struct Animation_Class_And_Name
//{
//	Animation_Class actual_class;
//	String name;
//};

// Create array of those structs to select an animation object from.
//static std::vector<Animation_Class_And_Name> animation_list;

class Animation_Controller
{
private:
	static Animation* current_animation;
	static Animation* next_animation;

	
	static int autoplay_min_time;
	static int autoplay_max_time;
	static long autoplay_next_time;

	int same_group_offset;

	// All speeds will be scaled as though they were running at this rate.
	// For example, if an animation is currently running at 200 fps, all speeds are cut in half.
	// If an animation is running at 50 fps, all speeds are doubled.
	const int target_fps = 100;

	friend class Wifi_Class;

public:
	static bool autoplay;
	Animation_Controller();

	void print_info();

	void run();

	void start_animation();

	static void change_animation(Animation_Name new_animation_name);

	void erase_prev_frame();

	void show();

	static void set_transition(Transition_Type new_transition_type);
};
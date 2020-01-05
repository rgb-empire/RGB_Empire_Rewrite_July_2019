#pragma once
// Every strip has 1 arrangement per display mode.

#include "LED_Group.h"
#include "My_Enums.h"
#include "Bug.h"

class LED_Arrangement
{
public:
	Strip_Display_Mode strip_display_mode;	// Display modes represent different ways to run animations on a given set of leds.

	std::vector<LED_Group*> led_groups;		// Each arrangement contains 1 or more groups.

	int num_groups;	// The number of groups the arrangement contains if groups cross strips.

	int size; // Size represents the total number of pixels an animation must generate.

	LED_Arrangement(Strip_Display_Mode new_strip_display_mode);

	void add(LED_Group* new_led_group);
	void add(LED_Group* new_led_group, int new_group_number);
	void add(LED_Arrangement* new_led_arrangement);
	void extend(LED_Arrangement* new_led_arrangement);

	int recalculate_size();

	void print_info();

	// Create_Strip_Arrangements.cpp
	static std::vector<LED_Arrangement*> create_strip_arrangements(CRGBSet* new_leds, Strip_Parameters new_strip_parameters);

	static std::vector<LED_Arrangement*> create_linear_arrangements(CRGBSet* new_leds, Strip_Parameters new_strip_parameters);
	static std::vector<LED_Arrangement*> create_folded_arrangements(CRGBSet* new_leds, Strip_Parameters new_strip_parameters);
	static std::vector<LED_Arrangement*> create_panel_arrangements(CRGBSet* new_leds, Strip_Parameters new_strip_parameters);
	static std::vector<LED_Arrangement*> create_circle_arrangements(CRGBSet* new_leds, Strip_Parameters new_strip_parameters);
	static std::vector<LED_Arrangement*> create_polygon_arrangements(CRGBSet* new_leds, Strip_Parameters new_strip_parameters);
	static std::vector<LED_Arrangement*> create_spiral_arrangements(CRGBSet* new_leds, Strip_Parameters new_strip_parameters);
	static std::vector<LED_Arrangement*> create_stalk_flower_arrangements(CRGBSet* new_leds, Strip_Parameters new_strip_parameters);

};
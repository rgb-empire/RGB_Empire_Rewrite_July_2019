#pragma once

// An LED_Group represents CRGBSets that will pull from the same pixel data.
// TODO: figure out how they could be offset from each other.

#include "FastLED.h"
#include "My_Enums.h"
#include "Bug.h"

class LED_Group
{
public:
	std::vector<CRGBSet*> leds;	// Vector of CRGBSets that refer directly to parts of the LED_Fixture g_leds.
	int group_number;	// The group number. Even groups on different strips will copy each other if their group number is the same.

	int size;			// The size of a group is equal to the largest CRGBSet it contains.
	int total_size;		// The total size is the sum of the sizes of all CRGBSets in the group.
	LED_Group(int new_group_number);

	void add_to_group(LED_Group* new_group);
	void add_to_group(CRGBSet* new_led_set);

	int recalculate_size();	// Returns the size of the largest CRGBSet in the group.
	int get_size();

	void print_info();

	LED_Group* change_group_number(int new_group_number);
};
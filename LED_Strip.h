// LED_Strip.h

// An LED Strip contains all information about a single LED strip in the physical world.

#ifndef _LED_STRIP_h
#define _LED_STRIP_h


#include "arduino.h"
#include "FastLED.h"
#include "My_Enums.h"
#include "vector"


struct LED_Group
{
	std::vector<CRGBSet*> leds;
	int group_number;
};

struct LED_Arrangement
{
	Display_Mode display_mode;
	std::vector<LED_Group> led_groups;
};


class LED_Strip
{
 protected:

	 int strip_index;

	 CRGBSet* leds;

	 int num_leds;
	 int leds_per_meter;
	 Shape shape;

	 int length_in_leds;
	 int width_in_leds;

	 std::vector<LED_Arrangement> led_arrangements;

	 friend class LED_Fixture;

	 void print_info();

	 
	 void divide_linear();
	 void divide_folded();
	 void divide_panel();
	 void divide_polygon();
	 

 public:

	LED_Strip(int new_strip_index, CRGBSet* leds, Strip_Parameters new_strip_parameters);
	~LED_Strip();

	LED_Arrangement* get_led_arrangement(Display_Mode new_display_mode);

};

#endif


// LED_Fixture.h

// The LED Fixture is a class that gives the Controller a single object
// to control and the Animation class one object to display on.

// As of right now, there is only one fixture per ESP32.

// There should also be methods that can alter how animations are displayed on the fixture.
// An example would be whether an animation runs in parallel on the strips or serially.

#ifndef _LED_FIXTURE_h
#define _LED_FIXTURE_h


#include "arduino.h"
#include "FastLED.h"
#include "vector"

#include "Fixture_Parameters.h"
#include "LED_Strip.h"

class LED_Fixture
{
protected:



	static Shape shape;

	static Fixture_Display_Mode fixture_display_mode;

	static CRGBArray<fixture_parameters.total_num_leds> g_leds;

	static std::vector<LED_Strip> led_strips;

public:
	static Fixture_Parameters fixture_params;

	static void create_strips();

	//LED_Fixture(Fixture_Parameters new_fixture_params);
	//~LED_Fixture();

	static void print_arrangement_info(Strip_Display_Mode new_display_mode);

	static void print_info();

	template <int pin>
	static void setStrip(int num_leds_so_far, int new_num_leds);

	template<int n>
	static void stripLoop(int num_leds_so_far);

	static LED_Arrangement* make_arrangement(Fixture_Display_Mode new_fixture_display_mode);
	static LED_Arrangement* make_arrangement();

	static void black_out();
};


#endif


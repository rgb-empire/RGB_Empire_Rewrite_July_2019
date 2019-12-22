// 
// 
// 

#include "Controller.h"
#include "Tasks.h"

Controller::Controller()
	//:display(Display::create()),
	//physical_input(Physical_Input())
{
	START;

	create_tasks();	// Start all the independently managed tasks.

	LED_Fixture::create_strips();

	// Print some info about the fixture and animation to make sure everything initialized correctly.
	LED_Fixture::print_info();

	//physical_input.check();	// TODO: implement this

	if (Wifi_Class::connected == false)
	{
		Wifi_Class::start_wifi();
	}

	//wifi_input.connect();	// TODO: implement this
	//wifi_input.check();	// TODO: implement this

	FastLED.setBrightness(255);

	MEM;

	END;
}

Controller::~Controller()
{
	
}

void Controller::run()
{
	START;

	// Check for input from buttons and wifi.
	//physical_input.check();
	Wifi_Class::get_udp_input();

	//EVERY_N_MILLISECONDS(250)
	//{
	//	display.update();	// Update the oled screen.
	//}

	//delay(20);

	FastLED_Show_ESP32();

	END;
}

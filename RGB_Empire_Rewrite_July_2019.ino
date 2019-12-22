//**********************//
//	Helper Files		//
//**********************//

#include "Bug.h"
#include <FastLED.h>
#include <Arduino.h>

//**********************//
//	Custom Libraries	//
//**********************//
#include "Controller.h"

// Create the pointer to our controller
Controller* controller;
Animation_Controller* animation_controller;

// The setup() function runs once each time the micro-controller starts
void setup()
{
	delay(500);

	Serial.begin(115200);

	// Delay to allow uploader time to fix unstable software.
	// Reduce or remove this for production.
	delay(500);

	START;

	// Create the controller object
	// It initializes everything based on the values in Fixture_Parameters.h
	controller = new Controller();
	animation_controller = new Animation_Controller();

	MEM;
	END;
}

void loop()
{
	START;

	EVERY_N_SECONDS(10) {
		Bug::check_memory();
	}

	controller->run();

	animation_controller->run();

	END;
}
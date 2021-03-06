// Fixture_Properties.h

// This should be the only file you need to change when installing the chip into a new fixture.

// I'm thinking there are several ways to define a fixture and it's properties:
// 1: 100% manually by defining all neccessary variables.
// 2: 50% manually by using preset configurations.
// 3: 0% manually by parsing a fixture_ID into all relevant parameters.


#ifndef _FIXTURE_PARAMETERS_h
#define _FIXTURE_PARAMETERS_h

#include "arduino.h"
#include "My_Enums.h"


constexpr int num_strips = 8;
constexpr int total_num_leds = 4000;

constexpr int volts = 5;
constexpr int milli_amps = 240000;

// { strip_pin, num_leds, leds_per_meter, shape, length_in_leds, width_in_leds }
constexpr Strip_Parameters strip_parameters[num_strips] = 
{
	{13,	300,	60,	Folded,	150,	2},
	{12,	300,	60,	Folded,	150,	2},
	{15,	300,	60,	Folded,	150,	2},
	{2,		300,	60,	Folded,	150,	2},
	{0,		300,	60,	Folded,	150,	2},
	{4,		300,	60,	Folded,	150,	2},
	{16,	300,	60,	Folded,	150,	2},
	{17,	300,	60,	Folded,	150,	2}
};

// { num_strips, total_num_leds, volts, milliamps, strip_parameters[] }
constexpr Fixture_Parameters fixture_parameters =
{
	num_strips,	total_num_leds,	volts,	milli_amps,
	strip_parameters

};

/*
template <uint8_t pin>
void addStrip() {
	FastLED.addLeds<WS2812B, pin, GRB>
		(g_leds, num_leds_so_far, num_leds_per_strip).setCorrection(TypicalLEDStrip);

	char buffer[100];
	sprintf(buffer, "Initialized pin %d with LED offset %d", pin, num_leds_so_far);
	Serial.println(buffer);

	num_leds_so_far += num_leds_per_strip;
}

template<uint8_t n>
void forLoop() {
	addStrip<strip_pin[n - 1]>();
	forLoop<n - 1>();
}

template<>
void forLoop<0>() {
	// Do nothing
}
*/

#endif


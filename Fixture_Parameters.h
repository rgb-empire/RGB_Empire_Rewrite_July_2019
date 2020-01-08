// Fixture_Properties.h

// This should be the only file you need to change when installing the chip into a new fixture.

// I'm thinking there are several ways to define a fixture and it's properties:
// 1: 100% manually by defining all neccessary variables.
// 2: 50% manually by using preset configurations.
// 3: 0% manually by parsing a fixture_ID into all relevant parameters.


#ifndef _FIXTURE_PROPERTIES_h
#define _FIXTURE_PROPERTIES_h

#include "arduino.h"
#include "My_Enums.h"


constexpr int num_strips = 8;			// You will also need to change the Strip_Parameter array size in Fixture_Parameters in My_Enums.h
constexpr int total_num_leds = 2304;	// TODO: make this programatic

constexpr int volts = 5;
constexpr int milli_amps = 300000;		// Maximum power output of the connected power supply. Setting this properly will prevent brown outs!

// { strip_pin, num_leds, leds_per_meter, shape, length_in_leds, width_in_leds }
constexpr Strip_Parameters strip_parameters[num_strips] = 
{
	{21,	164,	144,	_s_Linear,	164,	1},
	{19,	117,	100,	_s_Linear,	117,	1},
	{18,	117,	100,	_s_Linear,	117,	1},
	{15,	117,	100,	_s_Linear,	117,	1},
	{2,		117,	100,	_s_Linear,	117,	1},
	{0,		117,	100,	_s_Linear,	117,	1},
	{4,		117,	100,	_s_Linear,	117,	1},
	{5,		164,	144,	_s_Linear,	164,	1}
};

//constexpr Strip_Parameters strip_parameters[num_strips] =
//{
//	{21,	288,	60,	_s_Stalk_Flower,	288,	1},
//	{19,	288,	60,	_s_Stalk_Flower,	288,	1},
//	{18,	288,	60,	_s_Stalk_Flower,	288,	1},
//	{15,	288,	60,	_s_Stalk_Flower,	288,	1},
//	{2,		288,	60,	_s_Stalk_Flower,	288,	1},
//	{0,		288,	60,	_s_Stalk_Flower,	288,	1},
//	{4,		288,	60,	_s_Stalk_Flower,	288,	1},
//	{5,		288,	60,	_s_Stalk_Flower,	288,	1}
//};

constexpr Strip_Parameters stalk_flower_leaf =	{ 0,	300,	60,	_s_Folded,	150,	2 };
constexpr Strip_Parameters stalk_flower_stalk = { 0,	300,	60,	_s_Linear,	300,	1 };

//constexpr Strip_Parameters strip_parameters[num_strips] =
//{
//	{21,	144,	60,	_s_Linear,	144,	1},
//	{19,	144,	60,	_s_Linear,	144,	1},
//	{18,	144,	60,	_s_Linear,	144,	1},
//	{15,	144,	60,	_s_Linear,	144,	1},
//	{2,		144,	60,	_s_Linear,	144,	1},
//	{0,		144,	60,	_s_Linear,	144,	1},
//	{4,		144,	60,	_s_Linear,	144,	1},
//	{5,		144,	60,	_s_Linear,	144,	1},
//
//	{21,	144,	60,	_s_Folded,	72,	2},
//	{19,	144,	60,	_s_Folded,	72,	2},
//	{18,	144,	60,	_s_Folded,	72,	2},
//	{15,	144,	60,	_s_Folded,	72,	2},
//	{2,		144,	60,	_s_Folded,	72,	2},
//	{0,		144,	60,	_s_Folded,	72,	2},
//	{4,		144,	60,	_s_Folded,	72,	2},
//	{5,		144,	60,	_s_Folded,	72,	2}
//
//	
//};

// { strip_pin, num_leds, leds_per_meter, shape, length_in_leds, width_in_leds }
//constexpr Strip_Parameters strip_parameters[num_strips] = 
//{
//	{13,	600,	60,	_s_Stalk_Flower,	150,	4},
//	{12,	600,	60,	_s_Stalk_Flower,	150,	4},
//	{15,	600,	60,	_s_Stalk_Flower,	150,	4},
//	{2,		600,	60,	_s_Stalk_Flower,	150,	4},
//	{0,		600,	60,	_s_Stalk_Flower,	150,	4},
//	{4,		600,	60,	_s_Stalk_Flower,	150,	4},
//	{16,	600,	60,	_s_Stalk_Flower,	150,	4},
//	{17,	600,	60,	_s_Stalk_Flower,	150,	4}
//};

//constexpr Strip_Parameters strip_parameters[num_strips] =
//{
//	{13,	300,	144,	_s_Linear,	300,	1},
//	{12,	300,	144,	_s_Linear,	300,	1},
//	{26,	300,	144,	_s_Linear,	300,	1},
//	{2,		300,	144,	_s_Linear,	300,	1},
//	{0,		300,	144,	_s_Linear,	300,	1},
//	{4,		300,	144,	_s_Linear,	300,	1},
//	{16,	300,	144,	_s_Linear,	300,	1},
//	{17,	300,	144,	_s_Linear,	300,	1}
//};

// { num_strips, total_num_leds, volts, milliamps, strip_parameters[] }
constexpr Fixture_Parameters fixture_parameters =
{
	num_strips,	total_num_leds,	volts,	milli_amps,
	strip_parameters

};

#endif


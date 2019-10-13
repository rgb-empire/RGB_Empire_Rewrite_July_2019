// My_Enums.h

// I'll use this file to store any enumerated values and structs
// until I decide where to put them for realsies.

#ifndef _MY_ENUMS_h
#define _MY_ENUMS_h

#include "arduino.h"
#include <vector>
#include <FastLED.h>
#include "Bug.h"

#define NUM_AUTOPLAY_ANIMATIONS 12

enum Animation_Name
{
	_Rainbow_Wave,
	_Glitter,
	_Rainbow_Wave_With_Glitter,
	_Sinelon,
	_Solid_Color,
	_Meteor,
	_Multi_Meteor,
	_Wave,
	_Crazy_Time,
	_Mr_Poopy_Worm,
	_Color_Waves,
	_Confetti,

	_Artnet,

	_Default,
	_Base,
	_Template_Animation
};

// Shapes from 0-9 are strips.
// Shapes from 10-99 are fixtures.
enum Shape
{
	_s_Linear,
	_s_Folded,
	_s_Panel,
	_s_Circle,
	_s_Polygon,
	_s_Spiral,
	_s_Plant = 10,
	_s_Tree = 11,
	_s_Vertical_Lamp = 12
};

enum End_Of_Range
{
	_eor_Default,
	_eor_Loop,
	_eor_Bounce,
	_eor_Stop
};

enum Display_Display_Mode
{
	_ddm_Default,
	_ddm_SD_Card,
	_ddm_Test
};

// TODO: make an iterator for this enum
enum Strip_Display_Mode
{
	_sdm_Default,
	_sdm_Left_To_Right,
	_sdm_Around,
	_sdm_Middle_Out,
	_Master_Arrangement
};

enum Fixture_Display_Mode
{
	_fdm_Default,
	_fdm_Parallel,
	_fdm_Seperate,
	_fdm_Sequential,
	_fdm_Every_Other_Sequential,
};

enum Input_Type
{
	_it_Button,
	_it_Encoder,
	_it_Potentiometer,
	_it_Switch
};

enum Transition_Type
{
	_tt_Fade,
	_tt_Wipe,
	_tt_Dissolve,
	_tt_NUM_TRANSITIONS,
	_tt_Cycle,
	_tt_Random
};

// Use structs to make passing parameters into methods fast and easy.
struct Strip_Parameters
{
	const int strip_pin;
	const int num_leds;
	const int leds_per_meter;
	const Shape shape;
	const int length_in_leds;
	const int width_in_leds;
};

struct Fixture_Parameters
{
	const int num_strips;
	const int total_num_leds;
	const int volts;
	const int milli_amps;
	const Strip_Parameters* strip_parameters[8];
};

enum Variable_Name
{
	brightness,
	position,
	hue,
	size,
	density,
	fade
};

enum Bounded_Variable_Name
{
	b_value,
	b_min,
	b_max
};

enum Animation_Variable_Name
{
	a_value,
	a_speed,
	a_acceleration,
	a_offset,
	a_eor
};

#endif


// 
// 
// 

#include "LED_Fixture.h"

Fixture_Parameters LED_Fixture::fixture_params = fixture_parameters;
Fixture_Display_Mode LED_Fixture::fixture_display_mode = _fdm_Default;
Shape LED_Fixture::shape;
CRGBArray<fixture_parameters.total_num_leds> LED_Fixture::g_leds;
std::vector<LED_Strip> LED_Fixture::led_strips;

int fixture_num_leds = 0;

//**********************//
//	Protected Methods	//
//**********************//

void LED_Fixture::create_strips()
{
	START;

	// TODO: I don't think this is neccesary, but don't know how to get rid of it.
	int num_leds_so_far = 0;

	// Create the strips using this template.
	stripLoop<fixture_parameters.num_strips>(num_leds_so_far);

	FastLED.setMaxPowerInVoltsAndMilliamps(volts, milli_amps);

	g_leds.fill_solid(CRGB::Black);

	MEM;

	END;
}

void LED_Fixture::print_info()
{
	for (auto& strip : led_strips)
	{
		strip.print_info();
	}
}

LED_Arrangement* LED_Fixture::make_arrangement(Fixture_Display_Mode new_fixture_display_mode)
{
	START;

	LED_Arrangement* temp_arrangement = new LED_Arrangement(_Master_Arrangement);

	switch (new_fixture_display_mode)
	{
	case _fdm_Default:	// same as parallel
	case _fdm_Parallel:
		for (auto& strip : led_strips)
		{
			temp_arrangement->add(strip.arrangement());
		}
		break;

	case _fdm_Seperate:
		for (auto& strip : led_strips)
		{
			temp_arrangement->extend(strip.arrangement());
		}
		break;

	case _fdm_Sequential:
		//TODO: same as parallel for now, need to figure out how to manipulate groups for this
		for (auto& strip : led_strips)
		{
			temp_arrangement->add(strip.arrangement());
		}
		break;

	default:	// same as parallel
		for (auto& strip : led_strips)
		{
			temp_arrangement->add(strip.arrangement());
		}
	}

	END;

	return temp_arrangement;
}

LED_Arrangement* LED_Fixture::make_arrangement()
{
	START;

	LED_Arrangement* temp_arrangement = new LED_Arrangement(_Master_Arrangement);

	switch (fixture_display_mode)
	{
	case _fdm_Default:	// same as parallel
	case _fdm_Parallel:
		for (auto& strip : led_strips)
		{
			temp_arrangement->add(strip.arrangement());
		}
		break;

	case _fdm_Seperate:
		for (auto& strip : led_strips)
		{
			temp_arrangement->extend(strip.arrangement());
		}
		break;

	case _fdm_Sequential:
		//TODO: same as parallel for now, need to figure out how to manipulate groups for this
		for (auto& strip : led_strips)
		{
			temp_arrangement->add(strip.arrangement());
		}
		break;

	default:	// same as parallel
		for (auto& strip : led_strips)
		{
			temp_arrangement->add(strip.arrangement());
		}
	}

	END;

	return temp_arrangement;
}

void LED_Fixture::black_out()
{
	g_leds.fill_solid(CRGB::Black);
}

//**********************//
//	Public Methods		//
//**********************//

//LED_Fixture::LED_Fixture(Fixture_Parameters new_fixture_params)
//	:fixture_params(new_fixture_params),
//	fixture_display_mode(_fdm_Default)
//{
//	START;
//
//	create_strips();
//
//	//initilize_vars();
//
//	END;
//
//}

//LED_Fixture::~LED_Fixture()
//{
//}


void LED_Fixture::print_arrangement_info(Strip_Display_Mode new_display_mode)
{
	START;

	for (auto& strip : led_strips)
	{
		strip.print_arrangement_info(new_display_mode);
	}

	END;
}

template <int pin>
void LED_Fixture::setStrip(int num_leds_so_far, int new_num_leds)
{
	FastLED.addLeds<WS2812B, pin, GRB>
		(g_leds, num_leds_so_far, new_num_leds).setCorrection(TypicalLEDStrip);

}

template<int n>
void LED_Fixture::stripLoop(int num_leds_so_far)
{
	setStrip<strip_parameters[n - 1].strip_pin>(num_leds_so_far, strip_parameters[n - 1].num_leds);
	num_leds_so_far += strip_parameters[n - 1].num_leds;

	led_strips.push_back(
		LED_Strip
		(n - 1,
			new CRGBSet(g_leds(fixture_num_leds, num_leds_so_far - 1)),
			strip_parameters[n - 1])
	);

	fixture_num_leds = num_leds_so_far;

	stripLoop<n - 1>(num_leds_so_far);
}

template<>
void LED_Fixture::stripLoop<0>(int num_leds_so_far) {};

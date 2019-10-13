#include "Color_Waves.h"

Color_Waves::Color_Waves(LED_Group* new_group)
	:Animation(new_group)
{
	START;

	END;
}

// Use calculate_frame to assign values the animation's pixel array
// by using the variables in the struct Animation_Variables vars.
// This example is from the Glitter class.

void Color_Waves::calculate_frame()
{
	START;

	static uint16_t sPseudotime = 0;
	static uint16_t sLastMillis = 0;
	static uint16_t sHue16 = 0;

	// uint8_t sat8 = beatsin88( 87, 220, 250);
	uint8_t brightdepth = beatsin88(341 * speed_scale_factor_modifier, 96, 224);
	uint16_t brightnessthetainc16 = beatsin88(203 * speed_scale_factor_modifier, (25 * 256), (40 * 256));
	uint8_t msmultiplier = beatsin88(147 * speed_scale_factor_modifier, 23, 60);

	uint16_t hue16 = sHue16;//gHue * 256;
	uint16_t hueinc16 = beatsin88(113 * speed_scale_factor_modifier, 300, 1500);

	uint16_t ms = millis();
	uint16_t deltams = ms - sLastMillis;
	sLastMillis = ms;
	sPseudotime += deltams * msmultiplier;
	sHue16 += deltams * beatsin88(400 * speed_scale_factor_modifier, 5, 9);
	uint16_t brightnesstheta16 = sPseudotime;

	for (uint16_t i = 0; i < num_leds; i++) {
		hue16 += hueinc16;
		uint8_t hue8 = hue16 / 256;
		uint16_t h16_128 = hue16 >> 7;
		if (h16_128 & 0x100) {
			hue8 = 255 - (h16_128 >> 1);
		}
		else {
			hue8 = h16_128 >> 1;
		}

		brightnesstheta16 += brightnessthetainc16;
		uint16_t b16 = sin16(brightnesstheta16) + 32768;

		uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
		uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
		bri8 += (255 - brightdepth);

		uint8_t index = hue8;
		//index = triwave8( index);
		index = scale8(index, 240);

		//CRGB newcolor = ColorFromPalette(palette, index, bri8);
		CRGB newcolor = ColorFromPalette(RainbowColors_p, index, bri8);

		uint16_t pixelnumber = i;
		pixelnumber = (num_leds - 1) - pixelnumber;

		nblend(leds[pixelnumber], newcolor, 128);
	}

	END;
}
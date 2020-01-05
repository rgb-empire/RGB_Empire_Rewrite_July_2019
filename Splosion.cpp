#include "Splosion.h"


Splosion::Splosion(LED_Group* new_group)
	:Animation(new_group)
{
	START;

	num_sparks = num_leds / 4;

	spark_pos = new float[num_sparks];
	spark_vel = new float[num_sparks];
	spark_col = new float[num_sparks];
	spark_fade = new float[num_sparks];

	END;
}

Splosion::~Splosion()
{
	delete spark_pos;
	delete spark_vel;
	delete spark_col;
	delete spark_fade;
}

void Splosion::erase_previous_frame()
{
	led_set->fadeToBlackBy(40);
}

void Splosion::calculate_frame()
{
	START;

	if (splosion_trigger == true)
	{
		vars.random_palette();

		for (int i = 0; i < num_sparks; i++) {

			spark_pos[i] = 0;
			spark_vel[i] = (float(random16(5000, 30000)) / 10000.0) * speed_scale_factor_modifier/2.2;
			spark_col[i] = abs(spark_vel[i]) * 500; // set colors before scaling velocity to keep them bright 
			spark_col[i] = constrain(spark_col[i], 0, 240);
			spark_fade[i] = 1.0 - 0.01 * speed_scale_factor_modifier / 3.0;

		}
		spark_col[0] = 255; // this will be our known spark 
		dying_gravity = 0.02 * speed_scale_factor_modifier / 2.0;
		sparkle = random16(350, 1500);

	}


	for (int i = 0; i < num_sparks; i++) {
		spark_pos[i] += spark_vel[i];
		//spark_pos[i] = constrain(spark_pos[i], 0, num_leds);
		spark_vel[i] -= dying_gravity;
		spark_col[i] *= spark_fade[i];

		if (random16(0, sparkle) < 10 && spark_fade[i] > 0.98 && spark_col[i] < 200) {
			spark_col[i] = random8(230, 240);
			spark_fade[i] = 0.97;
		}


		if (spark_pos[i] < num_leds && spark_pos[i] >= 0) {
			//if (reversed) {
			//	leds[num_leds - 1 - int(spark_pos[i])] = ColorFromPalette(vars.palette_current, spark_col[i], spark_col[i]);
			//}
			//else {
			leds[int(spark_pos[i])] += ColorFromPalette(vars.palette_current, spark_col[i], spark_col[i]);
			//}
			if (random16(0, sparkle) < 30 && spark_fade[i] > 0.98 && spark_col[i] < 200) {
				leds[int(spark_pos[i])] = CRGB::White;
			}
		}
	}


	END;
}
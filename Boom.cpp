#include "Boom.h"
#include <time.h>

Boom::Boom(LED_Group* new_group)
	:Animation(new_group)
{
	START;

	num_sparks = num_leds / 2;

	spark_pos = new float[num_sparks];
	spark_vel = new float[num_sparks];
	spark_col = new float[num_sparks];
	spark_fade = new float[num_sparks];
	flare_pos = 0;
	vars.stage = 0;

	END;
}

Boom::~Boom()
{
	delete spark_pos;
	delete spark_vel;
	delete spark_col;
	delete spark_fade;
}


void Boom::update_vars()
{
	START;

	switch (vars.stage) {

	case 0:
		start_flare();
		break;
	case 1:
		flare();
		break;
	case 2:
		explode();
		break;
	case 3:
		wait();
		break;
	default:
		vars.stage = 0;
	}

	END;
}


// Use calculate_frame to assign values the animation's pixel array
// by using the variables in the struct Animation_Variables vars.
// This example is from the Glitter class.

void Boom::calculate_frame()
{
	START;

	//leds[(int)start] += CHSV(vars(hue), 255, vars(brightness) * (1 - (start - (int)start)));

	//if (start < end) {
	//	for (int i = start + 1; i < end - 1; i++) {
	//		leds[i] = CHSV(vars(hue), 255, vars(brightness));
	//	}
	//}
	//else {
	//	for (int i = start; i <= vars.range_end; i++) {
	//		leds[i] += CHSV(vars(hue), 255, vars(brightness));
	//	}
	//	for (int i = end; i >= (int)vars.range_start && end > 1; i--) {
	//		leds[i] += CHSV(vars(hue), 255, vars(brightness));
	//	}
	//}

	//leds[(int)end] += CHSV(vars(hue), 255, vars(brightness) * (end - (int)end));

	////MEM;
	END;
}

void Boom::start_flare() {

	vars.random_palette();

	flare_pos = 0;
	flare_vel = float(random16(120, 290)) / 300; // trial and error to get reasonable range
	vars(brightness, a_value)->value = 255;

	// initialize launch sparks
	for (int i = 0; i < 5; i++) {
		spark_pos[i] = 0;
		spark_vel[i] = (float(random8()) / 255) * (flare_vel / 5); // random around 20% of flare velocity 
		spark_col[i] = spark_vel[i] * 1000;
		spark_col[i] = constrain(spark_col[i], 0, 255);
	}

	if (random8() < 128) {
		reversed = true;
		//gravity = abs(gravity);
	}
	else {
		reversed = false;
		//gravity = -abs(gravity);
	}

	vars.stage++;
}

/*
 * Send up a flare
 *
 */
void Boom::flare() {

	// sparks
	for (int i = 0; i < 5; i++) {
		spark_pos[i] += spark_vel[i];
		//spark_pos[i] = constrain(spark_pos[i], 0, num_leds);
		spark_vel[i] += gravity;
		spark_col[i] += -.8;
		//spark_col[i] = constrain(spark_col[i], 0, 255);
		if (spark_pos[i] < num_leds && spark_pos[i] >= 0) {
			if (reversed) {
				leds[num_leds - 1 - int(spark_pos[i])] = HeatColor(spark_col[i]);
				leds[num_leds - 1 - int(spark_pos[i])] %= 50; // reduce brightness to 50/255
			}
			else {
				leds[int(spark_pos[i])] = HeatColor(spark_col[i]);
				leds[int(spark_pos[i])] %= 50; // reduce brightness to 50/255
			}
		}
	}

	// flare
	if (flare_pos < num_leds && flare_pos >= 0) {
		if (reversed) {
			leds[num_leds - 1 - int(flare_pos)] = CHSV(0, 0, vars(brightness));
		}
		else {
			leds[int(flare_pos)] = CHSV(0, 0, vars(brightness));
		}
	}

	flare_pos += flare_vel;
	flare_vel += gravity;

	vars(brightness, a_value)->value *= .989;

	if (flare_vel < 0) {
		// initialize sparks
		for (int i = 0; i < num_sparks; i++) {

			spark_pos[i] = flare_pos;
			spark_vel[i] = (float(random16(0, 20000)) / 10000.0) - 1.0; // from -1 to 1 
			spark_col[i] = abs(spark_vel[i]) * 500; // set colors before scaling velocity to keep them bright 
			spark_col[i] = constrain(spark_col[i], 0, 255);
			spark_vel[i] *= (flare_pos / num_leds); // proportional to height 
			spark_fade[i] = 0.98;

		}
		spark_col[0] = 255; // this will be our known spark 
		dying_gravity = 0.98;
		sparkle = random8();

		if (sparkle < 50) {
			sparkle = 0;
		}

		vars.stage++;
	}
}

/*
 * Explode!
 *
 * Explosion happens where the flare ended.
 * Size is proportional to the height.
 */
void Boom::explode() {

	int total_col = 0;
	// as long as our known spark is lit, work with all the sparks
	for (int i = 0; i < num_sparks; i++) {
		spark_pos[i] += spark_vel[i];
		//spark_pos[i] = constrain(spark_pos[i], 0, num_leds);
		spark_vel[i] *= dying_gravity;
		spark_col[i] *= spark_fade[i];

		if (255 - random16(0, sparkle) > 254 && spark_fade[i] > 0.97 && spark_col[i] < 200 && spark_col[i] > 8) {
			spark_col[i] = random8(230, 255);
			spark_fade[i] = 0.95;
		}

		total_col += spark_col[i];

		if (spark_pos[i] < num_leds && spark_pos[i] >= 0) {
			if (reversed) {
				leds[num_leds - 1 - int(spark_pos[i])] = ColorFromPalette(vars.palette_current, spark_col[i], spark_col[i]);
			}
			else {
				leds[int(spark_pos[i])] = ColorFromPalette(vars.palette_current, spark_col[i], spark_col[i]);
			}
		}
	}


	if (total_col < 5) {
		next_flare = (uint32_t)(clock() * 1000 / CLOCKS_PER_SEC) + random16(0, 600);
		vars.stage++;
	}

}

void Boom::wait() {

	if ((uint32_t)(clock() * 1000 / CLOCKS_PER_SEC) > next_flare) {
		vars.stage = 0;
	}
}
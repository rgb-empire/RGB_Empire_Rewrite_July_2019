#include "Boom_2.h"
#include <time.h>

Boom_2::Boom_2(LED_Group* new_group)
	:Animation(new_group)
{
	START;

	num_sparks = num_leds / 8;

	spark_pos = new float[num_sparks];
	spark_vel = new float[num_sparks];
	spark_col = new float[num_sparks];

	vars.stage = 0;

	speed_dampening = 0.98;

	END;
}

Boom_2::~Boom_2()
{
	delete spark_pos;
	delete spark_vel;
	delete spark_col;
}


void Boom_2::update_vars()
{
	START;

	switch (vars.stage) {

	case 0:
		explode();
		break;
	case 1:
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

void Boom_2::calculate_frame()
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

/*
 * Explode!
 *
 * Explosion happens where the flare ended.
 * Size is proportional to the height.
 */
void Boom_2::explode() {

	if (spark_col[0] > 0.5) { // as long as our known spark is lit, work with all the sparks
		for (int i = 0; i < num_sparks; i++) {
			spark_pos[i] += spark_vel[i];
			//spark_pos[i] = constrain(spark_pos[i], 0, num_leds);
			spark_vel[i] *= speed_dampening;
			spark_col[i] *= .95;

			if (spark_pos[i] < num_leds && spark_pos[i] >= 0) {

				leds[int(spark_pos[i])] = ColorFromPalette(vars.palette_current, spark_col[i], spark_col[i]);
			}
		}
	}
	else {

		vars.random_palette();

		int position = random16(9, num_leds - 10);
		float size = (float(random16(5000, 15000)) / 7000.0);

		for (int i = 0; i < num_sparks; i++) {

			spark_pos[i] = position;
			spark_vel[i] = (float(random16(0, 20000)) / 10000.0) - 1.0; // from -1 to 1 
			spark_col[i] = abs(spark_vel[i]) * 500; // set colors before scaling velocity to keep them bright 
			spark_col[i] = constrain(spark_col[i], 0, 255);
			spark_vel[i] *= size;
		}
		spark_col[0] = 255; // this will be our known spark 

		next_flare = (uint32_t)(clock() * 1000 / CLOCKS_PER_SEC) + random16(0, 600);
		vars.stage ++;
	}

}

void Boom_2::wait() {  

	if ((uint32_t)(clock() * 1000 / CLOCKS_PER_SEC) > next_flare) {
		vars.stage = 0;
	}
}
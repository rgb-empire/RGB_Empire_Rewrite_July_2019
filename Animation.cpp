// 
// 
// 

#include "Animation.h"

// Update the animation variables to calculate the next frame.
// The default way exactly as you would expect.
// You can change this in the specific animation if you want.
// TODO currently incomplete
void Animation::update_vars()
{
	//START;

	vars.vars[brightness].update();
	vars.vars[position].update();
	vars.vars[hue].update();
	vars.vars[size].update();
	vars.vars[density].update();
	vars.vars[fade].update();

	if (vars.palette_cycle != 0)
	{
		unsigned long now = millis();

		// abs() allows palette_cycle to be positive or negative0
		if (now - vars.palette_last_time > abs(vars.palette_cycle))
		{
			vars.random_palette_fade();
			vars.palette_last_time = now;
		}
	}

	nblendPaletteTowardPalette(vars.palette_current, vars.palette_next, vars.palette_cycle_speed);

	//END;
}

void Animation::erase_previous_frame()
{
	START;

	for (auto& pixel : *led_set)
	{
		pixel = CRGB::Black;
	}

	END;
}

Animation::Animation(Animation_Name new_animation_name)
	:arrangement(LED_Fixture::make_arrangement(_fdm_Seperate)),
	num_leds(arrangement->size),
	leds(new CRGB[num_leds]),
	led_set(new CRGBSet(leds, num_leds)),
	vars(Animation_Variables(0, num_leds - 1))
{
	//P(arrangement->num_groups);
	if (strip_parameters[0].shape == _s_Stalk_Flower && new_animation_name == _Drip_Splosion) {

		Serial.println("IM HEREEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE");

		int i = 0;

		for (auto& group : arrangement->led_groups)
		{
			if (i % 2 == 1)
			{
				Serial.println("DRIPPPPPERRRRRR");
				animations.push_back(create(_Dripper, group));
			}
			else
			{
				Serial.println("SPLOSIONNNNNNNN");
				animations.push_back(create(_Splosion, group));
			}
			
			i++;
		}

	}
	else
	{
		for (auto& group : arrangement->led_groups)
		{
			animations.push_back(create(new_animation_name, group));
		}
	}


	//Serial.println("what the heck BACK-2-BACK = " + (String)led_set->len);

	fill_solid(leds, num_leds, CRGB::Black);

	MEM;
}

Animation::Animation()
	:arrangement(LED_Fixture::make_arrangement()),
	num_leds(arrangement->size),
	leds(new CRGB[num_leds]),
	led_set(new CRGBSet(leds, num_leds)),
	vars(Animation_Variables(0,num_leds - 1))
{
	START;



	//Serial.println("what the heck = " + (String)led_set->len);

	fill_solid(leds, num_leds, CRGB::Black);

	MEM;
	END;
}

Animation::Animation(LED_Group* new_group)
	:arrangement(new LED_Arrangement(_sdm_Default)),
	num_leds(new_group->size),
	leds(new CRGB[num_leds]),
	led_set(new CRGBSet(leds, num_leds)),
	vars(Animation_Variables(0, num_leds - 1))
{
	arrangement->add(new_group, 0);

	//Serial.println("what the heck BACK-2-BACK = " + (String)led_set->len);

	fill_solid(leds, num_leds, CRGB::Black);
}


Animation* Animation::create(Animation_Name new_animation_name)
{
	START;

	END;

	//if (new_animation_name != _Artnet)
	//{
		return new Animation(new_animation_name);
	//}
	//else
	//{
	//	return new Artnet(new_fixture, new_fixture->make_arrangement(_fdm_Sequential)->led_groups[0]);
	//}

		//switch (new_animation_name)
		//{
		//case _Default:
		//	return new Crazy_Time(new_fixture);
		//case _Rainbow_Wave:
		//	return new Rainbow_Wave(new_fixture);
		//case _Glitter:
		//	return new Glitter(new_fixture);
		//case _Rainbow_Wave_With_Glitter:
		//	return new Rainbow_Wave_With_Glitter(new_fixture);
		//	//case _Random_Rainbow_Wave:			return new Random_Rainbow_Wave;
		//case _Sinelon:
		//	return new Sinelon(new_fixture);
		//case _Mr_Poopy_Worm:
		//	return new Mr_Poopy_Worm(new_fixture);
		//case _Solid_Color:
		//	return new Solid_Color(new_fixture);
		//case _Meteor:
		//	return new Meteor(new_fixture);
		//case _Wave:
		//	return new Wave(new_fixture);
		//case _Crazy_Time:
		//	return new Crazy_Time(new_fixture);
		//case _Artnet:
		//	return new Artnet(new_fixture);
		//default:
		//	return new Rainbow_Wave(new_fixture);
		//}
}

Animation* Animation::create(Animation_Name new_animation_name, LED_Group* new_group)
{
	START;
	
	END;

	//P(new_animation_name);

	//new_animation_name = Animation_Name(random8(0, 8));
	//new_animation_name = _Rainbow_Wave;

	switch (new_animation_name)
	{
	case _Default:
		return new MyAnime(new_group);
	case _Rainbow_Wave:
		return new Rainbow_Wave(new_group);
	case _Glitter:
		return new Glitter(new_group);
	case _Rainbow_Wave_With_Glitter:
		return new Rainbow_Wave_With_Glitter(new_group);
		//case _Random_Rainbow_Wave:			return new Random_Rainbow_Wave;
	case _Sinelon:
		return new Sinelon(new_group);
	case _Mr_Poopy_Worm:
		return new Mr_Poopy_Worm(new_group);
	case _Solid_Color:
		return new Solid_Color(new_group);
	case _Meteor:
		return new Meteor(new_group);
	case _Multi_Meteor:
		return new Multi_Meteor(new_group);
	case _Wave:
		return new Wave(new_group);
	case _Crazy_Time:
		return new Crazy_Time(new_group);
	case _Confetti:
		return new Confetti(new_group);
	case _Color_Waves:
		return new Color_Waves(new_group);
	case _Boom:
		return new Boom(new_group);
	case _Boom_2:
		return new Boom_2(new_group);
	case _Rapid_Boom:
		return new Rapid_Boom(new_group);
	case _Drip_Splosion:
		return new Dripper(new_group);
	case _Strobe:
		return new Strobe(new_group);
	case _Circle_Strobe:
		return new Circle_Strobe(new_group);
	case _Dripper:
		return new Dripper(new_group);
	case _Splosion:
		return new Splosion(new_group);
	case _Boomer:
		return new Boomer(new_group);
	case _Solid_Color_Palette:
		return new Solid_Color_Palette(new_group);
	case _Artnet:
		return new Artnet(new_group);
	case _MyAnime:
		return new MyAnime(new_group);
	default:
		return new Crazy_Time(new_group);
	}
}

void Animation::add_aniamtion(Animation_Name new_animation_name, LED_Group* new_group)
{

}

Animation::~Animation()
{
	START;

	//print_info();

	//THING;

	for (auto& animation : animations)
	{
		delete animation;
	}

	//THING;

	delete leds;

	//THING;

	delete led_set;

	delete arrangement;

	//THING;

	//MEM;
	END;
}

void Animation::print_info()
{
	START;

	Serial.print("Animation #");
	//Serial.print(animation_ID);
	Serial.println(" Information:");

	Serial.print("   Position = ");
	//Serial.println(vars.position);

	Serial.print("   Hue = ");
	//Serial.println(vars.hue);

	END;
}

void Animation::print_arrangement_info()
{
	START;

	//int i = 0;

	//Serial.println("LED Arrangement Info for the Current Animation");

	//for (auto& arrangement : led_arrangements->arrangements)
	//{
	//	THING;

	//	for (auto& group : arrangement.led_groups)
	//	{
	//		Serial.println("      LED_Arrangement #" + (String)i++);
	//		for (auto& led_set : group.leds)
	//		{
	//			Serial.println("            -" + (String)led_set.len + " LEDs");
	//		}
	//	}
	//}

	END;
}

void Animation::run()
{
	START;
	//MEM;

	erase_previous_frame();

	//THING;

	update_vars();

	//THING;

	calculate_frame();

	//THING;

	for (auto& animation : animations) {
		//THING;
		animation->run();
	}

	//MEM;
	END;
}

//void Animation::erase_previous_frame()
//{
//	START;
//
//	for (LED_Arrangement& arrangement : led_arrangements->arrangements)
//	{
//		for (LED_Group& group : arrangement.led_groups)
//		{
//			for (CRGBSet& led_set : group.leds)
//			{
//				led_set.fill_solid(CRGB::Black);
//			}
//		}
//	}
//
//	END;
//}

void Animation::calculate_frame()
{
	START;
	//MEM;

	//MEM;
	END;
}

int Animation::next(int cur, int dir, bool mask[])
{
	START;

	int mask_size = sizeof(mask);
	int next = cur;
	bool finished = false;

	int increment;

	if (dir > 0)
	{
		increment = 1;
	}
	else
	{
		increment = -1;
	}

	do
	{
		next = (next + increment);

		// Keep next within the bounds of the mask array.
		if (next > mask_size - 1)
		{
			next = 0;
		}
		else if (next < 0)
		{
			next = mask_size - 1;
		}

		if (mask[next])			// found the next available index
		{
			finished = true;
		}
		else if (next == cur)	// have gone all the way Around the mask array
		{
			finished = true;
		}
	}
	while (!finished);

	END;

	return next;
}

CRGB* Animation::next_frame()
{
	START;

	int cur_led_num = 0;
	int cur_group = 0;

	//P(arrangement->num_groups);
	//P(arrangement->size);

	if (arrangement->num_groups == 1)
	{
		for (auto& animation : animations)
		{
			CRGB* next_frame = animation->next_frame();

			for (int i = 0; i < animation->num_leds; i++)
			{
				leds[i + cur_led_num] += next_frame[i];
			}
		}
	}
	else
	{
		if (!animations.empty())
		{
			for (auto& group : arrangement->led_groups)
			{

				CRGB* next_frame = animations[cur_group]->next_frame();

				for (int i = 0; i < animations[cur_group]->num_leds; i++)
				{
					leds[i + cur_led_num] += next_frame[i];
				}

				cur_led_num += animations[cur_group++]->num_leds;

			}
		}
	}

	END;

	return leds;
}

void Animation::change_var(Variable_Name new_var_name, Animation_Variable_Name new_ani_var_name, float new_value)
{
	vars(new_var_name, new_ani_var_name)->value = new_value;

	for (auto& animation : animations)
	{
		animation->vars(new_var_name, new_ani_var_name)->value = new_value;
	}
}

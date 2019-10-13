#include "Animation_Controller.h"

Animation* Animation_Controller::current_animation;
Animation* Animation_Controller::next_animation;

Animation_Controller::Animation_Controller()
{
	START;

	LED_Fixture::print_arrangement_info(_sdm_Default);

	start_animation();

	current_animation->print_arrangement_info();

	MEM;
	END;
}

void Animation_Controller::print_info()
{
	START;
	END;
}

void Animation_Controller::run()
{
	START;

	speed_scale_factor = FastLED.getFPS() > 0 ? float(100.0 / FastLED.getFPS() * speed_scale_factor_modifier) : 0.5;

	erase_prev_frame();

	EVERY_N_SECONDS(10)
	{
		//change_animation(Animation_Name(random8(0,NUM_AUTOPLAY_ANIMATIONS)));
	}

	if (Transition::active)
	{
		if(millis() - Transition::start_time > Transition::total_time)
		{
			delete current_animation;

			current_animation = next_animation;

			next_animation = nullptr;

			Transition::active =  false;
		}
		else
		{
			next_animation->run();
		}
	}
	
	current_animation->run();

	show();

	END;
}

void Animation_Controller::start_animation()
{
	START;

	current_animation = Animation::create(_Default);

	END;
}

void Animation_Controller::change_animation(Animation_Name new_animation_name)
{
	START;

	if (Transition::active)
	{
		delete current_animation;

		current_animation = next_animation;

		next_animation = nullptr;
	}

	next_animation = Animation::create(new_animation_name);

	Transition::start();

	END;
}

// Surely there is a better way to do this that doesn't require so many comparisons?
// Make the input classes friend class of the animation class!
//void Animation_Controller::change_animation_variables(Animation_Variables_Old new_vars)
//{
	//current_animation->vars.brightness = (new_vars.brightness == NULL) ? current_animation->vars.brightness : new_vars.brightness;
	//current_animation->vars.brightness_speed = (new_vars.brightness_speed == NULL) ? current_animation->vars.brightness_speed : new_vars.brightness_speed;
	//current_animation->vars.brightness_acceleration = (new_vars.brightness_acceleration == NULL) ? current_animation->vars.brightness_acceleration : new_vars.brightness_acceleration;
	//current_animation->vars.brightness_offset = (new_vars.brightness_offset == NULL) ? current_animation->vars.brightness_offset : new_vars.brightness_offset;

	//current_animation->vars.acceleration = (new_vars.acceleration == NULL) ? current_animation->vars.acceleration : new_vars.acceleration;

	//switch (vars.strip_display_mode)
	//{
	//case Parallel:
	//	for (auto& led_set : leds) {
	//		led_set->fill_rainbow(vars.hue, vars.hue_offset);
	//	}
	//	break;
	//case Sequential:
	//{
	//	int offset = 0;

	//	for (auto& led_set : leds) {
	//		led_set->fill_rainbow(vars.hue + offset, vars.hue_offset);

	//		offset += led_set->size() % (int)vars.hue_offset;
	//	}
	//}

	//break;
	//default:
	//	for (auto& led_set : leds) {
	//		led_set->fill_rainbow(vars.hue, vars.hue_offset);
	//	}
	//}
//}

void Animation_Controller::erase_prev_frame()
{
	START;

	LED_Fixture::black_out();

	END;
}

// Show the current_animation leds based on it's led_arrangements
void Animation_Controller::show()
{
	START;

	if (Transition::active)
	{
		switch (Transition::temp_type)
		{
		case _tt_Fade:
			Transition::fade(current_animation, next_animation);
			break;
		case _tt_Wipe:
			Transition::wipe(current_animation, next_animation);
			break;
		case _tt_Dissolve:
			Transition::dissolve(current_animation, next_animation);
			break;
		default:
			Transition::fade(current_animation, next_animation);
		}
	}
	else
	{
		Transition::none(current_animation);
	}

	END;
}

void Animation_Controller::set_transition(Transition_Type new_transition_type)
{
	Transition::type = new_transition_type;
}
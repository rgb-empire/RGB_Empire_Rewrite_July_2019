#include "Template_Animation.h"

Template_Animation::Template_Animation(LED_Arrangements* new_led_arrangements)
	:Animation(new_led_arrangements)
{
	START;

	// This is where you can combine animations.
	//animations.push_back(Animation::create(_Rainbow_Wave, new_led_arrangements));
	//animations.push_back(Animation::create(_Glitter, new_led_arrangements));

	END;
}

// Use the run function to define what the animation must do every frame.
// This example is the default function in the Animation base class.

//void Template_Animation::run()
//{
//	START;
//
//	erase_previous_frame();
//
//	update_vars();
//
//	calculate_frame();
//
//	for (auto& animation : animations) {
//		THING;
//		animation->run();
//	}
//
//	END;
//}



// Use erase_previous_frame to define how the animation resets itself after each frame.
// This example is the default function in the Animation base class.

//void Template_Animation::erase_previous_frame()
//{
//	START;
//
//	for (auto& pixel : *led_set)
//	{
//		pixel = CRGB::Black;
//	}
//
//	END;
//}



// Update the animation variables to calculate the next frame.
// This example is the (incomplete) default function in the Animation base class.

//void Template_Animation::update_vars()
//{
//	START;
//
//	vars.brightness += vars.brightness_speed;
//	vars.brightness_speed += vars.brightness_acceleration;
//
//	vars.position += vars.speed;
//	vars.speed += vars.acceleration;
//
//	vars.hue += vars.hue_speed;
//	vars.hue_speed += vars.hue_acceleration;
//
//	vars.size += vars.size_speed;
//	vars.size_speed += vars.size_acceleration;
//
//	END;
//}


// Use calculate_frame to assign values the animation's pixel array
// by using the variables in the struct Animation_Variables vars.
// This example is from the Glitter class.

//void Template_Animation::calculate_frame()
//{
//	START;
//
//	for (auto& pixel : *led_set)
//	{
//		if (random(1000) < vars.density)
//		{
//			pixel = CRGB::White;
//		}
//	}
//
//	END;
//}
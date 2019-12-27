// Animation.h

// An Animation is designed to coordinate patterns on multiple strips of LEDs
// meaning it will interact directly with the LED_Fixture class.

// Arrays are used to give animations all the variables they need to operate
// correctly and allow for future extensibility.

// Floats are used to allow super smooth transitions and antialiased output.

// I think this should be an interface class to allow individual animations
// to be seperated out into children classes.

#ifndef _ANIMATION_h
#define _ANIMATION_h

#include "arduino.h"
#include <vector>
#include <typeinfo>

#include <FastLED.h>
#include "Oscillator.h"
#include "My_Enums.h"
#include "LED_Arrangement.h"
#include "LED_Fixture.h"
#include "Animation_Variables.h"
#include "Transition.h"
#include "Bug.h"


// Factory method eliminates this.
//extern std::vector<Animation_Class_And_Name> animation_list;


class Animation
{
protected:
	// Every animation should have a unique name.
	// "Base" is t he name of the interface.
	Animation_Name name;

	// Moved this to the Animation_Controller class.
	// Vector that contains all children of this interface. Push onto this vector in the header of each child.
	//static std::vector<Animation> animation_list;

	// Vector to contain any other animation objects this one creates.
	std::vector<Animation*> animations;

	LED_Arrangement* arrangement;

	LED_Group* group;

	// Each animation object should store its own LED data to be combined by the animation_controller.
	// Maybe store led data like this?
	int num_leds;
	CRGB* leds;
	CRGBSet* led_set;

	friend class Animation_Controller;
	friend class Wifi_Class;
	friend class Transition;

public:
	// A struct that contains all the variables associated with the animation.
	Animation_Variables vars;

	Animation(Animation_Name new_animation_name);
	Animation();
	Animation(LED_Group* new_group);

	static Animation* create(Animation_Name new_animation_name);
	static Animation* create(Animation_Name new_animation_name, LED_Group* new_group);

	void add_aniamtion(Animation_Name new_animation_name, LED_Group* new_group);

	virtual ~Animation();

	// Print out all relevant animation information.
	void print_info();
	void print_arrangement_info();

	virtual void update_vars();

	// Erase the previous frame to allow seemless overlapping of animations.
	// Not sure if this is necessary now that each animation has its own led data.
	virtual void erase_previous_frame();


	// Do whatever is necessary to advance the animation to the next frame.
	virtual void run();

	// Generate the next frame of the animation.
	virtual void calculate_frame();

	CRGB* next_frame();

	void change_var(Variable_Name new_var_name, Animation_Variable_Name new_ani_var_name, float new_value);

	int next(int cur, int dir, bool mask[]);
};

//std::vector<boost::variant<first, second> > vec2;
//std::vector<std::unique_ptr<Animation>> vec3;

#include "All_Animations.h"

#endif


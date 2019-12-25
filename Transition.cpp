#include "Transition.h"

Transition_Type Transition::type = _tt_Random;
Transition_Type Transition::temp_type = _tt_Fade;

bool Transition::active = false;
int Transition::total_time = 5000;
long Transition::start_time = 0;

bool* Transition::mask = nullptr;
fract16 Transition::ratio = 0;
fract16 Transition::eased_ratio = 0;
int Transition::num_transitioned = 0;
int Transition::new_num_transitioned = 0;
int Transition::num_leds = LED_Fixture::fixture_params.total_num_leds;

void Transition::set_ratio()
{
	const int elapsed_time = millis() - start_time;

	num_transitioned = new_num_transitioned;

	if (elapsed_time < total_time) {
		ratio = (total_time - elapsed_time) / total_time;
		eased_ratio = ease16InOutQuad(ratio);

		new_num_transitioned = lerp16by16(0, num_leds, ratio);
	}
	else {
		ratio = UINT16_MAX;
		eased_ratio = UINT16_MAX;

		new_num_transitioned = num_leds;
	}

}

void Transition::start()
{
	active = true;

	switch (type)
	{
	case _tt_Random:
		temp_type = Transition_Type(random(0, _tt_NUM_TRANSITIONS));
		break;
	case _tt_Cycle:
		temp_type = Transition_Type((temp_type + 1) % _tt_NUM_TRANSITIONS);
		break;
	default:
		temp_type = type;
	}

	start_time = millis();

	reset();
}

void Transition::reset()
{
	if (mask != nullptr)
	{
		delete mask;
	}

	num_transitioned = 0;
	new_num_transitioned = 0;

	mask = new bool[num_leds];

	for (int i = 0; i < num_leds; i++)
	{
		mask[i] = false;
	}
}

// Show the current_animation leds based on it's led_arrangements
void Transition::show(Animation* current_animation, Animation* next_animation)
{
	START;

	cur_animation_frame = current_animation->next_frame();
	cur_animation_frame_set = CRGBSet(cur_animation_frame, current_animation->num_leds);

	if (active)
	{
		next_animation_frame = next_animation->next_frame();
		next_animation_frame_set = CRGBSet(next_animation_frame, next_animation->num_leds);

		switch (temp_type)
		{
		case _tt_Fade:
			fade();
			break;
		case _tt_Wipe:
			wipe();
			break;
		case _tt_Dissolve:
			dissolve();
			break;
		default:
			fade();
		}
	}
	else
	{
		none();
	}

	END;
}

void Transition::none()
{
	int cur_led_num = 0;


	for (auto& group : current_animation->arrangement->led_groups)
	{
		for (auto& arr_led_set : group->leds)
		{
			int i = 0;

			for (auto& led : *arr_led_set)
			{
				led = current_animation->leds[cur_led_num + i++];
			}
		}
		cur_led_num += group->size;
	}
}

void Transition::fade(Animation* current_animation, Animation* next_animation)
{
	START;

	//Serial.println("Transitioned: ");
	//Serial.println(new_num_transitioned);
	//Serial.println(num_transitioned);

	int cur_led_num = 0;



	CRGB* next_animation_frame = next_animation->next_frame();
	CRGBSet next_animation_frame_set = CRGBSet(next_animation_frame, next_animation->num_leds);

	set_ratio();

	for (auto& group : current_animation->arrangement->led_groups)
	{

		for (auto& arr_led_set : group->leds)
		{
			int i = 0;

			for (auto& led : *arr_led_set)
			{
				led = next_animation->leds[cur_led_num + i].nscale8_video(255 * (1 - ratio));
				led += current_animation->leds[cur_led_num + i].nscale8_video(255 * ratio);

				i++;
			}
		}
		cur_led_num += group->size;
	}

	END;
}

void Transition::wipe(Animation* current_animation, Animation* next_animation)
{
	//Serial.println("Transitioned: ");
	//Serial.println(new_num_transitioned);
	//Serial.println(num_transitioned);

	int cur_led_num = 0;

	int cur_group_num = 0;

	CRGB* cur_animation_frame = current_animation->next_frame();
	CRGBSet cur_animation_frame_set = CRGBSet(cur_animation_frame, current_animation->num_leds);


	CRGB* next_animation_frame = next_animation->next_frame();
	CRGBSet next_animation_frame_set = CRGBSet(next_animation_frame, next_animation->num_leds);

	set_ratio();

	for (auto& group : current_animation->arrangement->led_groups)
	{
		for (auto& arr_led_set : group->leds)
		{
			int i = 0;

			for (auto& led : *arr_led_set)
			{
				if (i < abs(arr_led_set->len) * (1 - ratio))
				{
					
					led = next_animation->leds[cur_led_num + i];
				}
				else
				{

					led = current_animation->leds[cur_led_num + i];
				}

				i++;
			}
		}
		cur_led_num += group->size;
	}
}

void Transition::dissolve(Animation* current_animation, Animation* next_animation)
{
	START;

	//Serial.println("Transitioned: ");
	//Serial.println(new_num_transitioned);
	//Serial.println(num_transitioned);

	int cur_led_num = 0;

	CRGB* cur_animation_frame = current_animation->next_frame();
	CRGBSet cur_animation_frame_set = CRGBSet(cur_animation_frame, current_animation->num_leds);

	CRGB* next_animation_frame = next_animation->next_frame();
	CRGBSet next_animation_frame_set = CRGBSet(next_animation_frame, next_animation->num_leds);

	set_ratio();

	//Bug::thing_counter(__PRETTY_FUNCTION__);

	while (new_num_transitioned > num_transitioned)
	{
		int index = random(0, num_leds - 1);

		if (mask[index])
		{
			//Serial.println(index);

			if (random(0, 2))
			{

				while (mask[index])
				{
					index++;

					if (index >= num_leds)
					{
						index = 0;
					}
				}
			}
			else
			{

				while (mask[index])
				{
					index--;

					if (index < 0)
					{
						index = num_leds - 1;
					}
				}
			}

		}

		mask[index] = true;

		num_transitioned++;
	}

	//Bug::thing_counter(__PRETTY_FUNCTION__);

	for (auto& group : current_animation->arrangement->led_groups)
	{
		for (auto& arr_led_set : group->leds)
		{
			int i = 0;

			for (auto& led : *arr_led_set)
			{
				if (mask[i])
				{
					led = next_animation->leds[cur_led_num + i];
				}
				else
				{
					led = current_animation->leds[cur_led_num + i];
				}
				i++;
			}
		}
		cur_led_num += group->size;
	}

	//Bug::thing_counter(__PRETTY_FUNCTION__);

	END;
}
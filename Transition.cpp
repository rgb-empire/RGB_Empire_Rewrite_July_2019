#include "Transition.h"

Transition_Type Transition::type = _tt_Random;
Transition_Type Transition::temp_type = _tt_Fade;

bool Transition::active = false;
int Transition::total_time = 5000;
long Transition::start_time = 0;

bool* Transition::mask = nullptr;
float Transition::ratio = 0.0;
int Transition::num_transitioned = 0;
int Transition::new_num_transitioned = 0;
int Transition::num_leds = LED_Fixture::fixture_params.total_num_leds;

void Transition::set_ratio()
{
	ratio = (float)(total_time - (millis() - start_time)) / (float)total_time;

	if (ratio < 0)
	{
		ratio = 0;
	}

	num_transitioned = new_num_transitioned;
	new_num_transitioned = num_leds * (1 - ratio);
}

void Transition::set_eased_ratio()
{
	ratio = (float)((float)ease16InOutQuad(int((float)UINT16_MAX * ((float)(total_time - (millis() - start_time)) / (float)total_time))) / (float)UINT16_MAX);

	if (ratio < 0)
	{
		ratio = 0;
	}

	num_transitioned = new_num_transitioned;
	new_num_transitioned = num_leds * (1 - ratio);
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

	mask = new bool[num_leds];
	num_transitioned = 0;

	for (int i = 0; i < num_leds - 1; i++)
	{
		mask[i] = false;
	}
}

void Transition::none(Animation* current_animation)
{
	int cur_led_num = 0;

	THING;

	CRGB* current_next_frame = current_animation->next_frame();
	CRGBSet current_next_frame_set = CRGBSet(current_next_frame, current_animation->num_leds);

	THING;

	for (auto& group : current_animation->arrangement->led_groups)
	{
		//P(group->group_number);
		//P(group->size);

		for (auto& arr_led_set : group->leds)
		{
			int i = 0;

			//P(cur_led_num);

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

	int cur_led_num = 0;

	CRGB* current_next_frame = current_animation->next_frame();
	CRGBSet current_next_frame_set = CRGBSet(current_next_frame, current_animation->num_leds);

	CRGB* next_next_frame = next_animation->next_frame();
	CRGBSet next_next_frame_set = CRGBSet(next_next_frame, next_animation->num_leds);

	Transition::set_ratio();

	for (auto& group : current_animation->arrangement->led_groups)
	{

		for (auto& arr_led_set : group->leds)
		{
			int i = 0;

			for (auto& led : *arr_led_set)
			{
				led = next_animation->leds[cur_led_num + i].nscale8_video(255 * (1 - Transition::ratio));
				led += current_animation->leds[cur_led_num + i].nscale8_video(255 * Transition::ratio);

				i++;
			}
		}
		cur_led_num += group->size;
	}

	END;
}

void Transition::wipe(Animation* current_animation, Animation* next_animation)
{
	int cur_led_num = 0;

	int cur_group_num = 0;

	CRGB* current_next_frame = current_animation->next_frame();
	CRGBSet current_next_frame_set = CRGBSet(current_next_frame, current_animation->num_leds);


	CRGB* next_next_frame = next_animation->next_frame();
	CRGBSet next_next_frame_set = CRGBSet(next_next_frame, next_animation->num_leds);

	Transition::set_ratio();

	for (auto& group : current_animation->arrangement->led_groups)
	{
		for (auto& arr_led_set : group->leds)
		{
			int i = 0;

			for (auto& led : *arr_led_set)
			{
				if (i < abs(arr_led_set->len) * (1 - Transition::ratio))
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

	int cur_led_num = 0;

	CRGB* current_next_frame = current_animation->next_frame();
	CRGBSet current_next_frame_set = CRGBSet(current_next_frame, current_animation->num_leds);


	CRGB* next_next_frame = next_animation->next_frame();
	CRGBSet next_next_frame_set = CRGBSet(next_next_frame, next_animation->num_leds);

	Transition::set_eased_ratio();

	while (Transition::new_num_transitioned > Transition::num_transitioned)
	{
		int index = random(0, Transition::num_leds);

		//Serial.println(num_tDissolved);

		if (Transition::mask[index])
		{
			//Serial.println(index);

			if (random(0, 2))
			{

				while (Transition::mask[index])
				{
					index++;

					if (index >= Transition::num_leds)
					{
						index = 0;
					}
				}
			}
			else
			{

				while (Transition::mask[index])
				{
					index--;

					if (index < 0)
					{
						index = Transition::num_leds - 1;
					}
				}
			}

		}

		Transition::mask[index] = true;

		Transition::num_transitioned++;
	}

	for (auto& group : current_animation->arrangement->led_groups)
	{
		for (auto& arr_led_set : group->leds)
		{
			int i = 0;

			for (auto& led : *arr_led_set)
			{
				if (Transition::mask[i])
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

	END;
}
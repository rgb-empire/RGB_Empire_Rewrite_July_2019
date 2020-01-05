#include "LED_Arrangement.h"

std::vector<LED_Arrangement*> LED_Arrangement::create_strip_arrangements(CRGBSet* new_leds, Strip_Parameters new_strip_parameters)
{
	START;

	END;


	// TODO: get this second version of a macro to work
	switch (new_strip_parameters.shape)
	{
	case _s_Linear:
		//END(" case _s_Linear");
		return create_linear_arrangements(new_leds, new_strip_parameters);

	case _s_Folded:
		//END(" case _s_Folded");
		return create_folded_arrangements(new_leds, new_strip_parameters);

	case _s_Panel:
		//END(" case _s_Panel");
		return create_panel_arrangements(new_leds, new_strip_parameters);

	case _s_Circle:
		//END(" case _s_Circle");
		return create_circle_arrangements(new_leds, new_strip_parameters);

	case _s_Polygon:
		//END(" case _s_Polygon");
		return create_polygon_arrangements(new_leds, new_strip_parameters);

	case _s_Spiral:
		//END(" case _s_Spiral");
		return create_spiral_arrangements(new_leds, new_strip_parameters);

	case _s_Stalk_Flower:
		//END(" case _s_Stalk_Flower");
		return create_stalk_flower_arrangements(new_leds, new_strip_parameters);

	default:
		//END(" case default");
		return create_linear_arrangements(new_leds, new_strip_parameters);
	}

}

std::vector<LED_Arrangement*> LED_Arrangement::create_linear_arrangements(CRGBSet* new_leds, Strip_Parameters new_strip_parameters)
{
	std::vector<LED_Arrangement*> temp_arrangement_vector;
	//CRGBSet* leds = new_leds;

	// TODO: change this to use an iterator over the Strip_Display_Mode enum
	for (int i = 0; i < 4; i++)
	{
		int cur_group_number = 0;
		LED_Group* temp_group = new LED_Group(cur_group_number);
		LED_Arrangement* temp_arrangement = new LED_Arrangement(Strip_Display_Mode(i));
		
		switch (i)
		{
		case 0:
		case 1:
		case 2:
			temp_group->add_to_group(new_leds);
			temp_arrangement->add(temp_group);
			break;

		case 3:
			temp_group->add_to_group(new CRGBSet(new_leds[0](new_leds->len - 1, new_leds->len / 2)));
			temp_group->add_to_group(new CRGBSet(new_leds[0](0, new_leds->len / 2 - 1)));
			temp_arrangement->add(temp_group);
		}

		temp_arrangement_vector.push_back(temp_arrangement);
	}

	MEM;

	return temp_arrangement_vector;
}

std::vector<LED_Arrangement*> LED_Arrangement::create_folded_arrangements(CRGBSet* new_leds, Strip_Parameters new_strip_parameters)
{
	std::vector<LED_Arrangement*> temp_arrangement_vector;
	//CRGBSet* leds = new_leds;

	// TODO: change this to use an iterator over the Strip_Display_Mode enum
	for (int i = 0; i < 4; i++)
	{
		int cur_group_number = 0;
		LED_Group* temp_group = new LED_Group(cur_group_number);
		LED_Arrangement* temp_arrangement = new LED_Arrangement(Strip_Display_Mode(i));

		switch (i)
		{
		case 0:
		case 1:
			for (int j = 0; j < new_strip_parameters.width_in_leds; j++)
			{
				if (j % 2 == 1)
				{
					temp_group->add_to_group(new CRGBSet(new_leds[0](new_strip_parameters.length_in_leds* (j + 1) - 1, new_strip_parameters.length_in_leds * j)));
				}
				else
				{
					temp_group->add_to_group(new CRGBSet(new_leds[0](new_strip_parameters.length_in_leds * j, new_strip_parameters.length_in_leds * (j + 1) - 1)));
				}
			}
			temp_arrangement->add(temp_group);
			break;
		case 2:
			temp_group->add_to_group(new_leds);
			temp_arrangement->add(temp_group);
			break;

		case 3:
			temp_group->add_to_group(new CRGBSet(new_leds[0](new_strip_parameters.length_in_leds / 2 - 1, 0)));

			temp_group->add_to_group(new CRGBSet(new_leds[0](new_strip_parameters.length_in_leds / 2, new_strip_parameters.length_in_leds - 1)));

			temp_group->add_to_group(new CRGBSet(new_leds[0](new_strip_parameters.length_in_leds * 3 / 2 - 1, new_strip_parameters.length_in_leds)));

			temp_group->add_to_group(new CRGBSet(new_leds[0](new_strip_parameters.length_in_leds * 3 / 2, new_strip_parameters.length_in_leds * 2 - 1)));

			temp_arrangement->add(temp_group);
		}

		temp_arrangement_vector.push_back(temp_arrangement);
	}

	MEM;

	return temp_arrangement_vector;
}

std::vector<LED_Arrangement*> LED_Arrangement::create_panel_arrangements(CRGBSet* new_leds, Strip_Parameters new_strip_parameters)
{
	std::vector<LED_Arrangement*> temp_arrangement_vector;

	return temp_arrangement_vector;
}

std::vector<LED_Arrangement*> LED_Arrangement::create_circle_arrangements(CRGBSet* new_leds, Strip_Parameters new_strip_parameters)
{
	std::vector<LED_Arrangement*> temp_arrangement_vector;

	return temp_arrangement_vector;
}

std::vector<LED_Arrangement*> LED_Arrangement::create_polygon_arrangements(CRGBSet* new_leds, Strip_Parameters new_strip_parameters)
{
	std::vector<LED_Arrangement*> temp_arrangement_vector;

	return temp_arrangement_vector;
}

std::vector<LED_Arrangement*> LED_Arrangement::create_spiral_arrangements(CRGBSet* new_leds, Strip_Parameters new_strip_parameters)
{
	std::vector<LED_Arrangement*> temp_arrangement_vector;

	return temp_arrangement_vector;
}

std::vector<LED_Arrangement*> LED_Arrangement::create_stalk_flower_arrangements(CRGBSet* new_leds, Strip_Parameters new_strip_parameters)
{
	std::vector<LED_Arrangement*> temp_arrangement_vector;
	//CRGBSet* leds = new_leds;

	// TODO: change this to use an iterator over the Strip_Display_Mode enum
	for (int i = 0; i < 4; i++)
	{
		int cur_group_number = 0;
		LED_Group* temp_group = new LED_Group(cur_group_number);
		LED_Arrangement* temp_arrangement = new LED_Arrangement(Strip_Display_Mode(i));

		switch (i)
		{
		case 0:
		case 1:
			for (int j = 0; j < new_strip_parameters.width_in_leds; j++)
			{
				if (j % 2 == 1)
				{
					temp_group->add_to_group(new CRGBSet(new_leds[0](new_strip_parameters.length_in_leds* (j + 1) - 1, new_strip_parameters.length_in_leds* j)));
				}
				else
				{
					temp_group->add_to_group(new CRGBSet(new_leds[0](new_strip_parameters.length_in_leds* j, new_strip_parameters.length_in_leds* (j + 1) - 1)));
				}
			}
			temp_arrangement->add(temp_group);
			break;
		case 2:
			temp_group->add_to_group(new_leds);
			temp_arrangement->add(temp_group);
			break;

		case 3:
			temp_group->add_to_group(new CRGBSet(new_leds[0](new_strip_parameters.length_in_leds / 2 - 1, 0)));

			temp_group->add_to_group(new CRGBSet(new_leds[0](new_strip_parameters.length_in_leds / 2, new_strip_parameters.length_in_leds - 1)));

			temp_group->add_to_group(new CRGBSet(new_leds[0](new_strip_parameters.length_in_leds * 3 / 2 - 1, new_strip_parameters.length_in_leds)));

			temp_group->add_to_group(new CRGBSet(new_leds[0](new_strip_parameters.length_in_leds * 3 / 2, new_strip_parameters.length_in_leds * 2 - 1)));

			temp_arrangement->add(temp_group);
		}

		temp_arrangement_vector.push_back(temp_arrangement);
	}

	MEM;

	return temp_arrangement_vector;
}
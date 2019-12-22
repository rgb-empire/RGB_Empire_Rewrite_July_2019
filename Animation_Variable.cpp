#include "Animation_Variable.h"

Animation_Variable::Animation_Variable(Variable_Name new_name, float new_value, float new_speed, float new_acceleration, float new_offset, float new_min, float new_max, End_Of_Range new_eor)
	:name(new_name),
	eor(new_eor)
{
	//START;

	switch (eor)
	{
	case _eor_Default:
	case _eor_Loop:
		vars[a_value] = Bounded_Variable(new_value, new_min, new_max, _eor_Loop);
		vars[a_speed] = Bounded_Variable(new_speed, -10, 10, _eor_Stop);
		vars[a_acceleration] = Bounded_Variable(new_acceleration, -1, 1, _eor_Stop);
		vars[a_offset] = Bounded_Variable(new_offset, -1000, 1000, _eor_Stop);
		break;
	case _eor_Bounce:
		vars[a_value] = Bounded_Variable(new_value, new_min, new_max, _eor_Bounce);
		vars[a_speed] = Bounded_Variable(new_speed, -10, 10, _eor_Bounce);
		vars[a_acceleration] = Bounded_Variable(new_acceleration, -1, 1, _eor_Bounce);
		vars[a_offset] = Bounded_Variable(new_offset, -1000, 1000, _eor_Bounce);
		break;
	case _eor_Stop:
		vars[a_value] = Bounded_Variable(new_value, new_min, new_max, _eor_Stop);
		vars[a_speed] = Bounded_Variable(new_speed, -10, 10, _eor_Stop);
		vars[a_acceleration] = Bounded_Variable(new_acceleration, -1, 1, _eor_Stop);
		vars[a_offset] = Bounded_Variable(new_offset, -1000, 1000, _eor_Stop);
		break;
	default:
		vars[a_value] = Bounded_Variable(new_value, new_min, new_max, new_eor);
		vars[a_speed] = Bounded_Variable(new_speed, -10, 10, new_eor);
		vars[a_acceleration] = Bounded_Variable(new_acceleration, -1, 1, _eor_Stop);
		vars[a_offset] = Bounded_Variable(new_offset, -1000, 1000, _eor_Stop);
	}

	//END;
}

Bounded_Variable* Animation_Variable::operator()(Animation_Variable_Name new_ani_var_name)
{
	return &vars[new_ani_var_name];
}

void Animation_Variable::update()
{
	//START;

	vars[a_value].value += vars[a_speed].value * speed_scale_factor;
	vars[a_speed].value += vars[a_acceleration].value * speed_scale_factor;

	//if (name == _vPosition && vars[a_value].value > vars[a_value].max)
	//{
	//	P(name);
	//	P(vars[a_value].value);
	//	P(vars[a_speed].value);
	//}

	if (vars[a_value].is_at_eor())
	{
		switch (eor)
		{
		case _eor_Default:	// same as loop
		case _eor_Loop:
			// do nothing
			break;

		case _eor_Bounce:
			if (vars[a_value].value == vars[a_value].min)
			{
				vars[a_speed].make_positive();
				vars[a_acceleration].make_positive();
			}
			else if (vars[a_value].value == vars[a_value].max)
			{

				vars[a_speed].make_negative();
				vars[a_acceleration].make_negative();
			}
			break;

		case _eor_Stop:
			vars[a_speed].value = 0;
			vars[a_acceleration].value = 0;
			break;

		default:	// same as _Loop
			;// do nothing
		}
	}
	if (vars[a_speed].is_at_eor())
	{
		switch (vars[a_speed].eor)
		{
		case _eor_Default:	// same as loop
		case _eor_Loop:
			// do nothing
			break;

		case _eor_Bounce:
			if (vars[a_speed].value == vars[a_speed].min)
			{
				vars[a_acceleration].make_positive();
			}
			else if (vars[a_speed].value == vars[a_speed].max)
			{
				vars[a_acceleration].make_negative();
			}
			break;

		case _eor_Stop:
			vars[a_acceleration].value = 0;
			break;

		default:	// same as _Loop
			;// do nothing
		}
	}

	//END;
}
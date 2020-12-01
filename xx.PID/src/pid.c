t_error_data calculate_error(t_angle_data actual_pos, t_angle_data expected_pos)
{
	t_error_data error_pos;

	error.x = expected_pos.x - actual_pos.x;
	error.y = expected_pos.y - actual_pos.y;
	error.z = expected_pos.z - actual_pos.z;

	return (error_pos);
}

t_adjust_motor proportional(t_error_data error_pos)
{
	t_adjust_motor prop_adjust;


	if (error.x != 0)
	{
		prop_adjust.fl = -error.x;
		prop_adjust.fr = -error.x;
		prop_adjust.bl = error.x;
		prop_adjust.br = error.x;
	}

	if (error.y > 0)
	{
		prop_adjust.fl = -error.y;
		prop_adjust.bl = -error.y;
		prop_adjust.fr = error.y;
		prop_adjust.br = error.y;
	}

	if (error.z > 0)
	{
		prop_adjust.fl = -error.z;
		prop_adjust.br = -error.z;
		prop_adjust.fr = error.z;
		prop_adjust.bl = error.z;
	}
}

t_adjust_motor integral(t_error_data error_pos)
{
	static t_adjust_motor integ_adjust;


	if (error.x != 0)
	{
		integ_adjust.fl = -error.x;
		integ_adjust.fr = -error.x;
		integ_adjust.bl = error.x;
		integ_adjust.br = error.x;
	}

	if (error.y > 0)
	{
		integ_adjust.fl = -error.y;
		integ_adjust.bl = -error.y;
		integ_adjust.fr = error.y;
		integ_adjust.br = error.y;
	}

	if (error.z > 0)
	{
		integ_adjust.fl = -error.z;
		integ_adjust.br = -error.z;
		integ_adjust.fr = error.z;
		integ_adjust.bl = error.z;
	}

	return (integ_adjust);

}

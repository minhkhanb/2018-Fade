#include "pch.h"
#include "../../GameCore/CGame.h"

void Acceleration::Defalt()
{
	state = 0;
	speed = 10.0f;
}

void Acceleration::UpdateAcceleration(float & value_out, float value_end, float percent, bool increase, float pow_max, float pow_min, float speed_min, float speed_dont_pass)
{
	//printf("\nSpeed: %f", speed);
	if (state == 0 || state == 2)
	{
		state = 1;
		speed = speed_min;
	}
	if (state == 1)
	{
		if (!increase)
		{
			if (percent < 0.6f)
			{
				speed *= pow_max;
				value_out -= speed;
			}
			if (percent >= 0.6f)
			{
				speed *= pow_min;
				if (speed <= speed_dont_pass)
				{
					speed = speed_dont_pass;
				}
				value_out -= speed;
			}
		}
		else
		{
			if (percent > 0.4f)
			{
				speed *= pow_max;
				value_out += speed;
			}
			if (percent <= 0.4f)
			{
				speed *= pow_min;
				if (speed <= speed_dont_pass)
				{
					speed = speed_dont_pass;
				}
				value_out += speed;
			}
		}
	}
}

void Acceleration::UpdateAccelerationEnd(float & value_out, float value_end, float percent, bool increase)
{
	if (state == 1)
	{
		if (!increase)
		{
			if (percent >= 1.0f)
			{
				value_out = value_end;
				state = 2;
			}
		}
		else
		{
			//printf("\n percent: %f", percent);
			if (percent <= 0.0f)
			{
				value_out = value_end;
				state = 2;
			}
		}
	}
}

bool Acceleration::isFinish()
{
	if (state == 0 || state == 2)
	{
		return true;
	}
	else
	return false;
}

void Acceleration::PrintfSpeed()
{
	printf("\n_speed: %f", speed);
}

#include "pch.h"
#include "../../../GameCore/CGame.h"

void TransformColor::Init(COLOR one, COLOR two, int num_frame)
{
	_draw_color = one;

	_current_color._a._byte = ((one >> 24) & 0xFF);
	_current_color._r._byte = ((one >> 16) & 0xFF);
	_current_color._g._byte = ((one >> 8) & 0xFF);
	_current_color._b._byte = (one & 0xFF);

	_current_color._a._float = _current_color._a._byte;
	_current_color._r._float = _current_color._r._byte;
	_current_color._g._float = _current_color._g._byte;
	_current_color._b._float = _current_color._b._byte;

	_begin_color = _draw_color;

	_target_color._a._byte = ((two >> 24) & 0xFF);
	_target_color._r._byte = ((two >> 16) & 0xFF);
	_target_color._g._byte = ((two >> 8) & 0xFF);
	_target_color._b._byte = ((two)& 0xFF);

	_target_color._a._float = _target_color._a._byte;
	_target_color._r._float = _target_color._r._byte;
	_target_color._g._float = _target_color._g._byte;
	_target_color._b._float = _target_color._b._byte;

	_delta_color._a._float = 0;
	_delta_color._r._float = (float)(_target_color._r._byte - _current_color._r._byte) / (num_frame*1.0f);
	_delta_color._g._float = (float)(_target_color._g._byte - _current_color._g._byte) / (num_frame*1.0f);
	_delta_color._b._float = (float)(_target_color._b._byte - _current_color._b._byte) / (num_frame*1.0f);

	state = 1;
	//PDEBUG("\n one:0x%6x two:0x%6x", one, two);
}

void TransformColor::UpdateFollowPercent(float percent)
{
	if (state == 0 || state == 2)
	{
		_current_color._r._float = _start_color._r._float + ((float)(_target_color._r._byte - _start_color._r._byte))*percent;
		_current_color._g._float = _start_color._g._float + ((float)(_target_color._g._byte - _start_color._g._byte))*percent;
		_current_color._b._float = _start_color._b._float + ((float)(_target_color._b._byte - _start_color._b._byte))*percent;
	
		float temp = roundf(_current_color._a._float);
		_current_color._a._byte = (int)temp;

		temp = roundf(_current_color._r._float);
		_current_color._r._byte = (int)temp;

		temp = roundf(_current_color._g._float);
		_current_color._g._byte = (int)temp;

		temp = roundf(_current_color._b._float);
		_current_color._b._byte = (int)temp;

		if (percent >= 1.0f)
		{
			_current_color = _target_color;
		}

		int a = (((char)_current_color._a._byte) << 24) & 0xFF000000;
		int r = (((char)_current_color._r._byte) << 16) & 0x00FF0000;
		int g = (((char)_current_color._g._byte) << 8) & 0x0000FF00;
		int b = (((char)_current_color._b._byte)) & 0x000000FF;

		_draw_color = a | r | g | b;
	}
}

void TransformColor::Update()
{
	if (state == 1)
	{
		bool finish_r = false;
		bool finish_g = false;
		bool finish_b = false;

		float old_r = _target_color._r._float - _current_color._r._float;
		_current_color._r._float += _delta_color._r._float;
		finish_r = (old_r == 0) || ((_delta_color._r._float / old_r) >= 1.0f);
		if (finish_r)
		{
			_current_color._r._float = _target_color._r._float;
		}

		float old_g = _target_color._g._float - _current_color._g._float;
		_current_color._g._float += _delta_color._g._float;
		finish_g = (old_g == 0) || ((_delta_color._g._float / old_g) >= 1);
		if (finish_g)
		{
			_current_color._g._float = _target_color._g._float;
		}

		float old_b = _target_color._b._float - _current_color._b._float;
		_current_color._b._float += _delta_color._b._float;
		finish_b = (old_b == 0) || ((_delta_color._b._float / old_b) >= 1);
		if (finish_b)
		{
			_current_color._b._float = _target_color._b._float;
		}

		float temp = roundf(_current_color._a._float);
		_current_color._a._byte = (int)temp;

		temp = roundf(_current_color._r._float);
		_current_color._r._byte = (int)temp;

		temp = roundf(_current_color._g._float);
		_current_color._g._byte = (int)temp;

		temp = roundf(_current_color._b._float);
		_current_color._b._byte = (int)temp;



		if (finish_r && finish_g && finish_b)
		{
			_current_color = _target_color;
			state = 2;
		}
		int a = (((char)_current_color._a._byte) << 24) & 0xFF000000;
		int r = (((char)_current_color._r._byte) << 16) & 0x00FF0000;
		int g = (((char)_current_color._g._byte) << 8) & 0x0000FF00;
		int b = (((char)_current_color._b._byte)) & 0x000000FF;

		//PDEBUG("a:0x%6x r:0x%6x g:0x%6x b:0x%6x\n", a, r, g, b);
		_draw_color = a | r | g | b;

		//_result_color = (int)_current_color._a * 0x1000000 + (int)_current_color._r * 0x10000 + (int)_currentColor._g * 0x100 + (int)_currentColor._b;
	}
}

void TransformColor::Default()
{
	state = 0;

	COLOR one, two;
	one = 0xFFFFFFFF;
	two = 0xFFFFFFFF;

	_draw_color = one;

	_current_color._a._byte = ((one >> 24) & 0xFF);
	_current_color._r._byte = ((one >> 16) & 0xFF);
	_current_color._g._byte = ((one >> 8) & 0xFF);
	_current_color._b._byte = (one & 0xFF);

	_current_color._a._float = _current_color._a._byte;
	_current_color._r._float = _current_color._r._byte;
	_current_color._g._float = _current_color._g._byte;
	_current_color._b._float = _current_color._b._byte;

	_begin_color = _draw_color;

	_target_color._a._byte = ((two >> 24) & 0xFF);
	_target_color._r._byte = ((two >> 16) & 0xFF);
	_target_color._g._byte = ((two >> 8) & 0xFF);
	_target_color._b._byte = ((two)& 0xFF);

	_target_color._a._float = _target_color._a._byte;
	_target_color._r._float = _target_color._r._byte;
	_target_color._g._float = _target_color._g._byte;
	_target_color._b._float = _target_color._b._byte;

	_delta_color._a._float = 0;
	_delta_color._r._float = (float)(_target_color._r._byte - _current_color._r._byte) / 100.0f;
	_delta_color._g._float = (float)(_target_color._g._byte - _current_color._g._byte) / 100.0f;
	_delta_color._b._float = (float)(_target_color._b._byte - _current_color._b._byte) / 100.0f;
}

bool TransformColor::isFinish()
{
	if (state == 2 || state == 0)
	{
		return true;
	}
	else
		return false;
}

void TransformColor::InitColorFollowPercent(COLOR one, COLOR two)
{
	_draw_color = one;
	_begin_color = _draw_color;

	_current_color._a._byte = ((one >> 24) & 0xFF);
	_current_color._r._byte = ((one >> 16) & 0xFF);
	_current_color._g._byte = ((one >> 8) & 0xFF);
	_current_color._b._byte = (one & 0xFF);

	_current_color._a._float = _current_color._a._byte;
	_current_color._r._float = _current_color._r._byte;
	_current_color._g._float = _current_color._g._byte;
	_current_color._b._float = _current_color._b._byte;

	_start_color._a._byte = ((one >> 24) & 0xFF);
	_start_color._r._byte = ((one >> 16) & 0xFF);
	_start_color._g._byte = ((one >> 8) & 0xFF);
	_start_color._b._byte = (one & 0xFF);

	_start_color._a._float = _current_color._a._byte;
	_start_color._r._float = _current_color._r._byte;
	_start_color._g._float = _current_color._g._byte;
	_start_color._b._float = _current_color._b._byte;

	_target_color._a._byte = ((two >> 24) & 0xFF);
	_target_color._r._byte = ((two >> 16) & 0xFF);
	_target_color._g._byte = ((two >> 8) & 0xFF);
	_target_color._b._byte = ((two)& 0xFF);

	_target_color._a._float = _target_color._a._byte;
	_target_color._r._float = _target_color._r._byte;
	_target_color._g._float = _target_color._g._byte;
	_target_color._b._float = _target_color._b._byte;
}

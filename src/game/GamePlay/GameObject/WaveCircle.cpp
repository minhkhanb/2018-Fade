#include "pch.h"
#include "../../GameCore/CGame.h"

#define BOOM_RADIUS			7
#define PERCENT_SCALE_AFTER_BOOM		0.94f

void WaveCircle::Default(int row, int column)
{
	_current_row = row;
	_current_column = column;
	if (_matrix_pos_begin != nullptr)
	{
		SAFE_DEL_ARRAY(_matrix_pos_begin);
	}
	_matrix_pos_begin = new PinePoint*[_current_row];
	for (int i = 0; i < _current_row; i++)
	{
		_matrix_pos_begin[i] = new PinePoint[_current_column];
	}
	if (_matrix_pos_current != nullptr)
	{
		SAFE_DEL_ARRAY(_matrix_pos_current);
	}
	_matrix_pos_current = new PinePoint*[_current_row];
	for (int i = 0; i < _current_row; i++)
	{
		_matrix_pos_current[i] = new PinePoint[_current_column];
	}
	if (_matrix_vector != nullptr)
	{
		SAFE_DEL_ARRAY(_matrix_vector);
	}
	_matrix_vector = new SVector2*[_current_row];
	for (int i = 0; i < _current_row; i++)
	{
		_matrix_vector[i] = new SVector2[_current_column];
	}
#if defined (OPTIMIZE_ANDROID)
	if (_num_vector_push > 0)
	{
		SAFE_DEL_ARRAY(_matrix_vector);
	}

#else
	if (_matrix_vector_push != nullptr)
	{
		SAFE_DEL_ARRAY(_matrix_vector);
	}
#endif
	_num_vector_push = 0;


	for (int i = 0; i < _current_row; i++)
	{
		for (int j = 0; j < _current_column; j++)
		{
			_matrix_pos_begin[i][j].X = 0.0f;
			_matrix_pos_begin[i][j].Y = 0.0;
			_matrix_pos_current[i][j] = _matrix_pos_begin[i][j];
			_matrix_vector[i][j].Init(0.0f, 0.0f);
		}
	}
	
	_speed = 0.01f;

	_time_delay_change = 0;
	_flag_add_vector = false;

	BoomDefault();
}

void WaveCircle::Update()
{
	UpdateBoom();



	if (_flag_add_vector)
	{
		for (int i = 0; i < _current_row; i++)
		{
			for (int j = 0; j < _current_column; j++)
			{
				_matrix_pos_current[i][j].X += _matrix_vector[i][j].X();
				_matrix_pos_current[i][j].Y += _matrix_vector[i][j].Y();
				_matrix_vector[i][j].Init(0.0f, 0.0f);
			}
		}
		_flag_add_vector = false;
		_time_delay_change = 10;
	}
	if (_time_delay_change == 0 && !_flag_add_vector)
	{
		for (int i = 0; i < _current_row; i++)
		{
			for (int j = 0; j < _current_column; j++)
			{
				if (_matrix_pos_current[i][j].X != 0)
				{
					_matrix_pos_current[i][j].X *= PERCENT_SCALE_AFTER_BOOM;
					if (CMath::ABSOLUTE_VALUE(_matrix_pos_current[i][j].X) <= 1.0f)
					{
						_matrix_pos_current[i][j].X = 0.0f;
					}
				}
				if (_matrix_pos_current[i][j].Y != 0)
				{
					_matrix_pos_current[i][j].Y *= PERCENT_SCALE_AFTER_BOOM;
					if (CMath::ABSOLUTE_VALUE(_matrix_pos_current[i][j].Y) <= 1.0f)
					{
						_matrix_pos_current[i][j].Y = 0.0f;
					}
				}
			}
		}
	}
	else if(_time_delay_change != 0 && !_flag_add_vector)
	{
		_time_delay_change--;
		if (_time_delay_change < 0)
		{
			_time_delay_change = 0;
		}
	}
}

void WaveCircle::AddVectorPush(SVector2 v, PointIndex point)
{
#if defined (OPTIMIZE_ANDROID)
	int index = _num_vector_push++;
	_matrix_vector_push[index].vector_push = v;
	_matrix_vector_push[index].point_effect = point;
#else
	//printf("\npoint_effect.row: %d, point_effect.column: %d", point.row, point.column);
	if (_num_vector_push == 0)
	{
		_num_vector_push++;
		if (_matrix_vector_push != nullptr)
		{
			SAFE_DEL_ARRAY(_matrix_vector_push);
		}
		_matrix_vector_push = new VectorPush[_num_vector_push];
		_matrix_vector_push[0].vector_push = v;
		_matrix_vector_push[0].point_effect = point;
	}
	else if (_num_vector_push > 0)
	{
		VectorPush *matrix_back_up;
		int last_num = _num_vector_push;
		matrix_back_up = new VectorPush[last_num];
		for (int i = 0; i < last_num; i++)
		{
			matrix_back_up[i] = _matrix_vector_push[i];
		}
		if (_matrix_vector_push != nullptr)
		{
			SAFE_DEL_ARRAY(_matrix_vector_push);
		}
		_num_vector_push += 1;
		_matrix_vector_push = new VectorPush[_num_vector_push];
		for (int i = 0; i < last_num; i++)
		{
			_matrix_vector_push[i] = matrix_back_up[i];
		}
		_matrix_vector_push[last_num].vector_push = v;
		_matrix_vector_push[last_num].point_effect = point;
		if (matrix_back_up != nullptr)
		{
			SAFE_DEL_ARRAY(matrix_back_up);
		}
	}
#endif
}

void WaveCircle::SubmitVectorPush()
{
	if (_num_vector_push > 0)
	{
		for (int i = 0; i < _num_vector_push; i++)
		{
			_matrix_vector[_matrix_vector_push[i].point_effect.row][_matrix_vector_push[i].point_effect.column] += _matrix_vector_push[i].vector_push;
		}
		_num_vector_push = 0;
#if !defined (OPTIMIZE_ANDROID)
		if (_matrix_vector_push != nullptr)
		{
			SAFE_DEL_ARRAY(_matrix_vector_push);
		}
#endif
		_flag_add_vector = true;
	}
}

void WaveCircle::BoomDefault()
{
#if !defined (OPTIMIZE_ANDROID)
	if (_matrix_boom_current != nullptr)
	{
		SAFE_DEL_ARRAY(_matrix_boom_current);
	}
#endif
	_num_boom_current = 0;
}

void WaveCircle::AddBoom(int touch_r, int touch_c, float pow, float wek)
{
#if defined (OPTIMIZE_ANDROID)
	int index = _num_boom_current++;
	_matrix_boom_current[index].Init(touch_r, touch_c, pow, wek);
#else
	if (_num_boom_current == 0)
	{
		_num_boom_current++;
		if (_matrix_boom_current != nullptr)
		{
			SAFE_DEL_ARRAY(_matrix_boom_current);
		}
		_matrix_boom_current = new BoomInfo[_num_boom_current];
		_matrix_boom_current[0].Init(touch_r, touch_c, pow, wek);
	}
	else if (_num_boom_current > 0)
	{
		BoomInfo *matrix_backup;
		int last_num = _num_boom_current;
		matrix_backup = new BoomInfo[last_num];
		for (int i = 0; i < last_num; i++)
		{
			matrix_backup[i] = _matrix_boom_current[i];
		}
		if (_matrix_boom_current != nullptr)
		{
			SAFE_DEL_ARRAY(_matrix_boom_current);
		}
		_num_boom_current += 1;
		_matrix_boom_current = new BoomInfo[_num_boom_current];
		for (int i = 0; i < last_num; i++)
		{
			_matrix_boom_current[i] = matrix_backup[i];
		}
		_matrix_boom_current[last_num].Init(touch_r, touch_c, pow, wek);
		if (matrix_backup != nullptr)
		{
			SAFE_DEL_ARRAY(matrix_backup);
		}
	}
#endif
}

void WaveCircle::UpdateBoom()
{
	if (_num_boom_current > 0)
	{
		for (int i = 0; i < _num_boom_current; i++)
		{
			/*GetCurrentPowerBoom*/
			UpdateAffectBoomInMatrixVector(i);
			/*End*/



			/*Update Array Boom*/
			_matrix_boom_current[i].Update();
			if (_matrix_boom_current[i].isDie())
			{
				DelBoom(i);
			}
			/*End*/
		}
	}
}

void WaveCircle::UpdateAffectBoomInMatrixVector(int index)
{
	float power_get = _matrix_boom_current[index].getCurrentPower();
	PointIndex point_wave;
	point_wave.row = _matrix_boom_current[index]._point_center_begin_wave.row;
	point_wave.column = _matrix_boom_current[index]._point_center_begin_wave.column;

	for (int k = 1; k <= BOOM_RADIUS; k++)
	{
		SVector2 vector_push;
		PointIndex point_begin_vector;
		int radius = k;

		int index_r_begin = point_wave.row - radius;
		int index_r_end = point_wave.row + radius;
		int index_c_begin = point_wave.column - radius;
		int index_c_end = point_wave.column + radius;
		//top_circle
		if (index_r_begin >= 0 && index_r_begin < _current_row)
		{
			for (int j = index_c_begin; j <= index_c_end; j++)
			{
				if (j < 0 || j >= _current_column)
				{
					continue;
				}
				point_begin_vector.row = index_r_begin;
				point_begin_vector.column = j;
				float decrease = 1.0f;
				/*if (k > 1)
				{
					decrease = 0.1f / (k * 1.0f);
				}*/
				float power_input = power_get * (((k * 1.0f) - (k - 1)) / (k * 1.0f)) * decrease;
				float x = (j - point_wave.column) * power_input;
				float y = (index_r_begin - point_wave.row) * power_input;
				vector_push.Init(x, y);

				AddVectorPush(vector_push, point_begin_vector);
			}
		}
		//printf("\n-------------------------------------------");
		//bot_circle
		if (index_r_end >= 0 && index_r_end < _current_row)
		{
			for (int j = index_c_begin; j <= index_c_end; j++)
			{
				if (j < 0 || j >= _current_column)
				{
					continue;
				}
				point_begin_vector.row = index_r_end;
				point_begin_vector.column = j;
				float power_input = power_get * (((k * 1.0f) - (k - 1)) / (k * 1.0f));
				float x = (j - point_wave.column) * power_input;
				float y = (index_r_end - point_wave.row) * power_input;
				vector_push.Init(x, y);

				AddVectorPush(vector_push, point_begin_vector);
			}
		}
		//printf("\n-------------------------------------------");
		//left_circle
		if (index_c_begin >= 0 && index_c_begin < _current_column)
		{
			for (int i = index_r_begin + 1; i < index_r_end; i++)
			{
				if (i < 0 || i >= _current_row)
				{
					continue;
				}
				point_begin_vector.row = i;
				point_begin_vector.column = index_c_begin;
				float power_input = power_get * (((k * 1.0f) - (k - 1)) / (k * 1.0f));
				float x = (index_c_begin - point_wave.column) * power_input;
				float y = (i - point_wave.row) * power_input;
				vector_push.Init(x, y);

				AddVectorPush(vector_push, point_begin_vector);
			}
		}
		//printf("\n-------------------------------------------");
		//right_circle
		if (index_c_end >= 0 && index_c_end < _current_column)
		{
			for (int i = index_r_begin + 1; i < index_r_end; i++)
			{
				if (i < 0 || i >= _current_row)
				{
					continue;
				}
				point_begin_vector.row = i;
				point_begin_vector.column = index_c_end;
				float power_input = power_get * (((k * 1.0f) - (k - 1)) / (k * 1.0f));
				float x = (index_c_end - point_wave.column) * power_input;
				float y = (i - point_wave.row) * power_input;
				vector_push.Init(x, y);

				AddVectorPush(vector_push, point_begin_vector);
			}
		}
		//printf("\n-------------------------------------------");
	}

	SubmitVectorPush();
}

void WaveCircle::DelBoom(int index)
{
#if defined (OPTIMIZE_ANDROID)
	if (_num_boom_current > 0)
	{
		_num_boom_current--;
		for (int i = index; i < _num_boom_current; i++)
		{
			_matrix_boom_current[i] = _matrix_boom_current[i + 1];
		}
	}
#else
	if (_num_boom_current == 1)
	{
		_num_boom_current = 0;
		if (_matrix_boom_current != nullptr)
		{
			SAFE_DEL_ARRAY(_matrix_boom_current);
		}
	}
	else if (_num_boom_current > 1)
	{
		int new_num_arr = _num_boom_current - 1;
		BoomInfo *matrix_new;
		matrix_new = new BoomInfo[new_num_arr];
		int counter = 0;
		for (int i = 0; i < _num_boom_current; i++)
		{
			if (i == index)
			{

			}
			else
			{
				matrix_new[counter] = _matrix_boom_current[i];
				counter++;
			}
		}
		if (_matrix_vector_push != nullptr)
		{
			SAFE_DEL_ARRAY(_matrix_vector_push);
		}
		_num_boom_current = new_num_arr;
		_matrix_boom_current = new BoomInfo[_num_boom_current];
		for (int i = 0; i < new_num_arr; i++)
		{
			_matrix_boom_current[i] = matrix_new[i];
		}

		if (matrix_new != nullptr)
		{
			SAFE_DEL_ARRAY(matrix_new);
		}
	}
#endif
}

void BoomInfo::Update()
{
	_power *= _weak_percent;
}

float BoomInfo::getCurrentPower()
{
	return _power;
}

bool BoomInfo::isDie()
{
	if (_power < 0.025f)
	{
		return true;
	}
	else return false;
}

void BoomInfo::Init(int touch_r, int touch_c, float pow, float wek)
{
	_point_center_begin_wave.row = touch_r;
	_point_center_begin_wave.column = touch_c;

	_power = pow;
	_weak_percent = wek;
}

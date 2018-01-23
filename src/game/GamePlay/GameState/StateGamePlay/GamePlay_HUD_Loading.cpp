#include "pch.h"
#include "../../../GameCore/CGame.h"

void GPHudLoading::Init(bool auto_off)
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	_state = 1;
	_point_begin.X = game->_point_o.X;
	_point_begin.Y = game->_point_o.Y;
	_point_draw = _point_begin;
	_percent = 0.0f;
	_speed = 0.05f;
	_time_counter = 30;
	_rotate_circle = 0.0f;
	_speed_rotate = 1.0f;
	LoadingCircleDefault();
	if (game->_current_state == k_GS_PLAYGAME)
	{
		_last_state_backup = game->_state_gameplay._gameplay_state;
		game->_state_gameplay._gameplay_state = -20;
	}
	if (game->_current_state == k_GS_SETTING)
	{
		_last_state_backup = game->_state_setting_credit._state;
		game->_state_setting_credit._state = -20;
	}

	flag_auto = auto_off;
	if (flag_auto)
	{
		_time_turn_off = 240;
	}
	else
	{
		_time_turn_off = 0;
	}
}

void GPHudLoading::Update()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	if (_state == 1)
	{
		LoadingCircleUpdate();
		_percent += _speed;
		if (_percent > 1.0f)
		{
			_percent = 1.0f;
		}
		if (_percent >= 1.0f)
		{
			_rotate_circle += _speed_rotate;
			if (_rotate_circle > 360.0f)
			{
				_rotate_circle -= 360.0f;
			}
			_speed_rotate *= 1.03f;
			if (_speed_rotate >= 7.0f)
			{
				_speed_rotate = 7.0f;
				_time_counter++;
				if (_time_counter > 45)
				{
					_time_counter = 0;
					PinePoint draw;
					draw.X = game->_point_o.X + game->_screen_width / 2;
					draw.Y = game->_point_o.Y + game->_screen_height / 2;
					LoadingCircleAdd(draw);
				}
				if (flag_auto)
				{
					_time_turn_off--;
					if (_time_turn_off < 0)
					{
						_time_turn_off = 0;
						_state = 2;
					}
				}
			}
		}
	}
	if (_state == 2)
	{
		_percent -= _speed;
		if (_percent < 0.0f)
		{
			_state = 3;
			_percent = 0.0f;
			_num_circle = 0;
			if (_loading_arr_circle != nullptr)
			{
				SAFE_DEL_ARRAY(_loading_arr_circle);
			}
			if (game->_current_state == k_GS_PLAYGAME)
			{
				game->_state_gameplay._gameplay_state = _last_state_backup;
			}
			if (game->_current_state == k_GS_SETTING)
			{
				game->_state_setting_credit._state = _last_state_backup;
			}
		}
	}
}

void GPHudLoading::Render()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	if (_state == 1 || _state == 2)
	{
		float opacity = _percent * 80.0f;
		G()->SetOpacity((int)opacity);
		G()->SetColor(0xFF000000);
		G()->FillFullScreen(true);
		G()->SetOpacity(100);

		LoadingCircleRender();


		float draw_x = game->_point_o.X + game->_screen_width / 2;
		float draw_y = game->_point_o.Y + game->_screen_height / 2;

		float scale_block = (game->_state_gameplay._master_game._matrix_block_width + game->_state_gameplay._master_game._effect_idle_zoom.value_current * 2) / (GET_SPRITE(SPRITEID_OBJECT_01_N_COLOR)->GetFrameWidth(0) *1.0f);
		scale_block *= 1.3f;
		opacity = _percent * 100.0f;
		G()->SetOpacity(opacity);
		CMatrix4x4Util matrix_normal;
		matrix_normal.reNew();
		matrix_normal.DoScale(scale_block, scale_block, draw_x, draw_y);
		matrix_normal.DoRotate(_rotate_circle, draw_x, draw_y);
		G()->SetTransform(matrix_normal.toPineTranform());
		GET_SPRITE(SPRITEID_OBJECT_01)->DrawFrame(G(), 0, draw_x, draw_y);
		G()->ClearTransform();
		G()->SetOpacity(100);
	}
}

void GPHudLoading::LoadingCircleDefault()
{
	_num_circle = 0;
}

void GPHudLoading::LoadingCircleAdd(PinePoint index)
{
	if (_num_circle == 0)
	{
		_num_circle = 1;
		if (_loading_arr_circle != nullptr)
		{
			SAFE_DEL_ARRAY(_loading_arr_circle);
		}
		_loading_arr_circle = new LoadingCircle[_num_circle];
		_loading_arr_circle[0].Init(index);
	}
	else if (_num_circle > 0)
	{
		int last_num = _num_circle;
		LoadingCircle *arr_backup;
		arr_backup = new LoadingCircle[last_num];
		for (int i = 0; i < last_num; i++)
		{
			arr_backup[i] = _loading_arr_circle[i];
		}
		_num_circle++;
		if (_loading_arr_circle != nullptr)
		{
			SAFE_DEL_ARRAY(_loading_arr_circle);
		}
		_loading_arr_circle = new LoadingCircle[_num_circle];
		for (int i = 0; i < last_num; i++)
		{
			_loading_arr_circle[i] = arr_backup[i];
		}
		_loading_arr_circle[last_num].Init(index);
		if (arr_backup != nullptr)
		{
			SAFE_DEL_ARRAY(arr_backup);
		}
	}
}

void GPHudLoading::LoadingCircleDelete(int index)
{
	if (_num_circle == 1)
	{
		_num_circle = 0;
		if (_loading_arr_circle != nullptr)
		{
			SAFE_DEL_ARRAY(_loading_arr_circle);
		}
	}
	else if (_num_circle > 1)
	{
		LoadingCircle *new_arr;
		int new_num = _num_circle - 1;
		new_arr = new LoadingCircle[new_num];
		int counter = 0;
		for (int i = 0; i < _num_circle; i++)
		{
			if (i == index)
			{

			}
			else
			{
				new_arr[counter] = _loading_arr_circle[i];
				counter++;
			}
		}
		if (_loading_arr_circle != nullptr)
		{
			SAFE_DEL_ARRAY(_loading_arr_circle);
		}
		_loading_arr_circle = new LoadingCircle[new_num];
		for (int i = 0; i < new_num; i++)
		{
			_loading_arr_circle[i] = new_arr[i];
		}
		_num_circle = new_num;
		if (new_arr != nullptr)
		{
			SAFE_DEL_ARRAY(new_arr);
		}
	}
}

void GPHudLoading::LoadingCircleUpdate()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	if (_num_circle > 0)
	{
		for (int i = 0; i < _num_circle; i++)
		{
			_loading_arr_circle[i].Update();
			if (_loading_arr_circle[i].isFinish())
			{
				LoadingCircleDelete(i);
			}
		}
	}
}

void GPHudLoading::LoadingCircleRender()
{
	if (_num_circle > 0)
	{
		for (int i = 0; i < _num_circle; i++)
		{
			_loading_arr_circle[i].Render();
		}
	}
}

void GPHudLoading::LoadingCircle::Init(PinePoint index)
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	_state = 1;
	_percent = 0.0f;
	_speed = 0.007f;
	_pos_draw = index;
}

void GPHudLoading::LoadingCircle::Update()
{
	if (_state == 1)
	{
		_percent += _speed;
		if (_percent > 1.0f)
		{
			_percent = 1.0f;
			_state = 2;
		}
	}
}

void GPHudLoading::LoadingCircle::Render()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	int draw_x = _pos_draw.X;
	int draw_y = _pos_draw.Y;

	float frame_width = game->_state_gameplay._master_game._matrix_block_width * (1.3f);
	float frame_height = game->_state_gameplay._master_game._matrix_block_height * (1.3f);
	float radius = ((game->_state_gameplay._master_game._matrix_block_width * (1.3f)) / 2) + game->_state_gameplay._master_game._effect_idle_zoom.value_current;
	radius += _percent * (frame_width / 2.0f) + 3.0f;
	int opacity = 40.0f * (1.0f - _percent);//100.0f * (1.0f - _percent) / 0.8f;
	opacity = (opacity / 40.0f)* (game->_state_gameplay._hud_loading._percent * 20.0f);
	if (_state == 1)
	{
		G()->SetColor(0xFFDDDDDD);
		G()->SetOpacity(opacity);
		for (float i = radius - 3.0f; i <= radius; i += 0.5f)
		{
			G()->DrawCircle(draw_x, draw_y, i, 10, true);
		}
		G()->SetOpacity(100);
	}
}

bool GPHudLoading::LoadingCircle::isFinish()
{
	if (_state == 2)
	{
		return true;
	}
	else
		return false;
}

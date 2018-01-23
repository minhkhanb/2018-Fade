#include "pch.h"
#include "../../../GameCore/CGame.h"

void EffectTypeClearIdle::TypeClearGlow::Init(PointIndex index)
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	_state = 1;
	_percent = 0.0f;
	_speed = 0.01f;
	_point_index = index;
}

void EffectTypeClearIdle::TypeClearGlow::Update()
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

void EffectTypeClearIdle::TypeClearGlow::Render()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	float grid_w = game->_state_gameplay._master_game._matrix_max_column_current * game->_state_gameplay._master_game._matrix_block_width + game->_state_gameplay._master_game._grap.width * (game->_state_gameplay._master_game._matrix_max_column_current - 1);
	float grid_h = game->_state_gameplay._master_game._matrix_max_row_current * game->_state_gameplay._master_game._matrix_block_height + game->_state_gameplay._master_game._grap.height * (game->_state_gameplay._master_game._matrix_max_row_current - 1);

	float new_x = game->_point_o.X + game->_screen_width / 2 - grid_w / 2;
	float new_y = game->_point_o.Y + game->_screen_height / 2 - grid_h / 2 + SCROLL_DOWN_GRID_FAKE;
	int draw_x = new_x + 0.0f;
	int draw_y = new_y + 0.0f;

	draw_x = _point_index.column * (game->_state_gameplay._master_game._matrix_block_width + (game->_state_gameplay._master_game._grap.width)) + new_x;
	draw_y = _point_index.row * (game->_state_gameplay._master_game._matrix_block_height + (game->_state_gameplay._master_game._grap.height)) + new_y;

	draw_x += game->_state_gameplay._master_game._effect_wave_circle._matrix_pos_current[_point_index.row][_point_index.column].X;
	draw_y += game->_state_gameplay._master_game._effect_wave_circle._matrix_pos_current[_point_index.row][_point_index.column].Y;

	draw_x += game->_state_gameplay._scroll_page_x;
	draw_y += game->_state_gameplay._scroll_page_y;


	float frame_width = game->_state_gameplay._master_game._matrix_block_width;
	float frame_height = game->_state_gameplay._master_game._matrix_block_height;
	float radius = (game->_state_gameplay._master_game._matrix_block_width / 2) + game->_state_gameplay._master_game._effect_idle_zoom.value_current;
	radius += _percent * (frame_width / 4.0f) + 3.0f;
	int opacity = 40.0f * (1.0f - _percent);//100.0f * (1.0f - _percent) / 0.8f;
	opacity = (opacity / 40.0f)* game->_state_gameplay._master_game._opacity_grid;
	if (_state == 1)
	{
		draw_x += frame_width / 2;
		draw_y += frame_width / 2;

		G()->SetColor(0xFFDDDDDD);
		G()->SetOpacity(opacity);
		for (float i = radius - 3.0f; i <= radius; i += 0.5f)
		{
			G()->DrawCircle(draw_x, draw_y, i, 10, true);
		}
		G()->SetOpacity(100);
	}
}

bool EffectTypeClearIdle::TypeClearGlow::isFinish()
{
	if (_state == 2)
	{
		return true;
	}
	else
		return false;
}

void EffectTypeClearIdle::Default()
{
	_num_effect_current = 0;
	_time_counter = 30;
}

void EffectTypeClearIdle::Add(PointIndex index)
{
	if (_num_effect_current == 0)
	{
		_num_effect_current = 1;
		if (_wave_arr != nullptr)
		{
			SAFE_DEL_ARRAY(_wave_arr);
		}
		_wave_arr = new TypeClearGlow[_num_effect_current];
		_wave_arr[0].Init(index);
	}
	else if (_num_effect_current > 0)
	{
		int last_num = _num_effect_current;
		TypeClearGlow *arr_backup;
		arr_backup = new TypeClearGlow[last_num];
		for (int i = 0; i < last_num; i++)
		{
			arr_backup[i] = _wave_arr[i];
		}
		_num_effect_current++;
		if (_wave_arr != nullptr)
		{
			SAFE_DEL_ARRAY(_wave_arr);
		}
		_wave_arr = new TypeClearGlow[_num_effect_current];
		for (int i = 0; i < last_num; i++)
		{
			_wave_arr[i] = arr_backup[i];
		}
		_wave_arr[last_num].Init(index);
		if (arr_backup != nullptr)
		{
			SAFE_DEL_ARRAY(arr_backup);
		}
	}
}

void EffectTypeClearIdle::Delete(int index)
{
	if (_num_effect_current == 1)
	{
		_num_effect_current = 0;
		if (_wave_arr != nullptr)
		{
			SAFE_DEL_ARRAY(_wave_arr);
		}
	}
	else if (_num_effect_current > 1)
	{
		TypeClearGlow *new_arr;
		int new_num = _num_effect_current - 1;
		new_arr = new TypeClearGlow[new_num];
		int counter = 0;
		for (int i = 0; i < _num_effect_current; i++)
		{
			if (i == index)
			{

			}
			else
			{
				new_arr[counter] = _wave_arr[i];
				counter++;
			}
		}
		if (_wave_arr != nullptr)
		{
			SAFE_DEL_ARRAY(_wave_arr);
		}
		_wave_arr = new TypeClearGlow[new_num];
		for (int i = 0; i < new_num; i++)
		{
			_wave_arr[i] = new_arr[i];
		}
		_num_effect_current = new_num;
		if (new_arr != nullptr)
		{
			SAFE_DEL_ARRAY(new_arr);
		}
	}
}

void EffectTypeClearIdle::Update()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	if (_num_effect_current > 0)
	{
		for (int i = 0; i < _num_effect_current; i++)
		{
			_wave_arr[i].Update();
			if (_wave_arr[i].isFinish())
			{
				Delete(i);
				_time_counter = 30;
			}
		}
	}
	else if (_num_effect_current == 0)
	{
		_time_counter--;
		if (_time_counter <= 0)
		{
			//if (game->_state_gameplay._master_game._state_matrix == MATRIX_CAN_TOUCH)
			{
				int total_type_clear = game->_state_gameplay._master_game.GetTotalBlockLikeTypeAndState(BLOCK_NORMAL, TYPE_CLEAR);
				if (total_type_clear >= 1)
				{
					int random = CMath::RANDOM(1, total_type_clear);
					int counter = 1;
					bool out_loop = false;
					for (int i = 0; i < game->_state_gameplay._master_game._matrix_max_row_current; i++)
					{
						for (int j = 0; j < game->_state_gameplay._master_game._matrix_max_column_current; j++)
						{
							if (game->_state_gameplay._master_game._arr_block[i][j]._state == BLOCK_NORMAL)
							{
								if (game->_state_gameplay._master_game._arr_block[i][j]._type == TYPE_CLEAR)
								{
									/*if (counter == random)
									{
										out_loop = true;
										Add(game->_state_gameplay._master_game._arr_block[i][j]._point_begin);
										break;
									}*/
									Add(game->_state_gameplay._master_game._arr_block[i][j]._point_begin);
									counter++;
								}
							}
						}
						if (out_loop)
						{
							break;
						}
					}
				}
			}
		}
	}
}

void EffectTypeClearIdle::Render()
{
	if (_num_effect_current > 0)
	{
		for (int i = 0; i < _num_effect_current; i++)
		{
			_wave_arr[i].Render();
		}
	}
}

void EffectTypeClearIdle::FreeMemory()
{
	if (_num_effect_current > 0)
	{
		_num_effect_current = 0;
	}
	if (_wave_arr != nullptr)
	{
		SAFE_DEL_ARRAY(_wave_arr);
	}
}

#include "pch.h"
#include "../../../GameCore/CGame.h"

#define FRAME_RATE_SPEED_MAX		43
#define FRAME_RATE_SPEED_IN			60
#define FRAME_RATE_SPEED_RETURN		15


void BlockGrid::Init(int index_c, int index_r, int type_block)
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	_state = BLOCK_NORMAL;
	_type = type_block;
	_point_begin.column = index_c;
	_point_begin.row = index_r;

	int grid_w = game->_state_gameplay._master_game._matrix_max_column_current * game->_state_gameplay._master_game._matrix_block_width + game->_state_gameplay._master_game._grap.width * (game->_state_gameplay._master_game._matrix_max_column_current - 1);
	int grid_h = game->_state_gameplay._master_game._matrix_max_row_current * game->_state_gameplay._master_game._matrix_block_height + game->_state_gameplay._master_game._grap.height * (game->_state_gameplay._master_game._matrix_max_row_current - 1);

	int new_x = game->_point_o.X + game->_screen_width / 2 - grid_w / 2;
	int new_y = game->_point_o.Y + game->_screen_height / 2 - grid_h / 2 + SCROLL_DOWN_GRID_FAKE;
	_point_begin_pixel.X = _point_begin.column * (game->_state_gameplay._master_game._matrix_block_width + game->_state_gameplay._master_game._grap.width) + new_x;
	_point_begin_pixel.Y = _point_begin.row * (game->_state_gameplay._master_game._matrix_block_height + game->_state_gameplay._master_game._grap.height) + new_y;

	_color = game->_state_gameplay._master_game.GetCurrentColor(type_block);
	_transform_color.Default();
	_is_touch_state = 0;
	_effect_zoom_object_max.Default();
	_effect_zoom_object_scale_in.Default();
	_effect_zoom_object_reborn.Default();
}

void BlockGrid::RenderBlockNormal(float pos_x, float pos_y)
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	float grid_w = game->_state_gameplay._master_game._matrix_max_column_current * game->_state_gameplay._master_game._matrix_block_width + game->_state_gameplay._master_game._grap.width * (game->_state_gameplay._master_game._matrix_max_column_current - 1);
	float grid_h = game->_state_gameplay._master_game._matrix_max_row_current * game->_state_gameplay._master_game._matrix_block_height + game->_state_gameplay._master_game._grap.height * (game->_state_gameplay._master_game._matrix_max_row_current - 1);

	float new_x = game->_point_o.X + game->_screen_width / 2 - grid_w / 2 + pos_x;
	float new_y = game->_point_o.Y + game->_screen_height / 2 - grid_h / 2 + SCROLL_DOWN_GRID_FAKE + pos_y;
	int draw_x = new_x + 0.0f;
	int draw_y = new_y + 0.0f;

	//printf("\nscale_block: %.1f, width: %.1f, height: %.1f, (%d, %d)", scale_block, (scale_block * BLOCK_FRAME_WIDTH), (scale_block * BLOCK_FRAME_HEIGHT),
	//game->_state_gameplay_dlc_one._master_game._matrix_block_width, game->_state_gameplay_dlc_one._master_game._matrix_block_height);
	draw_x = _point_begin.column * (game->_state_gameplay._master_game._matrix_block_width + (game->_state_gameplay._master_game._grap.width)) + new_x;
	draw_y = _point_begin.row * (game->_state_gameplay._master_game._matrix_block_height + (game->_state_gameplay._master_game._grap.height)) + new_y;

	draw_x += game->_state_gameplay._master_game._effect_wave_circle._matrix_pos_current[_point_begin.row][_point_begin.column].X;
	draw_y += game->_state_gameplay._master_game._effect_wave_circle._matrix_pos_current[_point_begin.row][_point_begin.column].Y;

	draw_x += game->_state_gameplay._scroll_page_x;
	draw_y += game->_state_gameplay._scroll_page_y;

	//G()->SetColor(0xFFFFFFFF);
	//G()->FillRect(draw_x, draw_y, game->_state_gameplay._master_game._matrix_block_width, game->_state_gameplay._master_game._matrix_block_height);

	int opacity = (int)game->_state_gameplay._master_game._opacity_grid;
	float radius = (game->_state_gameplay._master_game._matrix_block_width / 2) + game->_state_gameplay._master_game._effect_idle_zoom.value_current;
	float scale_block = (game->_state_gameplay._master_game._matrix_block_width + game->_state_gameplay._master_game._effect_idle_zoom.value_current * 2) / (GET_SPRITE(SPRITEID_OBJECT_01_N_COLOR)->GetFrameWidth(0) *1.0f);
	if (_type != TYPE_EMPTY)
	{
		G()->SetOpacity(opacity);
		if (_type == TYPE_CLEAR)
		{
			if (_state == BLOCK_NORMAL || _state == BLOCK_WILL_SELECT || _state == BLOCK_WILL_INVI || _state == BLOCK_TOUCH_DOWN)
			{
				CMatrix4x4Util matrix_normal;
				matrix_normal.reNew();
				matrix_normal.DoScale(scale_block, scale_block, draw_x + game->_state_gameplay._master_game._matrix_block_width / 2, draw_y + game->_state_gameplay._master_game._matrix_block_width / 2);
				G()->SetTransform(matrix_normal.toPineTranform());
				GET_SPRITE(SPRITEID_OBJECT_01)->DrawFrame(G(), 0, draw_x + game->_state_gameplay._master_game._matrix_block_width / 2, draw_y + game->_state_gameplay._master_game._matrix_block_width / 2);
				G()->ClearTransform();
			}
		}
		else
		{
			if (_state == BLOCK_NORMAL || _state == BLOCK_WILL_SELECT || _state == BLOCK_WILL_INVI || _state == BLOCK_TOUCH_DOWN)
			{
				/*G()->SetColor(_color);
				for (float i = radius - 3.0f; i <= radius; i+=0.5f)
				{
				G()->DrawCircle(draw_x + game->_state_gameplay._master_game._matrix_block_width / 2, draw_y + game->_state_gameplay._master_game._matrix_block_width / 2, i, 5);
				}*/
				G()->SetColorMask(_color);
				CMatrix4x4Util matrix_normal;
				matrix_normal.reNew();
				matrix_normal.DoScale(scale_block, scale_block, draw_x + game->_state_gameplay._master_game._matrix_block_width / 2, draw_y + game->_state_gameplay._master_game._matrix_block_width / 2);
				G()->SetTransform(matrix_normal.toPineTranform());
				GET_SPRITE(SPRITEID_OBJECT_01_N_COLOR)->DrawFrame(G(), 0, draw_x + game->_state_gameplay._master_game._matrix_block_width / 2, draw_y + game->_state_gameplay._master_game._matrix_block_width / 2);
				G()->ClearTransform();
				G()->ClearColorMask();

				//G()->FillCircle(draw_x + game->_state_gameplay._master_game._matrix_block_width / 2, draw_y + game->_state_gameplay._master_game._matrix_block_width / 2, radius / 3, 5);

				//G()->SetColorMask(0xFFFFFFFF);
				//GET_SPRITE(SPRITEID_FONT_LOGO)->DrawAnsiTextFormat(G(), draw_x + game->_state_gameplay._master_game._matrix_block_width / 2, draw_y + game->_state_gameplay._master_game._matrix_block_width / 2, _HCENTER, "%d", _type);
				//G()->ClearColorMask();
			}
		}
		G()->SetOpacity(100);
	}
}

void BlockGrid::RenderBlockScaleIn(float pos_x, float pos_y)
{
	if (_type != TYPE_EMPTY)
	{
		if (_state == BLOCK_INVI)
		{
			_effect_zoom_object_scale_in.Render(pos_x, pos_y);
		}
	}
}

void BlockGrid::RenderBlockScaleOut(float pos_x, float pos_y)
{
	if (_type != TYPE_EMPTY)
	{
		if (_state == BLOCK_SELECT || _state == BLOCK_TARGET_JOIN)
		{
			_effect_zoom_object_max.Render(pos_x, pos_y);
		}
	}
}

void BlockGrid::RenderBlockReborn(float pos_x, float pos_y)
{
	if (_state == BLOCK_REBORN)
	{
		_effect_zoom_object_reborn.Render(pos_x, pos_y);
	}
}

void BlockGrid::UpdateStateSelect()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	if (_state == BLOCK_TOUCH_DOWN)
	{
		CheckCanJoin();
	}
	if (_state == BLOCK_SELECT)
	{
		_effect_zoom_object_max.Update();
		if (_effect_zoom_object_max.isFinish())
		{
			_effect_zoom_object_max.Default();
			_state = BLOCK_TARGET_JOIN;
		}
	}
}

void BlockGrid::UpdateStateTargetJoin()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	if (_state == BLOCK_TARGET_JOIN)
	{
		bool no_update = false;
		for (int i = 0; i < game->_state_gameplay._master_game._matrix_max_row_current; i++)
		{
			for (int j = 0; j < game->_state_gameplay._master_game._matrix_max_column_current; j++)
			{
				if (game->_state_gameplay._master_game._arr_block[i][j]._state == BLOCK_WILL_INVI ||
					game->_state_gameplay._master_game._arr_block[i][j]._state == BLOCK_INVI)
				{
					no_update = true;
					break;
				}
			}
			if (no_update)
			{
				break;
			}
		}
		if (!no_update)
		{
			_state = BLOCK_NORMAL;
			_type = TYPE_EMPTY;
			_effect_zoom_object_max.Default();

			game->_state_gameplay._master_game._state_matrix = MATRIX_LOOP_CHECK_FILL;
		}
	}
}

void BlockGrid::UpdateStateScaleOut()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	if (_state == BLOCK_INVI)
	{
		_effect_zoom_object_scale_in.Update();
		if (_effect_zoom_object_scale_in.isFinish())
		{
			_state = BLOCK_NORMAL;
			_type = TYPE_EMPTY;
			_effect_zoom_object_scale_in.Default();
		}
	}
}

void BlockGrid::UpdateReborn()
{
	ColorBorn *game = (ColorBorn*)GAME()->_current_game;
	if (_state == BLOCK_REBORN)
	{
		_effect_zoom_object_reborn.Update();
		if (_effect_zoom_object_reborn.isFinish())
		{
			_state = BLOCK_NORMAL;
			_type = _effect_zoom_object_reborn.effect_type;
			_color = _effect_zoom_object_reborn.effect_color;
			_effect_zoom_object_reborn.Default();
		}
	}
}

void BlockGrid::CheckCanJoin()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	int score_count = 0;
	int count = 0;
	bool one = false;
	bool two = false;
	bool three = false;
	bool four = false;
	bool five = false;
	bool six = false;
	bool seven = false;
	bool eight = false;
	int index_row_check = _point_begin.row;
	int index_column_check = _point_begin.column;

	//Top
	int index_one_r = _point_begin.row - 1;
	int index_one_c = _point_begin.column;
	if (index_one_r >= 0)
	{
		if (game->_state_gameplay._master_game._arr_block[index_one_r][index_one_c]._type != TYPE_EMPTY && game->_state_gameplay._master_game._arr_block[index_one_r][index_one_c]._state == BLOCK_NORMAL)
		{
			one = true;
			count++;
		}
	}

	//TR
	int index_two_r = _point_begin.row - 1;
	int index_two_c = _point_begin.column + 1;
	if (index_two_r >= 0 && index_two_c < game->_state_gameplay._master_game._matrix_max_column_current)
	{
		if (game->_state_gameplay._master_game._arr_block[index_two_r][index_two_c]._type != TYPE_EMPTY && game->_state_gameplay._master_game._arr_block[index_two_r][index_two_c]._state == BLOCK_NORMAL)
		{
			two = true;
			count++;
		}
	}

	//Right
	int index_three_r = _point_begin.row;
	int index_three_c = _point_begin.column + 1;
	if (index_three_c < game->_state_gameplay._master_game._matrix_max_column_current)
	{
		if (game->_state_gameplay._master_game._arr_block[index_three_r][index_three_c]._type != TYPE_EMPTY && game->_state_gameplay._master_game._arr_block[index_three_r][index_three_c]._state == BLOCK_NORMAL)
		{
			three = true;
			count++;
		}
	}

	//BR
	int index_four_r = _point_begin.row + 1;
	int index_four_c = _point_begin.column + 1;
	if (index_four_r < game->_state_gameplay._master_game._matrix_max_row_current &&
		index_four_c < game->_state_gameplay._master_game._matrix_max_column_current)
	{
		if (game->_state_gameplay._master_game._arr_block[index_four_r][index_four_c]._type != TYPE_EMPTY && game->_state_gameplay._master_game._arr_block[index_four_r][index_four_c]._state == BLOCK_NORMAL)
		{
			four = true;
			count++;
		}
	}

	//Bot
	int index_five_r = _point_begin.row + 1;
	int index_five_c = _point_begin.column;
	if (index_five_r < game->_state_gameplay._master_game._matrix_max_row_current)
	{
		if (game->_state_gameplay._master_game._arr_block[index_five_r][index_five_c]._type != TYPE_EMPTY && game->_state_gameplay._master_game._arr_block[index_five_r][index_five_c]._state == BLOCK_NORMAL)
		{
			five = true;
			count++;
		}
	}

	//BL
	int index_six_r = _point_begin.row + 1;
	int index_six_c = _point_begin.column - 1;
	if (index_six_r < game->_state_gameplay._master_game._matrix_max_row_current &&
		index_six_c >= 0)
	{
		if (game->_state_gameplay._master_game._arr_block[index_six_r][index_six_c]._type != TYPE_EMPTY && game->_state_gameplay._master_game._arr_block[index_six_r][index_six_c]._state == BLOCK_NORMAL)
		{
			six = true;
			count++;
		}
	}

	//Left
	int index_seven_r = _point_begin.row;
	int index_seven_c = _point_begin.column - 1;
	if (index_seven_c >= 0)
	{
		if (game->_state_gameplay._master_game._arr_block[index_seven_r][index_seven_c]._type != TYPE_EMPTY && game->_state_gameplay._master_game._arr_block[index_seven_r][index_seven_c]._state == BLOCK_NORMAL)
		{
			seven = true;
			count++;
		}
	}

	//TL
	int index_eight_r = _point_begin.row - 1;
	int index_eight_c = _point_begin.column - 1;
	if (index_eight_r >= 0 && index_eight_c >= 0)
	{
		if (game->_state_gameplay._master_game._arr_block[index_eight_r][index_eight_c]._type != TYPE_EMPTY && game->_state_gameplay._master_game._arr_block[index_eight_r][index_eight_c]._state == BLOCK_NORMAL)
		{
			eight = true;
			count++;
		}
	}

	if (_type == TYPE_CLEAR)
	{
		if (game->_state_gameplay._master_game._x_combo_current >= 7)
		{
			int count_clear = game->_state_gameplay._master_game._x_combo_current;
			int index_r_begin = _point_begin.row - 7;
			int index_r_end = _point_begin.row + 7;
			int index_c_begin = _point_begin.column - 7;
			int index_c_end = _point_begin.column + 7;
			for (int i = index_r_begin; i <= index_r_end; i++)
			{
				for (int j = index_c_begin; j <= index_c_end; j++)
				{
					if (j < 0 || j >= game->_state_gameplay._master_game._matrix_max_column_current ||
						i < 0 || i >= game->_state_gameplay._master_game._matrix_max_row_current)
					{
						continue;
					}
					else if (i == _point_begin.row && j == _point_begin.column)
					{
						continue;
					}
					else
					{
						if (game->_state_gameplay._master_game._arr_block[i][j]._state == BLOCK_NORMAL)
						{
							//printf("\nindex: %d %d", i, j);
							count_clear += game->_state_gameplay._master_game._x_combo_current;
							game->_state_gameplay._master_game._arr_block[i][j]._state = BLOCK_WILL_INVI;
							game->_state_gameplay._master_game._arr_block[i][j]._effect_zoom_object_scale_in.InitPointBonus(game->_state_gameplay._master_game._x_combo_current);
						}
					}
				}
			}

			score_count += count_clear;
			//printf("\nscore_count: %d", score_count);
			/*Calculate score cache*/
			game->_state_gameplay._hud_score.AddCacheScore(score_count);
			/*End*/
			_state = BLOCK_SELECT;
			game->_state_gameplay._master_game._is_big_boom_ready = true;
			_effect_zoom_object_max.Init(_point_begin.row, _point_begin.column, game->_state_gameplay._master_game._x_combo_current);
			game->_state_gameplay._master_game.PlaySoundCombo(true);
			game->_state_gameplay._master_game._x_combo_current += 1;
			//game->_state_gameplay._hud_background.SetResetTimeBar(-1);
		}
		else
		{
			int count_clear = game->_state_gameplay._master_game._x_combo_current;
			int index_r_begin = _point_begin.row - 1;
			int index_r_end = _point_begin.row + 1;
			int index_c_begin = _point_begin.column - 1;
			int index_c_end = _point_begin.column + 1;
			for (int i = index_r_begin; i <= index_r_end; i++)
			{
				for (int j = index_c_begin; j <= index_c_end; j++)
				{
					if (j < 0 || j >= game->_state_gameplay._master_game._matrix_max_column_current ||
						i < 0 || i >= game->_state_gameplay._master_game._matrix_max_row_current)
					{
						continue;
					}
					else if (i == _point_begin.row && j == _point_begin.column)
					{
						continue;
					}
					else
					{
						if (game->_state_gameplay._master_game._arr_block[i][j]._state == BLOCK_NORMAL)
						{
							if (game->_state_gameplay._master_game._arr_block[i][j]._type == game->_state_gameplay._master_game._type_current_check)
							{
								game->_state_gameplay._master_game._arr_block[i][j]._state = BLOCK_WILL_SELECT;
							}
							else
							{
								count_clear += game->_state_gameplay._master_game._x_combo_current;
								game->_state_gameplay._master_game._arr_block[i][j]._state = BLOCK_WILL_INVI;
								game->_state_gameplay._master_game._arr_block[i][j]._effect_zoom_object_scale_in.InitPointBonus(game->_state_gameplay._master_game._x_combo_current);
							}
						}
					}
				}
			}

			score_count += count_clear;
			//printf("\nscore_count: %d", score_count);
			/*Calculate score cache*/
			game->_state_gameplay._hud_score.AddCacheScore(score_count);
			/*End*/
			_state = BLOCK_SELECT;
			_effect_zoom_object_max.Init(_point_begin.row, _point_begin.column, game->_state_gameplay._master_game._x_combo_current);
			game->_state_gameplay._master_game.PlaySoundCombo(false);
			game->_state_gameplay._master_game._x_combo_current += 1;
		}
	}
	else
	{
		if (count > 0)
		{
			//Top
			if (one)
			{
				if (game->_state_gameplay._master_game._arr_block[index_one_r][index_one_c]._type != _type)
				{
					if (game->_state_gameplay._master_game._arr_block[index_one_r][index_one_c]._type == TYPE_CLEAR)
					{
						game->_state_gameplay._master_game._arr_block[index_one_r][index_one_c]._state = BLOCK_WILL_SELECT;
					}
					else
					{
						game->_state_gameplay._master_game._arr_block[index_one_r][index_one_c]._state = BLOCK_WILL_INVI;
						score_count += game->_state_gameplay._master_game._x_combo_current;
						game->_state_gameplay._master_game._arr_block[index_one_r][index_one_c]._effect_zoom_object_scale_in.InitPointBonus(game->_state_gameplay._master_game._x_combo_current);
					}
					
				}
				else
				{
					game->_state_gameplay._master_game._arr_block[index_one_r][index_one_c]._state = BLOCK_WILL_SELECT;
				}
			}

			//TR
			if (two)
			{
				if (game->_state_gameplay._master_game._arr_block[index_two_r][index_two_c]._type != _type)
				{
					if (game->_state_gameplay._master_game._arr_block[index_two_r][index_two_c]._type == TYPE_CLEAR)
					{
						game->_state_gameplay._master_game._arr_block[index_two_r][index_two_c]._state = BLOCK_WILL_SELECT;
					}
					else
					{
						game->_state_gameplay._master_game._arr_block[index_two_r][index_two_c]._state = BLOCK_WILL_INVI;
						score_count += game->_state_gameplay._master_game._x_combo_current;
						game->_state_gameplay._master_game._arr_block[index_two_r][index_two_c]._effect_zoom_object_scale_in.InitPointBonus(game->_state_gameplay._master_game._x_combo_current);
					}
				}
				else
				{
					game->_state_gameplay._master_game._arr_block[index_two_r][index_two_c]._state = BLOCK_WILL_SELECT;
				}
			}

			//Right
			if (three)
			{
				if (game->_state_gameplay._master_game._arr_block[index_three_r][index_three_c]._type != _type)
				{
					if (game->_state_gameplay._master_game._arr_block[index_three_r][index_three_c]._type == TYPE_CLEAR)
					{
						game->_state_gameplay._master_game._arr_block[index_three_r][index_three_c]._state = BLOCK_WILL_SELECT;
					}
					else
					{
						game->_state_gameplay._master_game._arr_block[index_three_r][index_three_c]._state = BLOCK_WILL_INVI;
						score_count += game->_state_gameplay._master_game._x_combo_current;
						game->_state_gameplay._master_game._arr_block[index_three_r][index_three_c]._effect_zoom_object_scale_in.InitPointBonus(game->_state_gameplay._master_game._x_combo_current);
					}
				}
				else
				{
					game->_state_gameplay._master_game._arr_block[index_three_r][index_three_c]._state = BLOCK_WILL_SELECT;
				}
			}

			//BR
			if (four)
			{
				if (game->_state_gameplay._master_game._arr_block[index_four_r][index_four_c]._type != _type)
				{
					if (game->_state_gameplay._master_game._arr_block[index_four_r][index_four_c]._type == TYPE_CLEAR)
					{
						game->_state_gameplay._master_game._arr_block[index_four_r][index_four_c]._state = BLOCK_WILL_SELECT;
					}
					else
					{
						game->_state_gameplay._master_game._arr_block[index_four_r][index_four_c]._state = BLOCK_WILL_INVI;
						score_count += game->_state_gameplay._master_game._x_combo_current;
						game->_state_gameplay._master_game._arr_block[index_four_r][index_four_c]._effect_zoom_object_scale_in.InitPointBonus(game->_state_gameplay._master_game._x_combo_current);
					}
				}
				else
				{
					game->_state_gameplay._master_game._arr_block[index_four_r][index_four_c]._state = BLOCK_WILL_SELECT;
				}
			}

			//Bot
			if (five)
			{
				if (game->_state_gameplay._master_game._arr_block[index_five_r][index_five_c]._type != _type)
				{
					if (game->_state_gameplay._master_game._arr_block[index_five_r][index_five_c]._type == TYPE_CLEAR)
					{
						game->_state_gameplay._master_game._arr_block[index_five_r][index_five_c]._state = BLOCK_WILL_SELECT;
					}
					else
					{
						game->_state_gameplay._master_game._arr_block[index_five_r][index_five_c]._state = BLOCK_WILL_INVI;
						score_count += game->_state_gameplay._master_game._x_combo_current;
						game->_state_gameplay._master_game._arr_block[index_five_r][index_five_c]._effect_zoom_object_scale_in.InitPointBonus(game->_state_gameplay._master_game._x_combo_current);
					}
				}
				else
				{
					game->_state_gameplay._master_game._arr_block[index_five_r][index_five_c]._state = BLOCK_WILL_SELECT;
				}
			}

			//BL
			if (six)
			{
				if (game->_state_gameplay._master_game._arr_block[index_six_r][index_six_c]._type != _type)
				{
					if (game->_state_gameplay._master_game._arr_block[index_six_r][index_six_c]._type == TYPE_CLEAR)
					{
						game->_state_gameplay._master_game._arr_block[index_six_r][index_six_c]._state = BLOCK_WILL_SELECT;
					}
					else
					{
						game->_state_gameplay._master_game._arr_block[index_six_r][index_six_c]._state = BLOCK_WILL_INVI;
						score_count += game->_state_gameplay._master_game._x_combo_current;
						game->_state_gameplay._master_game._arr_block[index_six_r][index_six_c]._effect_zoom_object_scale_in.InitPointBonus(game->_state_gameplay._master_game._x_combo_current);
					}
				}
				else
				{
					game->_state_gameplay._master_game._arr_block[index_six_r][index_six_c]._state = BLOCK_WILL_SELECT;
				}
			}

			//Left
			if (seven)
			{
				if (game->_state_gameplay._master_game._arr_block[index_seven_r][index_seven_c]._type != _type)
				{
					if (game->_state_gameplay._master_game._arr_block[index_seven_r][index_seven_c]._type == TYPE_CLEAR)
					{
						game->_state_gameplay._master_game._arr_block[index_seven_r][index_seven_c]._state = BLOCK_WILL_SELECT;
					}
					else
					{
						game->_state_gameplay._master_game._arr_block[index_seven_r][index_seven_c]._state = BLOCK_WILL_INVI;
						score_count += game->_state_gameplay._master_game._x_combo_current;
						game->_state_gameplay._master_game._arr_block[index_seven_r][index_seven_c]._effect_zoom_object_scale_in.InitPointBonus(game->_state_gameplay._master_game._x_combo_current);
					}
				}
				else
				{
					game->_state_gameplay._master_game._arr_block[index_seven_r][index_seven_c]._state = BLOCK_WILL_SELECT;
				}
			}

			//TL
			if (eight)
			{
				if (game->_state_gameplay._master_game._arr_block[index_eight_r][index_eight_c]._type != _type)
				{
					if (game->_state_gameplay._master_game._arr_block[index_eight_r][index_eight_c]._type == TYPE_CLEAR)
					{
						game->_state_gameplay._master_game._arr_block[index_eight_r][index_eight_c]._state = BLOCK_WILL_SELECT;
					}
					else
					{
						game->_state_gameplay._master_game._arr_block[index_eight_r][index_eight_c]._state = BLOCK_WILL_INVI;
						score_count += game->_state_gameplay._master_game._x_combo_current;
						game->_state_gameplay._master_game._arr_block[index_eight_r][index_eight_c]._effect_zoom_object_scale_in.InitPointBonus(game->_state_gameplay._master_game._x_combo_current);
					}
				}
				else
				{
					game->_state_gameplay._master_game._arr_block[index_eight_r][index_eight_c]._state = BLOCK_WILL_SELECT;
				}
			}
		}
		score_count += game->_state_gameplay._master_game._x_combo_current;
		//printf("\nscore_count: %d", score_count);
		/*Calculate score cache*/
		game->_state_gameplay._hud_score.AddCacheScore(score_count);
		/*End*/


		_state = BLOCK_SELECT;
		_effect_zoom_object_max.Init(_point_begin.row, _point_begin.column, game->_state_gameplay._master_game._x_combo_current);

		game->_state_gameplay._master_game.PlaySoundCombo(false);
		game->_state_gameplay._master_game._x_combo_current += 1;
	}
}

int BlockGrid::GetNumbeBlockEat(bool type_clear)
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	int num_radius = 1;
	if (type_clear)
	{
		num_radius = 7;
	}
	int num_ret = 0;

	int score_count = 0;
	int count = 0;
	bool one = false;
	bool two = false;
	bool three = false;
	bool four = false;
	bool five = false;
	bool six = false;
	bool seven = false;
	bool eight = false;
	int index_row_check = _point_begin.row;
	int index_column_check = _point_begin.column;

	//Top
	int index_one_r = _point_begin.row - num_radius;
	int index_one_c = _point_begin.column;
	if (index_one_r >= 0)
	{
		if (game->_state_gameplay._master_game._arr_block[index_one_r][index_one_c]._type != TYPE_EMPTY && game->_state_gameplay._master_game._arr_block[index_one_r][index_one_c]._state == BLOCK_NORMAL)
		{
			one = true;
			count++;
		}
	}

	//TR
	int index_two_r = _point_begin.row - num_radius;
	int index_two_c = _point_begin.column + num_radius;
	if (index_two_r >= 0 && index_two_c < game->_state_gameplay._master_game._matrix_max_column_current)
	{
		if (game->_state_gameplay._master_game._arr_block[index_two_r][index_two_c]._type != TYPE_EMPTY && game->_state_gameplay._master_game._arr_block[index_two_r][index_two_c]._state == BLOCK_NORMAL)
		{
			two = true;
			count++;
		}
	}

	//Right
	int index_three_r = _point_begin.row;
	int index_three_c = _point_begin.column + num_radius;
	if (index_three_c < game->_state_gameplay._master_game._matrix_max_column_current)
	{
		if (game->_state_gameplay._master_game._arr_block[index_three_r][index_three_c]._type != TYPE_EMPTY && game->_state_gameplay._master_game._arr_block[index_three_r][index_three_c]._state == BLOCK_NORMAL)
		{
			three = true;
			count++;
		}
	}

	//BR
	int index_four_r = _point_begin.row + num_radius;
	int index_four_c = _point_begin.column + num_radius;
	if (index_four_r < game->_state_gameplay._master_game._matrix_max_row_current &&
		index_four_c < game->_state_gameplay._master_game._matrix_max_column_current)
	{
		if (game->_state_gameplay._master_game._arr_block[index_four_r][index_four_c]._type != TYPE_EMPTY && game->_state_gameplay._master_game._arr_block[index_four_r][index_four_c]._state == BLOCK_NORMAL)
		{
			four = true;
			count++;
		}
	}

	//Bot
	int index_five_r = _point_begin.row + num_radius;
	int index_five_c = _point_begin.column;
	if (index_five_r < game->_state_gameplay._master_game._matrix_max_row_current)
	{
		if (game->_state_gameplay._master_game._arr_block[index_five_r][index_five_c]._type != TYPE_EMPTY && game->_state_gameplay._master_game._arr_block[index_five_r][index_five_c]._state == BLOCK_NORMAL)
		{
			five = true;
			count++;
		}
	}

	//BL
	int index_six_r = _point_begin.row + num_radius;
	int index_six_c = _point_begin.column - num_radius;
	if (index_six_r < game->_state_gameplay._master_game._matrix_max_row_current &&
		index_six_c >= 0)
	{
		if (game->_state_gameplay._master_game._arr_block[index_six_r][index_six_c]._type != TYPE_EMPTY && game->_state_gameplay._master_game._arr_block[index_six_r][index_six_c]._state == BLOCK_NORMAL)
		{
			six = true;
			count++;
		}
	}

	//Left
	int index_seven_r = _point_begin.row;
	int index_seven_c = _point_begin.column - num_radius;
	if (index_seven_c >= 0)
	{
		if (game->_state_gameplay._master_game._arr_block[index_seven_r][index_seven_c]._type != TYPE_EMPTY && game->_state_gameplay._master_game._arr_block[index_seven_r][index_seven_c]._state == BLOCK_NORMAL)
		{
			seven = true;
			count++;
		}
	}

	//TL
	int index_eight_r = _point_begin.row - num_radius;
	int index_eight_c = _point_begin.column - num_radius;
	if (index_eight_r >= 0 && index_eight_c >= 0)
	{
		if (game->_state_gameplay._master_game._arr_block[index_eight_r][index_eight_c]._type != TYPE_EMPTY && game->_state_gameplay._master_game._arr_block[index_eight_r][index_eight_c]._state == BLOCK_NORMAL)
		{
			eight = true;
			count++;
		}
	}

	if (_type == TYPE_CLEAR)
	{
		if (game->_state_gameplay._master_game._x_combo_current >= 7)
		{
			int index_r_begin = _point_begin.row - 7;
			int index_r_end = _point_begin.row + 7;
			int index_c_begin = _point_begin.column - 7;
			int index_c_end = _point_begin.column + 7;
			for (int i = index_r_begin; i <= index_r_end; i++)
			{
				for (int j = index_c_begin; j <= index_c_end; j++)
				{
					if (j < 0 || j >= game->_state_gameplay._master_game._matrix_max_column_current ||
						i < 0 || i >= game->_state_gameplay._master_game._matrix_max_row_current)
					{
						continue;
					}
					else if (i == _point_begin.row && j == _point_begin.column)
					{
						continue;
					}
					else
					{
						if (game->_state_gameplay._master_game._arr_block[i][j]._state == BLOCK_NORMAL)
						{
							//BLOCK_WILL_INVI
							num_ret++;
						}
					}
				}
			}
		}
		else
		{
			int index_r_begin = _point_begin.row - num_radius;
			int index_r_end = _point_begin.row + num_radius;
			int index_c_begin = _point_begin.column - num_radius;
			int index_c_end = _point_begin.column + num_radius;
			for (int i = index_r_begin; i <= index_r_end; i++)
			{
				for (int j = index_c_begin; j <= index_c_end; j++)
				{
					if (j < 0 || j >= game->_state_gameplay._master_game._matrix_max_column_current ||
						i < 0 || i >= game->_state_gameplay._master_game._matrix_max_row_current)
					{
						continue;
					}
					else if (i == _point_begin.row && j == _point_begin.column)
					{
						continue;
					}
					else
					{
						if (game->_state_gameplay._master_game._arr_block[i][j]._state == BLOCK_NORMAL)
						{
							if (game->_state_gameplay._master_game._arr_block[i][j]._type == game->_state_gameplay._master_game._type_current_check)
							{
								//BLOCK_WILL_SELECT
							}
							else
							{
								//BLOCK_WILL_INVI
								num_ret++;
							}
						}
					}
				}
			}
		}
	}
	else
	{
		if (count > 0)
		{
			//Top
			if (one)
			{
				if (game->_state_gameplay._master_game._arr_block[index_one_r][index_one_c]._type != _type)
				{
					if (game->_state_gameplay._master_game._arr_block[index_one_r][index_one_c]._type == TYPE_CLEAR)
					{
						//BLOCK_WILL_SELECT
					}
					else
					{
						//BLOCK_WILL_INVI
						num_ret++;
					}

				}
				else
				{
					//BLOCK_WILL_SELECT
				}
			}

			//TR
			if (two)
			{
				if (game->_state_gameplay._master_game._arr_block[index_two_r][index_two_c]._type != _type)
				{
					if (game->_state_gameplay._master_game._arr_block[index_two_r][index_two_c]._type == TYPE_CLEAR)
					{
						//BLOCK_WILL_SELECT
					}
					else
					{
						//BLOCK_WILL_INVI
						num_ret++;
					}
				}
				else
				{
					//BLOCK_WILL_SELECT
				}
			}

			//Right
			if (three)
			{
				if (game->_state_gameplay._master_game._arr_block[index_three_r][index_three_c]._type != _type)
				{
					if (game->_state_gameplay._master_game._arr_block[index_three_r][index_three_c]._type == TYPE_CLEAR)
					{
						//BLOCK_WILL_SELECT
					}
					else
					{
						//BLOCK_WILL_INVI
						num_ret++;
					}
				}
				else
				{
					//BLOCK_WILL_SELECT
				}
			}

			//BR
			if (four)
			{
				if (game->_state_gameplay._master_game._arr_block[index_four_r][index_four_c]._type != _type)
				{
					if (game->_state_gameplay._master_game._arr_block[index_four_r][index_four_c]._type == TYPE_CLEAR)
					{
						//BLOCK_WILL_SELECT
					}
					else
					{
						//BLOCK_WILL_INVI
						num_ret++;
					}
				}
				else
				{
					//BLOCK_WILL_SELECT
				}
			}

			//Bot
			if (five)
			{
				if (game->_state_gameplay._master_game._arr_block[index_five_r][index_five_c]._type != _type)
				{
					if (game->_state_gameplay._master_game._arr_block[index_five_r][index_five_c]._type == TYPE_CLEAR)
					{
						//BLOCK_WILL_SELECT
					}
					else
					{
						//BLOCK_WILL_INVI
						num_ret++;
					}
				}
				else
				{
					//BLOCK_WILL_SELECT
				}
			}

			//BL
			if (six)
			{
				if (game->_state_gameplay._master_game._arr_block[index_six_r][index_six_c]._type != _type)
				{
					if (game->_state_gameplay._master_game._arr_block[index_six_r][index_six_c]._type == TYPE_CLEAR)
					{
						//BLOCK_WILL_SELECT
					}
					else
					{
						//BLOCK_WILL_INVI
						num_ret++;
					}
				}
				else
				{
					//BLOCK_WILL_SELECT
				}
			}

			//Left
			if (seven)
			{
				if (game->_state_gameplay._master_game._arr_block[index_seven_r][index_seven_c]._type != _type)
				{
					if (game->_state_gameplay._master_game._arr_block[index_seven_r][index_seven_c]._type == TYPE_CLEAR)
					{
						//BLOCK_WILL_SELECT
					}
					else
					{
						//BLOCK_WILL_INVI
						num_ret++;
					}
				}
				else
				{
					//BLOCK_WILL_SELECT
				}
			}

			//TL
			if (eight)
			{
				if (game->_state_gameplay._master_game._arr_block[index_eight_r][index_eight_c]._type != _type)
				{
					if (game->_state_gameplay._master_game._arr_block[index_eight_r][index_eight_c]._type == TYPE_CLEAR)
					{
						//BLOCK_WILL_SELECT
					}
					else
					{
						//BLOCK_WILL_INVI
						num_ret++;
					}
				}
				else
				{
					//BLOCK_WILL_SELECT
				}
			}
		}
	}
	return num_ret;
}

void BlockGrid::UpdatePos()
{
	ColorBorn *game = (ColorBorn*)GAME()->_current_game;

	int grid_w = game->_state_gameplay._master_game._matrix_max_column_current * game->_state_gameplay._master_game._matrix_block_width + game->_state_gameplay._master_game._grap.width * (game->_state_gameplay._master_game._matrix_max_column_current - 1);
	int grid_h = game->_state_gameplay._master_game._matrix_max_row_current * game->_state_gameplay._master_game._matrix_block_height + game->_state_gameplay._master_game._grap.height * (game->_state_gameplay._master_game._matrix_max_row_current - 1);

	int new_x = game->_point_o.X + game->_screen_width / 2 - grid_w / 2 + game->_state_gameplay._scroll_page_x;
	int new_y = game->_point_o.Y + game->_screen_height / 2 - grid_h / 2 + SCROLL_DOWN_GRID_FAKE + game->_state_gameplay._scroll_page_y;
	_point_begin_pixel.X = _point_begin.column * (game->_state_gameplay._master_game._matrix_block_width + game->_state_gameplay._master_game._grap.width) + new_x;
	_point_begin_pixel.Y = _point_begin.row * (game->_state_gameplay._master_game._matrix_block_height + game->_state_gameplay._master_game._grap.height) + new_y;

	_point_begin_pixel.X += game->_state_gameplay._master_game._effect_wave_circle._matrix_pos_current[_point_begin.row][_point_begin.column].X;
	_point_begin_pixel.Y += game->_state_gameplay._master_game._effect_wave_circle._matrix_pos_current[_point_begin.row][_point_begin.column].Y;
}

void BlockGrid::EffectZoomObjectMax::Default()
{
	state = 0;
}

void BlockGrid::EffectZoomObjectMax::Init(int row, int column, int p_bonus)
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	effect_point_begin = game->_state_gameplay._master_game._arr_block[row][column]._point_begin;
	effect_point_begin_pixel = game->_state_gameplay._master_game._arr_block[row][column]._point_begin_pixel;
	effect_point_draw_pixel = game->_state_gameplay._master_game._arr_block[row][column]._point_draw_pixel;
	effect_is_touch_state = game->_state_gameplay._master_game._arr_block[row][column]._is_touch_state;
	effect_state_block = game->_state_gameplay._master_game._arr_block[row][column]._state;
	effect_type = game->_state_gameplay._master_game._arr_block[row][column]._type;
	effect_color = game->_state_gameplay._master_game._arr_block[row][column]._color;
	effect_radius_begin = game->_state_gameplay._master_game._matrix_block_width / 2;
	effect_radius = game->_state_gameplay._master_game._matrix_block_width / 2;

	effect_radius_target = game->_state_gameplay._master_game._matrix_block_width * 2 + game->_state_gameplay._master_game._grap.width / 2;
	int frame_need = FRAME_RATE_SPEED_MAX;
	effect_speed = (effect_radius_target - (game->_state_gameplay._master_game._matrix_block_width / 2)) / frame_need;

	state = 1;
	point_bonus = p_bonus;
	if (effect_type == TYPE_CLEAR)
	{
		is_type_clear = true;
		effect_radius_target = game->_state_gameplay._master_game._matrix_block_width * 2 + game->_state_gameplay._master_game._grap.width / 2;
		effect_speed = (effect_radius_target - (game->_state_gameplay._master_game._matrix_block_width / 2)) / frame_need;
		if (game->_state_gameplay._master_game._is_big_boom_ready)
		{
			SetBigRadius();
		}
		DefaultEffectTypeClear();
	}
	else
	{
		is_type_clear = false;
	}
}

void BlockGrid::EffectZoomObjectMax::Render(float pos_x, float pos_y)
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	if (state >= 1 && state <= 3)
	{
		float row = game->_state_gameplay._master_game._matrix_max_row_current;
		float column = game->_state_gameplay._master_game._matrix_max_column_current;
		float block_width = game->_state_gameplay._master_game._matrix_block_width;
		float block_heigh = game->_state_gameplay._master_game._matrix_block_height;
		float grap_width = game->_state_gameplay._master_game._grap.width;
		float grap_height = game->_state_gameplay._master_game._grap.height;

		float grid_w = column * block_width + grap_width * (column - 1);
		float grid_h = row * block_heigh + grap_height * (row - 1);

		float new_x = game->_point_o.X + game->_screen_width / 2 - grid_w / 2 + pos_x;
		float new_y = game->_point_o.Y + game->_screen_height / 2 - grid_h / 2 + SCROLL_DOWN_GRID_FAKE + pos_y;
		int draw_x = new_x + 0.0f;
		int draw_y = new_y + 0.0f;

		draw_x = effect_point_begin.column * (block_width + (grap_width)) + new_x;
		draw_y = effect_point_begin.row * (block_heigh + (grap_height)) + new_y;

		draw_x += game->_state_gameplay._master_game._effect_wave_circle._matrix_pos_current[effect_point_begin.row][effect_point_begin.column].X;
		draw_y += game->_state_gameplay._master_game._effect_wave_circle._matrix_pos_current[effect_point_begin.row][effect_point_begin.column].Y;

		draw_x += game->_state_gameplay._scroll_page_x;
		draw_y += game->_state_gameplay._scroll_page_y;

		float opacity = 1.0f;
		opacity = ((1.0f - getCurrentPercent()) / 0.5f) * 100.0f;
		if (opacity < 0.0f)
		{
			opacity = 0.0f;
		}
		if (opacity > 100.0f)
		{
			opacity = 100.0f;
		}
		opacity = (opacity / 100.0f) * game->_state_gameplay._master_game._opacity_grid;
		G()->SetOpacity((int)opacity);
		if (effect_type != TYPE_EMPTY)
		{
			G()->SetColor(effect_color);
#if defined (ANDROID_OS)
			for (int i = (int)effect_radius - 3; i <= (int)effect_radius; i ++)
#else
			for (float i = effect_radius - 3.0f; i <= effect_radius; i += 0.5f)
#endif
			{
				if (effect_type == TYPE_CLEAR)
				{
					G()->DrawCircle(draw_x + game->_state_gameplay._master_game._matrix_block_width / 2, draw_y + game->_state_gameplay._master_game._matrix_block_width / 2, i, 13);
				}
				else
				{
					G()->DrawCircle(draw_x + game->_state_gameplay._master_game._matrix_block_width / 2, draw_y + game->_state_gameplay._master_game._matrix_block_width / 2, i, 13);
				}
			}

			G()->SetColorMask(effect_color);
			CMatrix4x4Util matrix_text;
			matrix_text.reNew();
			matrix_text.DoScale(0.35f, 0.35f, draw_x + game->_state_gameplay._master_game._matrix_block_width / 2, draw_y + game->_state_gameplay._master_game._matrix_block_width / 2);
			G()->SetTransform(matrix_text.toPineTranform());
			GET_SPRITE(SPRITEID_FONT_SCORE_INGAME)->DrawAnsiTextFormat(G(), draw_x + game->_state_gameplay._master_game._matrix_block_width / 2, draw_y + game->_state_gameplay._master_game._matrix_block_width / 2 + 50.0f, _HCENTER, "+%d", point_bonus);
			G()->ClearTransform();
			G()->ClearColorMask();
			//G()->FillCircle(draw_x + game->_state_gameplay._master_game._matrix_block_width / 2, draw_y + game->_state_gameplay._master_game._matrix_block_width / 2, effect_radius / 3, 5);
		}
		G()->SetOpacity(100);
	}
}

void BlockGrid::EffectZoomObjectMax::Update()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	if (state == 1)
	{
		UpdateEffectTypeClear();
		effect_radius += effect_speed;
		if (effect_radius >= effect_radius_target)
		{
			effect_radius = effect_radius_begin;
			state = 4;
		}
	}

	/*if (state == 1)
	{
		effect_radius += effect_speed;
		if (effect_radius >= effect_radius_target)
		{
			effect_radius = effect_radius_target;
			state = 2;
			effect_radius_target = 0.0f;
			int frame_need = 15;
			effect_speed = (effect_radius_target - (game->_state_gameplay._master_game._matrix_block_width * 3 / 2)) / frame_need;
		}
	}
	if (state == 3)
	{
		effect_radius += effect_speed;
		if (effect_radius <= 0.0f)
		{
			effect_radius = 0.0f;
			state = 4;
		}
	}*/
}

bool BlockGrid::EffectZoomObjectMax::isZoomFinish()
{
	if (state == 2)
	{
		return true;
	}
	else
		return false;
}

bool BlockGrid::EffectZoomObjectMax::isOverPercent(float percent)
{
	if (state == 1)
	{
		float value_current = effect_radius - effect_radius_begin;
		float value_end = effect_radius_target - effect_radius_begin;

		float percent_current = value_current / (value_end * 1.0f);
		if (percent_current >= percent)
		{
			return true;
		}
		else
			return false;
	}
	else
		return false;
}

float BlockGrid::EffectZoomObjectMax::getCurrentPercent()
{
	float value_current = effect_radius - effect_radius_begin;
	float value_end = effect_radius_target - effect_radius_begin;

	float percent_current = value_current / (value_end * 1.0f);
	return percent_current;
}

bool BlockGrid::EffectZoomObjectMax::isRunning()
{
	if (state >= 1 && state <= 3)
	{
		return true;
	}
	else
		return false;
}

bool BlockGrid::EffectZoomObjectMax::isFinish()
{
	if (state <= 0 || state >= 4)
	{
		return true;
	}
	else
		return false;
}

void BlockGrid::EffectZoomObjectMax::DefaultEffectTypeClear()
{
	effect_color = 0xFFA052DF;
	effect_type_clear_type_color = 2;
	effect_type_clear_color_target = 0xFFF1930C;
	effect_type_clear_transform_color.Default();
	effect_type_clear_transform_color.Init(effect_color, effect_type_clear_color_target, 10);
}

void BlockGrid::EffectZoomObjectMax::InitEffectTypeClear()
{
	effect_type_clear_type_color++;
	if (effect_type_clear_type_color > 5)
	{
		effect_type_clear_type_color = 1;
	}
	switch (effect_type_clear_type_color)
	{
	case 1:
		//tim
		effect_type_clear_color_target = 0xFFA052DF;
		break;
	case 2:
		//cam
		effect_type_clear_color_target = 0xFFF1930C;
		break;
	case 3:
		//blue
		effect_type_clear_color_target = 0xFF257CE2;
		break;
	case 4:
		//green
		effect_type_clear_color_target = 0xFF70C045;
		break;
	case 5:
		//pink
		effect_type_clear_color_target = 0xFFE5347A;
		break;
	default:
		break;
	}
	effect_type_clear_transform_color.Init(effect_color, effect_type_clear_color_target, 10);
}

void BlockGrid::EffectZoomObjectMax::UpdateEffectTypeClear()
{
	if (is_type_clear)
	{
		effect_type_clear_transform_color.Update();
		effect_color = effect_type_clear_transform_color._draw_color;
		if (effect_type_clear_transform_color.isFinish())
		{
			InitEffectTypeClear();
		}
	}	
}

void BlockGrid::EffectZoomObjectMax::SetBigRadius()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	int column_max, row_max;
	column_max = 0;
	for (int i = 0; i <= effect_point_begin.column; i++)
	{
		column_max++;
	}
	if (column_max < 4)
	{
		column_max = 7 - column_max;
	}
	else if (column_max > 4)
	{
		column_max = (column_max - 4) + 3;
	}
	else
	{
		column_max = 3;
	}

	row_max = 0;
	for (int i = 0; i <= effect_point_begin.row; i++)
	{
		row_max++;
	}
	if (row_max < 4)
	{
		row_max = 7 - row_max;
	}
	else if (row_max > 4)
	{
		row_max = (row_max - 4) + 3;
	}
	else
	{
		row_max = 3;
	}

	float a_column = game->_state_gameplay._master_game._matrix_block_width / 2;
	a_column += game->_state_gameplay._master_game._matrix_block_width * column_max;
	a_column += game->_state_gameplay._master_game._grap.width * column_max;

	float b_row = game->_state_gameplay._master_game._matrix_block_height / 2;
	b_row += game->_state_gameplay._master_game._matrix_block_height * row_max;
	b_row += game->_state_gameplay._master_game._grap.height * row_max;

	float frame_need = FRAME_RATE_SPEED_MAX;
	if (column_max > row_max)
	{
		frame_need = FRAME_RATE_SPEED_MAX;
	}
	else
	{
		frame_need = FRAME_RATE_SPEED_MAX;
	}

	effect_radius_target = CMath::SQRT((a_column * a_column) + (b_row * b_row));
	effect_speed = (effect_radius_target - (game->_state_gameplay._master_game._matrix_block_width / 2)) / (frame_need);
}


void BlockGrid::EffectZoomObjectScaleIn::Default()
{
	state = 0;
}

void BlockGrid::EffectZoomObjectScaleIn::InitPointBonus(int point)
{
	point_bonus = point;
}

void BlockGrid::EffectZoomObjectScaleIn::Init(int row, int column)
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	state = 1;

	effect_point_begin = game->_state_gameplay._master_game._arr_block[row][column]._point_begin;
	effect_point_begin_pixel = game->_state_gameplay._master_game._arr_block[row][column]._point_begin_pixel;
	effect_point_draw_pixel = game->_state_gameplay._master_game._arr_block[row][column]._point_draw_pixel;
	effect_is_touch_state = game->_state_gameplay._master_game._arr_block[row][column]._is_touch_state;
	effect_state_block = game->_state_gameplay._master_game._arr_block[row][column]._state;
	effect_type = game->_state_gameplay._master_game._arr_block[row][column]._type;
	effect_color = game->_state_gameplay._master_game._arr_block[row][column]._color;
	effect_radius = game->_state_gameplay._master_game._matrix_block_width / 2 + game->_state_gameplay._master_game._effect_idle_zoom.value_current;


	effect_radius_target = 0.0f;
	int frame_need = FRAME_RATE_SPEED_IN;
	effect_speed = (effect_radius_target - (game->_state_gameplay._master_game._matrix_block_width / 2)) / frame_need;

	percent = 1.0f;
	speed = 1.0f / (frame_need * 1.0f);
}

void BlockGrid::EffectZoomObjectScaleIn::Render(float pos_x, float pos_y)
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	if (state == 1)
	{
		float row = game->_state_gameplay._master_game._matrix_max_row_current;
		float column = game->_state_gameplay._master_game._matrix_max_column_current;
		float block_width = game->_state_gameplay._master_game._matrix_block_width;
		float block_heigh = game->_state_gameplay._master_game._matrix_block_height;
		float grap_width = game->_state_gameplay._master_game._grap.width;
		float grap_height = game->_state_gameplay._master_game._grap.height;

		float grid_w = column * block_width + grap_width * (column - 1);
		float grid_h = row * block_heigh + grap_height * (row - 1);

		float new_x = game->_point_o.X + game->_screen_width / 2 - grid_w / 2 + pos_x;
		float new_y = game->_point_o.Y + game->_screen_height / 2 - grid_h / 2 + SCROLL_DOWN_GRID_FAKE + pos_y;
		int draw_x = new_x + 0.0f;
		int draw_y = new_y + 0.0f;

		draw_x = effect_point_begin.column * (block_width + (grap_width)) + new_x;
		draw_y = effect_point_begin.row * (block_heigh + (grap_height)) + new_y;

		draw_x += game->_state_gameplay._master_game._effect_wave_circle._matrix_pos_current[effect_point_begin.row][effect_point_begin.column].X;
		draw_y += game->_state_gameplay._master_game._effect_wave_circle._matrix_pos_current[effect_point_begin.row][effect_point_begin.column].Y;

		draw_x += game->_state_gameplay._scroll_page_x;
		draw_y += game->_state_gameplay._scroll_page_y;

		float scale_block = (effect_radius * 2.0f) / (GET_SPRITE(SPRITEID_OBJECT_01_N_COLOR)->GetFrameWidth(0)*1.0f);
		float opacity = 100.0f * percent;
		opacity = (opacity / 100.0f) * game->_state_gameplay._master_game._opacity_grid;

		if (effect_type != TYPE_EMPTY)
		{
			G()->SetOpacity((int)opacity);
			if (effect_type == TYPE_CLEAR)
			{
				CMatrix4x4Util matrix_normal;
				matrix_normal.reNew();
				matrix_normal.DoScale(scale_block, scale_block, draw_x + game->_state_gameplay._master_game._matrix_block_width / 2, draw_y + game->_state_gameplay._master_game._matrix_block_width / 2);
				G()->SetTransform(matrix_normal.toPineTranform());
				GET_SPRITE(SPRITEID_OBJECT_01)->DrawFrame(G(), 0, draw_x + game->_state_gameplay._master_game._matrix_block_width / 2, draw_y + game->_state_gameplay._master_game._matrix_block_width / 2);
				G()->ClearTransform();
			}
			else
			{
				G()->SetColor(effect_color);
#if defined (ANDROID_OS)
				for (int i = (int)effect_radius - 3; i <= (int)effect_radius; i++)
#else
				for (float i = effect_radius - 3.0f; i <= effect_radius; i += 0.5f)
#endif
				{
					G()->DrawCircle(draw_x + game->_state_gameplay._master_game._matrix_block_width / 2, draw_y + game->_state_gameplay._master_game._matrix_block_width / 2, effect_radius, 10);
				}
			}
			G()->SetOpacity(100);

			opacity = 100.0f * (percent / 0.2f);
			if (opacity > 100.0f)
			{
				opacity = 100.0f;
			}
			opacity = (opacity / 100.0f) * game->_state_gameplay._master_game._opacity_grid;
			G()->SetOpacity((int)opacity);
			G()->SetColorMask(effect_color);
			CMatrix4x4Util matrix_text;
			matrix_text.reNew();
			matrix_text.DoScale(0.35f, 0.35f, draw_x + game->_state_gameplay._master_game._matrix_block_width / 2, draw_y + game->_state_gameplay._master_game._matrix_block_width / 2);
			G()->SetTransform(matrix_text.toPineTranform());
			GET_SPRITE(SPRITEID_FONT_SCORE_INGAME)->DrawAnsiTextFormat(G(), draw_x + game->_state_gameplay._master_game._matrix_block_width / 2, draw_y + game->_state_gameplay._master_game._matrix_block_width / 2 + 50.0f, _HCENTER, "+%d", point_bonus);
			G()->ClearTransform();
			G()->ClearColorMask();
			G()->SetOpacity(100);
			//G()->FillCircle(draw_x + game->_state_gameplay._master_game._matrix_block_width / 2, draw_y + game->_state_gameplay._master_game._matrix_block_width / 2, effect_radius / 3, 5);
		}
	}
}

void BlockGrid::EffectZoomObjectScaleIn::Update()
{
	if (state == 1)
	{
		percent -= speed;
		if (percent <= 0.0f)
		{
			percent = 0.0f;
			state = 2;
		}
	}
}

bool BlockGrid::EffectZoomObjectScaleIn::isRunning()
{
	if (state == 1)
	{
		return true;
	}
	else
		return false;
}

bool BlockGrid::EffectZoomObjectScaleIn::isFinish()
{
	if (state >= 2 || state <= 0)
	{
		return true;
	}
	else
		return false;
}

void BlockGrid::EffectZoomObjectReborn::Default()
{
	state = 0;
}

void BlockGrid::EffectZoomObjectReborn::Init(int row, int column, int type)
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	state = 1;

	effect_point_begin = game->_state_gameplay._master_game._arr_block[row][column]._point_begin;
	effect_point_begin_pixel = game->_state_gameplay._master_game._arr_block[row][column]._point_begin_pixel;
	effect_point_draw_pixel = game->_state_gameplay._master_game._arr_block[row][column]._point_draw_pixel;
	effect_is_touch_state = game->_state_gameplay._master_game._arr_block[row][column]._is_touch_state;
	effect_state_block = game->_state_gameplay._master_game._arr_block[row][column]._state;
	effect_type = type;
	effect_color = game->_state_gameplay._master_game.GetCurrentColor(type);
	effect_radius = 0.0f;


	effect_radius_target = game->_state_gameplay._master_game._matrix_block_width / 2;
	int frame_need = FRAME_RATE_SPEED_RETURN;
	effect_speed = (effect_radius_target - (0.0f)) / frame_need;
}

void BlockGrid::EffectZoomObjectReborn::Render(float pos_x, float pos_y)
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	if (state == 1)
	{
		float row = game->_state_gameplay._master_game._matrix_max_row_current;
		float column = game->_state_gameplay._master_game._matrix_max_column_current;
		float block_width = game->_state_gameplay._master_game._matrix_block_width;
		float block_heigh = game->_state_gameplay._master_game._matrix_block_height;
		float grap_width = game->_state_gameplay._master_game._grap.width;
		float grap_height = game->_state_gameplay._master_game._grap.height;

		float grid_w = column * block_width + grap_width * (column - 1);
		float grid_h = row * block_heigh + grap_height * (row - 1);

		float new_x = game->_point_o.X + game->_screen_width / 2 - grid_w / 2 + pos_x;
		float new_y = game->_point_o.Y + game->_screen_height / 2 - grid_h / 2 + SCROLL_DOWN_GRID_FAKE + pos_y;
		int draw_x = new_x + 0.0f;
		int draw_y = new_y + 0.0f;

		draw_x = effect_point_begin.column * (block_width + (grap_width)) + new_x;
		draw_y = effect_point_begin.row * (block_heigh + (grap_height)) + new_y;

		draw_x += game->_state_gameplay._master_game._effect_wave_circle._matrix_pos_current[effect_point_begin.row][effect_point_begin.column].X;
		draw_y += game->_state_gameplay._master_game._effect_wave_circle._matrix_pos_current[effect_point_begin.row][effect_point_begin.column].Y;

		draw_x += game->_state_gameplay._scroll_page_x;
		draw_y += game->_state_gameplay._scroll_page_y;

		float radius = effect_radius + game->_state_gameplay._master_game._effect_idle_zoom.value_current;
		float scale_block = (radius * 2.0f) / (GET_SPRITE(SPRITEID_OBJECT_01_N_COLOR)->GetFrameWidth(0)*1.0f);
		if (effect_type != TYPE_EMPTY)
		{
			int opacity = 100 * getPercent();
			opacity = (opacity / 100.0f) * game->_state_gameplay._master_game._opacity_grid;
			G()->SetOpacity(opacity);
			if (effect_type == TYPE_CLEAR)
			{
				CMatrix4x4Util matrix_normal;
				matrix_normal.reNew();
				matrix_normal.DoScale(scale_block, scale_block, draw_x + game->_state_gameplay._master_game._matrix_block_width / 2, draw_y + game->_state_gameplay._master_game._matrix_block_width / 2);
				G()->SetTransform(matrix_normal.toPineTranform());
				GET_SPRITE(SPRITEID_OBJECT_01)->DrawFrame(G(), 0, draw_x + game->_state_gameplay._master_game._matrix_block_width / 2, draw_y + game->_state_gameplay._master_game._matrix_block_width / 2);
				G()->ClearTransform();
			}
			else
			{
				G()->SetColor(effect_color);
				for (float i = radius - 3.0f; i <= radius; i += 0.5f)
				{
					G()->DrawCircle(draw_x + game->_state_gameplay._master_game._matrix_block_width / 2, draw_y + game->_state_gameplay._master_game._matrix_block_width / 2, radius, 5, true);
				}
			}
			

			//G()->FillCircle(draw_x + game->_state_gameplay._master_game._matrix_block_width / 2, draw_y + game->_state_gameplay._master_game._matrix_block_width / 2, radius / 3, 5, true);
			G()->SetOpacity(100);
		}
	}
}

void BlockGrid::EffectZoomObjectReborn::Update()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	if (state == 1)
	{
		effect_radius += effect_speed;
		if (effect_radius >= (game->_state_gameplay._master_game._matrix_block_width / 2))
		{
			effect_radius = (game->_state_gameplay._master_game._matrix_block_width / 2);
			state = 2;
		}
	}
}

bool BlockGrid::EffectZoomObjectReborn::isRunning()
{
	if (state == 1)
	{
		return true;
	}
	else
		return false;
}

bool BlockGrid::EffectZoomObjectReborn::isFinish()
{
	if (state >= 2 || state <= 0)
	{
		return true;
	}
	else
		return false;
}

float BlockGrid::EffectZoomObjectReborn::getPercent()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	float ret = 0.0f;
	ret = effect_radius / (game->_state_gameplay._master_game._matrix_block_width / 2);
	return ret;
}

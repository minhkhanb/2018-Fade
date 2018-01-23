#include "pch.h"
#include "../../../GameCore/CGame.h"

//0.60f
//0.989f
//0.55f
//0.993f
//0.64f
//0.98f

#define BOOM_POWER				0.2f		
#define BOOM_WEAK_PERCENT		0.95f

#define BOOM_POWER_CLEAR				2.0f		
#define BOOM_WEAK_CLEAR_PERCENT			0.96f

void MatrixDraw::ResetGrid()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	_matrix_max_row_current = 7;
	_matrix_max_column_current = 7;

	SetValueGrap();

	int width = GetCurrentBlockWidth();
	int height = GetCurrentBlockHeight();
	_matrix_block_width = width;
	_matrix_block_height = height;
	if (_arr_block != nullptr)
	{
		SAFE_DEL_ARRAY(_arr_block);
	}
	_arr_block = new BlockGrid*[_matrix_max_row_current];
	for (int i = 0; i < _matrix_max_row_current; i++)
	{
		_arr_block[i] = new BlockGrid[_matrix_max_column_current];
	}
	InitMatrix();
	_effect_idle_zoom.Init(0.0f, 5.0f);
	_effect_wave_circle.Default(_matrix_max_row_current, _matrix_max_column_current);
	_effect_type_clear_idle.Default();
	_effect_fade_in_fade_out_grid.Default();
}

void MatrixDraw::InitGrid7x7()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	_matrix_max_row_current = 7;
	_matrix_max_column_current = 7;

	SetValueGrap();

	int width = GetCurrentBlockWidth();
	int height = GetCurrentBlockHeight();
	_matrix_block_width = width;
	_matrix_block_height = height;

	if (_arr_block != nullptr)
	{
		SAFE_DEL_ARRAY(_arr_block);
	}
	_arr_block = new BlockGrid*[_matrix_max_row_current];
	for (int i = 0; i < _matrix_max_row_current; i++)
	{
		_arr_block[i] = new BlockGrid[_matrix_max_column_current];
	}
	InitMatrix();
	_effect_idle_zoom.Init(0.0f, 5.0f);
	_effect_wave_circle.Default(_matrix_max_row_current, _matrix_max_column_current);
	_effect_type_clear_idle.Default();
	_opacity_grid = 100.0f;
	_effect_fade_in_fade_out_grid.Default();
	_is_big_boom_ready = false;
}

void MatrixDraw::InitMatrix()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	_index_touch_matrix = -1;
	_current_block_choose = 1;
	_x_combo_current = 1;
	_type_current_check = -100;
	for (int i = 0; i < _matrix_max_row_current; i++)
	{
		for (int j = 0; j < _matrix_max_column_current; j++)
		{
			int type_random = 2;
			type_random = CMath::RANDOM(1, 6);
			_arr_block[i][j].Init(j, i, type_random);
		}
	}

	if (_matrix_max_row_current < 8)
	{
		for (int i = 0; i < _matrix_max_row_current; i++)
		{
			for (int j = 0; j < _matrix_max_column_current; j++)
			{
				_arr_block_test[i][j] = _arr_block[i][j];
			}
		}
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				_arr_block_test[i][j] = _arr_block[i][j];
			}
		}
	}
	_state_matrix = MATRIX_CAN_TOUCH;
	_sound_combo_index_current = 1;
	_time_counter_stun = 0;
}

void MatrixDraw::InitMatrixForTutorial()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	_index_touch_matrix = -1;
	_current_block_choose = 1;
	_x_combo_current = 1;
	_type_current_check = -100;
	for (int i = 0; i < _matrix_max_row_current; i++)
	{
		for (int j = 0; j < _matrix_max_column_current; j++)
		{
			int type_random = 2;
			type_random = CMath::RANDOM(1, 6);
			_arr_block[i][j].Init(j, i, type_random);
		}
	}
	int type_random = 2;
	type_random = CMath::RANDOM(1, 6);
	for (int i = 0; i < _matrix_max_row_current; i++)
	{
		_arr_block[i][game->_state_gameplay._hud_tutorial._index_column_choose].Init(game->_state_gameplay._hud_tutorial._index_column_choose, i, type_random);
	}

	if (_matrix_max_row_current < 8)
	{
		for (int i = 0; i < _matrix_max_row_current; i++)
		{
			for (int j = 0; j < _matrix_max_column_current; j++)
			{
				_arr_block_test[i][j] = _arr_block[i][j];
			}
		}
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				_arr_block_test[i][j] = _arr_block[i][j];
			}
		}
	}
	_state_matrix = MATRIX_CAN_TOUCH;
	_time_counter_stun = 0;
}

void MatrixDraw::InitMatrixForTutorialClear()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	_index_touch_matrix = -1;
	_current_block_choose = 1;
	_x_combo_current = 1;
	_type_current_check = -100;
	for (int i = 0; i < _matrix_max_row_current; i++)
	{
		for (int j = 0; j < _matrix_max_column_current; j++)
		{
			int type_random = 2;
			type_random = CMath::RANDOM(1, 6);
			_arr_block[i][j].Init(j, i, type_random);
		}
	}
	int type_random = 2;
	type_random = CMath::RANDOM(1, 6);
	for (int i = 0; i < _matrix_max_row_current; i++)
	{
		_arr_block[i][game->_state_gameplay._hud_tutorial._index_column_choose].Init(game->_state_gameplay._hud_tutorial._index_column_choose, i, type_random);
	}
	_arr_block[0][game->_state_gameplay._hud_tutorial._index_column_choose].Init(game->_state_gameplay._hud_tutorial._index_column_choose, 0, TYPE_CLEAR);

	if (_matrix_max_row_current < 8)
	{
		for (int i = 0; i < _matrix_max_row_current; i++)
		{
			for (int j = 0; j < _matrix_max_column_current; j++)
			{
				_arr_block_test[i][j] = _arr_block[i][j];
			}
		}
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				_arr_block_test[i][j] = _arr_block[i][j];
			}
		}
	}
	_state_matrix = MATRIX_CAN_TOUCH;
	_time_counter_stun = 0;
}

void MatrixDraw::UpdateMatrix()
{
	ColorBorn *game = (ColorBorn*)GAME()->_current_game;
	//printf("\nState: %d", _state_matrix);
	UpdatePosMatrix();
	if (_state_matrix == MATRIX_CLEAR_TOUCH)
	{
		for (int i = 0; i < game->_state_gameplay._master_game._matrix_max_row_current; i++)
		{
			for (int j = 0; j < game->_state_gameplay._master_game._matrix_max_column_current; j++)
			{
				_arr_block[i][j].UpdateStateSelect();
			}
		}

		for (int i = 0; i < game->_state_gameplay._master_game._matrix_max_row_current; i++)
		{
			for (int j = 0; j < game->_state_gameplay._master_game._matrix_max_column_current; j++)
			{
				_arr_block[i][j].UpdateStateScaleOut();
			}
		}

		UpdateCheckAllFinishEffectEplant();



		for (int i = 0; i < game->_state_gameplay._master_game._matrix_max_row_current; i++)
		{
			for (int j = 0; j < game->_state_gameplay._master_game._matrix_max_column_current; j++)
			{
				_arr_block[i][j].UpdateStateTargetJoin();
			}
		}
	}
	if (_state_matrix == MATRIX_LOOP_CHECK_FILL)
	{
		for (int i = 0; i < game->_state_gameplay._master_game._matrix_max_row_current; i++)
		{
			for (int j = 0; j < game->_state_gameplay._master_game._matrix_max_column_current; j++)
			{
				_arr_block[i][j].UpdateStateSelect();
			}
		}

		for (int i = 0; i < game->_state_gameplay._master_game._matrix_max_row_current; i++)
		{
			for (int j = 0; j < game->_state_gameplay._master_game._matrix_max_column_current; j++)
			{
				_arr_block[i][j].UpdateStateScaleOut();
			}
		}

		UpdateCheckAllFinishEffectEplant();

		for (int i = 0; i < game->_state_gameplay._master_game._matrix_max_row_current; i++)
		{
			for (int j = 0; j < game->_state_gameplay._master_game._matrix_max_column_current; j++)
			{
				_arr_block[i][j].UpdateStateTargetJoin();
			}
		}

		int num = 0;
		for (int i = 0; i < game->_state_gameplay._master_game._matrix_max_row_current; i++)
		{
			for (int j = 0; j < game->_state_gameplay._master_game._matrix_max_column_current; j++)
			{
				if (_arr_block[i][j]._state == BLOCK_TARGET_JOIN || _arr_block[i][j]._state == BLOCK_WILL_SELECT || _arr_block[i][j]._state == BLOCK_SELECT || _arr_block[i][j]._state == BLOCK_TOUCH_DOWN)
				{
					num++;
				}
			}
		}
		if (num == 0)
		{
			_state_matrix = MATRIX_STUN;
			printf("\nCurrentCombo: %d", _x_combo_current);
			bool set_insert_type_clear = false;
			int num_random = -1;
			if (_x_combo_current - 1 >= 7)
			{
				set_insert_type_clear = true;
				int total = GetTotalBlockLikeTypeAndState(BLOCK_NORMAL, TYPE_EMPTY);
				if (total >= 1)
				{
					num_random = CMath::RANDOM(1, total);
				}
				else
				{
					num_random = 0;
				}
			}
			int counter = 1;
			for (int i = 0; i < game->_state_gameplay._master_game._matrix_max_row_current; i++)
			{
				for (int j = 0; j < game->_state_gameplay._master_game._matrix_max_column_current; j++)
				{
					if (_arr_block[i][j]._type == TYPE_EMPTY)
					{
						int type_random = 2;
						type_random = CMath::RANDOM(1, 5);
						_arr_block[i][j]._state = BLOCK_REBORN;
						_arr_block[i][j]._effect_zoom_object_reborn.Init(i, j, type_random);
						if (set_insert_type_clear)
						{
							if (counter == num_random)
							{
								set_insert_type_clear = false;
								_arr_block[i][j]._state = BLOCK_REBORN;
								_arr_block[i][j]._effect_zoom_object_reborn.Init(i, j, TYPE_CLEAR);
								game->_state_gameplay._effect_fish_tank.Add(_arr_block[i][j]._point_begin_pixel.X + game->_state_gameplay._master_game._matrix_block_width / 2, _arr_block[i][j]._point_begin_pixel.Y + game->_state_gameplay._master_game._matrix_block_height / 2);
							}
							counter++;
						}
					}
				}
			}
		}
	}
	if (_state_matrix == MATRIX_STUN)
	{
		int num = 0;
		for (int i = 0; i < game->_state_gameplay._master_game._matrix_max_row_current; i++)
		{
			for (int j = 0; j < game->_state_gameplay._master_game._matrix_max_column_current; j++)
			{
				if (_arr_block[i][j]._state == BLOCK_REBORN)
				{
					num++;
				}
			}
		}
		if (num >= 47)
		{
			_time_counter_stun++;
			if (_time_counter_stun > 60)
			{
				_time_counter_stun = 0;
				_state_matrix = MATRIX_REFILL;
			}
		}
		else
		{
			_state_matrix = MATRIX_REFILL;
		}
	}
	if (_state_matrix == MATRIX_REFILL)
	{
		for (int i = 0; i < game->_state_gameplay._master_game._matrix_max_row_current; i++)
		{
			for (int j = 0; j < game->_state_gameplay._master_game._matrix_max_column_current; j++)
			{
				_arr_block[i][j].UpdateReborn();
			}
		}
		int num = 0;
		for (int i = 0; i < game->_state_gameplay._master_game._matrix_max_row_current; i++)
		{
			for (int j = 0; j < game->_state_gameplay._master_game._matrix_max_column_current; j++)
			{
				if (_arr_block[i][j]._state == BLOCK_REBORN)
				{
					num++;
				}
			}
		}
		if (num == 0)
		{
			_state_matrix = MATRIX_CAN_TOUCH;
		}
	}

	//_effect_wave_circle.Update();
	_effect_wave_circle.Update();
	/*-----------------------------------------------------------------------------------------------------------------------------------*/
	_effect_idle_zoom.Update();
	_effect_type_clear_idle.Update();


	for (int i = 0; i < game->_state_gameplay._master_game._matrix_max_row_current; i++)
	{
		for (int j = 0; j < game->_state_gameplay._master_game._matrix_max_column_current; j++)
		{
			if (_arr_block[i][j]._state != BLOCK_NORMAL)
			{
				//printf("\nindex: %d, %d", i, j);
			}
		}
	}

	if (_matrix_max_row_current < 8)
	{
		for (int i = 0; i < _matrix_max_row_current; i++)
		{
			for (int j = 0; j < _matrix_max_column_current; j++)
			{
				_arr_block_test[i][j] = _arr_block[i][j];
			}
		}
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				_arr_block_test[i][j] = _arr_block[i][j];
			}
		}
	}
}

void MatrixDraw::UpdateCheckAllFinishEffectEplant()
{
	ColorBorn *game = (ColorBorn*)GAME()->_current_game;

	bool flag_submit_score = false;
	int index_center_r = 0;
	int index_center_c = 0;
	for (int i = 0; i < game->_state_gameplay._master_game._matrix_max_row_current; i++)
	{
		for (int j = 0; j < game->_state_gameplay._master_game._matrix_max_column_current; j++)
		{
			if (_arr_block[i][j]._state == BLOCK_SELECT)
			{
				flag_submit_score = true;

				index_center_r = i;
				index_center_c = j;
				/*SetValue*/
				//printf("\nIndex_check %d, %d", index_center_r, index_center_c);
				int index_r_begin = 0;
				int index_r_end = 0;
				int index_c_begin = 0;
				int index_c_end = 0;
				if (_arr_block[i][j]._type == TYPE_CLEAR && _is_big_boom_ready)
				{
					index_r_begin = index_center_r - 7;
					if (index_r_begin < 0)
					{
						index_r_begin = 0;
					}
					index_r_end = index_center_r + 7;
					if (index_r_end >= game->_state_gameplay._master_game._matrix_max_row_current - 1)
					{
						index_r_end = game->_state_gameplay._master_game._matrix_max_row_current - 1;
					}
					index_c_begin = index_center_c - 7;
					if (index_c_begin < 0)
					{
						index_c_begin = 0;
					}
					index_c_end = index_center_c + 7;
					if (index_c_end >= game->_state_gameplay._master_game._matrix_max_column_current - 1)
					{
						index_c_end = game->_state_gameplay._master_game._matrix_max_column_current - 1;
					}
				}
				else
				{
					index_r_begin = index_center_r - 1;
					if (index_r_begin < 0)
					{
						index_r_begin = 0;
					}
					index_r_end = index_center_r + 1;
					if (index_r_end > game->_state_gameplay._master_game._matrix_max_row_current - 1)
					{
						index_r_end = game->_state_gameplay._master_game._matrix_max_row_current - 1;
					}
					index_c_begin = index_center_c - 1;
					if (index_c_begin < 0)
					{
						index_c_begin = 0;
					}
					index_c_end = index_center_c + 1;
					if (index_c_end > game->_state_gameplay._master_game._matrix_max_column_current - 1)
					{
						index_c_end = game->_state_gameplay._master_game._matrix_max_column_current - 1;
					}
				}
				if (_arr_block[i][j]._effect_zoom_object_max.isOverPercent(0.2f))
				{
					for (int a = index_r_begin; a <= index_r_end; a++)
					{
						for (int b = index_c_begin; b <= index_c_end; b++)
						{
							if (_arr_block[a][b]._state == BLOCK_WILL_INVI)
							{
								_arr_block[a][b]._state = BLOCK_INVI;
								_arr_block[a][b]._effect_zoom_object_scale_in.Init(a, b);
							}
						}
					}
					/*EndSet*/
				}
				//if (_arr_block[i][j]._type != TYPE_CLEAR)
				{
					if (_arr_block[i][j]._effect_zoom_object_max.isOverPercent(0.5f))
					{
						//printf("\n r %d ---c %d", i, j);
						index_r_begin = index_center_r - 1;
						index_r_end = index_center_r + 1;
						index_c_begin = index_center_c - 1;
						index_c_end = index_center_c + 1;
						int counter_num = 0;
						int num = 0;
						bool type_here = false;
						for (int a = index_r_begin; a <= index_r_end; a++)
						{
							for (int b = index_c_begin; b <= index_c_end; b++)
							{
								if (a >= 0 && a < game->_state_gameplay._master_game._matrix_max_row_current)
								{
									if (b >= 0 && b < game->_state_gameplay._master_game._matrix_max_column_current)
									{
										if ((a == index_r_begin || a == index_r_end) && (b == index_c_begin || b == index_c_end))
										{

										}
										else
										{
											//printf("\n add a %d ---b %d", a, b);
											if (game->_state_gameplay._master_game._arr_block[a][b]._state == BLOCK_WILL_SELECT)
											{
												game->_state_gameplay._master_game._arr_block[a][b]._state = BLOCK_TOUCH_DOWN;
												counter_num += 1; (game->_state_gameplay._master_game._x_combo_current + num);
												if (game->_state_gameplay._master_game._arr_block[a][b]._type == TYPE_CLEAR && game->_state_gameplay._master_game._x_combo_current + num >= 7)
												{
													counter_num += game->_state_gameplay._master_game._arr_block[a][b].GetNumbeBlockEat(true);
													type_here = true;
													_effect_wave_circle.AddBoom(a, b, BOOM_POWER_CLEAR, BOOM_WEAK_CLEAR_PERCENT);
												}
												else
												{
													counter_num += game->_state_gameplay._master_game._arr_block[a][b].GetNumbeBlockEat(false);
													_effect_wave_circle.AddBoom(a, b, BOOM_POWER, BOOM_WEAK_PERCENT);
												}
												num += 1;
											}
										}
									}
								}
							}
						}
						if (counter_num > 0)
						{
							game->_state_gameplay._hud_background._manager_fadei_push.Add(counter_num, type_here);
						}
					}
					if (_arr_block[i][j]._effect_zoom_object_max.isOverPercent(0.6f))
					{
						//printf("\n r %d ---c %d", i, j);
						index_r_begin = index_center_r - 1;
						index_r_end = index_center_r + 1;
						index_c_begin = index_center_c - 1;
						index_c_end = index_center_c + 1;
						int counter_num = 0;
						int num = 0;
						bool type_here = false;
						for (int a = index_r_begin; a <= index_r_end; a++)
						{
							for (int b = index_c_begin; b <= index_c_end; b++)
							{
								if (a >= 0 && a < game->_state_gameplay._master_game._matrix_max_row_current)
								{
									if (b >= 0 && b < game->_state_gameplay._master_game._matrix_max_column_current)
									{
										if ((a == index_r_begin || a == index_r_end) && (b == index_c_begin || b == index_c_end))
										{
											if (game->_state_gameplay._master_game._arr_block[a][b]._state == BLOCK_WILL_SELECT)
											{
												game->_state_gameplay._master_game._arr_block[a][b]._state = BLOCK_TOUCH_DOWN;
												counter_num += 1; (game->_state_gameplay._master_game._x_combo_current + num);
												if (game->_state_gameplay._master_game._arr_block[a][b]._type == TYPE_CLEAR && game->_state_gameplay._master_game._x_combo_current + num >= 7)
												{
													counter_num += game->_state_gameplay._master_game._arr_block[a][b].GetNumbeBlockEat(true);
													type_here = true;
													_effect_wave_circle.AddBoom(a, b, BOOM_POWER_CLEAR, BOOM_WEAK_CLEAR_PERCENT);
												}
												else
												{
													counter_num += game->_state_gameplay._master_game._arr_block[a][b].GetNumbeBlockEat(false);
													_effect_wave_circle.AddBoom(a, b, BOOM_POWER, BOOM_WEAK_PERCENT);
												}
												num += 1;
											}
										}
										else
										{
										}
									}
								}
							}
						}
						if (counter_num > 0)
						{
							game->_state_gameplay._hud_background._manager_fadei_push.Add(counter_num, type_here);
						}
					}
				}
				/*else
				{
					if (_arr_block[i][j]._effect_zoom_object_max.isOverPercent(0.5f))
					{
						int counter_num = 0;
						int num = 0;
						for (int a = index_r_begin; a <= index_r_end; a++)
						{
							for (int b = index_c_begin; b <= index_c_end; b++)
							{
								if (game->_state_gameplay._master_game._arr_block[a][b]._state == BLOCK_WILL_SELECT)
								{
									game->_state_gameplay._master_game._arr_block[a][b]._state = BLOCK_TOUCH_DOWN;
									_effect_wave_circle.AddBoom(a, b, BOOM_POWER, BOOM_WEAK_PERCENT);
									counter_num += (game->_state_gameplay._master_game._x_combo_current + num);
									num += 1;
								}
							}
						}
						if (counter_num > 0)
						{
							game->_state_gameplay._hud_background._manager_fadei_push.Add(counter_num);
						}
					}
				}*/
			}
		}
	}
	if (flag_submit_score)
	{
		/*Caculate score hud*/
		game->_state_gameplay._hud_score.SubmitCache();
		/*End*/
	}
}

void MatrixDraw::UpdatePosMatrix()
{
	ColorBorn *game = (ColorBorn*)GAME()->_current_game;
	for (int i = 0; i < game->_state_gameplay._master_game._matrix_max_row_current; i++)
	{
		for (int j = 0; j < game->_state_gameplay._master_game._matrix_max_column_current; j++)
		{
			_arr_block[i][j].UpdatePos();
		}
	}
}

void MatrixDraw::RenderMatrix(float pos_x, float pos_y)
{
	_effect_type_clear_idle.Render();

	for (int i = 0; i < _matrix_max_row_current; i++)
	{
		for (int j = 0; j < _matrix_max_column_current; j++)
		{
			_arr_block[i][j].RenderBlockNormal(pos_x, pos_y);
		}
	}
	for (int i = 0; i < _matrix_max_row_current; i++)
	{
		for (int j = 0; j < _matrix_max_column_current; j++)
		{
			_arr_block[i][j].RenderBlockScaleIn(pos_x, pos_y);
		}
	}
	for (int i = 0; i < _matrix_max_row_current; i++)
	{
		for (int j = 0; j < _matrix_max_column_current; j++)
		{
			_arr_block[i][j].RenderBlockScaleOut(pos_x, pos_y);
		}
	}
	for (int i = 0; i < _matrix_max_row_current; i++)
	{
		for (int j = 0; j < _matrix_max_column_current; j++)
		{
			_arr_block[i][j].RenderBlockReborn(pos_x, pos_y);
		}
	}
}

void MatrixDraw::RenderBlockNormalCurrent(int index_r, int index_c, int opacity_input, float pos_x, float pos_y)
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
	draw_x = index_c * (game->_state_gameplay._master_game._matrix_block_width + (game->_state_gameplay._master_game._grap.width)) + new_x;
	draw_y = index_r * (game->_state_gameplay._master_game._matrix_block_height + (game->_state_gameplay._master_game._grap.height)) + new_y;

	draw_x += game->_state_gameplay._master_game._effect_wave_circle._matrix_pos_current[index_r][index_c].X;
	draw_y += game->_state_gameplay._master_game._effect_wave_circle._matrix_pos_current[index_r][index_c].Y;

	draw_x += game->_state_gameplay._scroll_page_x;
	draw_y += game->_state_gameplay._scroll_page_y;

	//G()->SetColor(0xFFFFFFFF);
	//G()->FillRect(draw_x, draw_y, game->_state_gameplay._master_game._matrix_block_width, game->_state_gameplay._master_game._matrix_block_height);

	int opacity = opacity_input;
	float radius = (game->_state_gameplay._master_game._matrix_block_width / 2) + game->_state_gameplay._master_game._effect_idle_zoom.value_current;
	float scale_block = (game->_state_gameplay._master_game._matrix_block_width + game->_state_gameplay._master_game._effect_idle_zoom.value_current * 2) / (GET_SPRITE(SPRITEID_OBJECT_01_N_COLOR)->GetFrameWidth(0) *1.0f);
	if (_arr_block[index_r][index_c]._type != TYPE_EMPTY)
	{
		G()->SetOpacity(opacity);
		G()->SetColor(0xFF0A3351);
		G()->FillCircle(draw_x + game->_state_gameplay._master_game._matrix_block_width / 2, draw_y + game->_state_gameplay._master_game._matrix_block_width / 2, radius, 5, true);
		G()->SetOpacity(100);

		if (_arr_block[index_r][index_c]._type == TYPE_CLEAR)
		{
			if (_arr_block[index_r][index_c]._state == BLOCK_NORMAL || _arr_block[index_r][index_c]._state == BLOCK_WILL_SELECT || _arr_block[index_r][index_c]._state == BLOCK_WILL_INVI || _arr_block[index_r][index_c]._state == BLOCK_TOUCH_DOWN)
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
			if (_arr_block[index_r][index_c]._state == BLOCK_NORMAL || _arr_block[index_r][index_c]._state == BLOCK_WILL_SELECT || _arr_block[index_r][index_c]._state == BLOCK_WILL_INVI || _arr_block[index_r][index_c]._state == BLOCK_TOUCH_DOWN)
			{
				/*G()->SetColor(_color);
				for (float i = radius - 3.0f; i <= radius; i+=0.5f)
				{
				G()->DrawCircle(draw_x + game->_state_gameplay._master_game._matrix_block_width / 2, draw_y + game->_state_gameplay._master_game._matrix_block_width / 2, i, 5);
				}*/
				G()->SetColorMask(_arr_block[index_r][index_c]._color);
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

bool MatrixDraw::UpdateTouchMatrix()
{
	ColorBorn *game = (ColorBorn*)GAME()->_current_game;
	bool ret = false;
	PinePoint pos_get;
	for (int i = 0; i < GAME()->_num_touches; i++)
	{
		if (TOUCHS(i)->_flag)
		{
			int touch_x = TOUCHS(i)->x;
			int touch_y = TOUCHS(i)->y;
			if (TOUCHS(i)->_state == TOUCH_DOWN)
			{
				if (_index_touch_matrix == -1 && _state_matrix == MATRIX_CAN_TOUCH)
				{
					if (_state_matrix == 1)
					{
						if (GetCurrentBlockChoose(touch_x, touch_y, pos_get) != -1)
						{
							_current_block_choose = GetCurrentBlockChoose(touch_x, touch_y, pos_get);
							_index_touch_matrix = TOUCHS(i)->_id;
							int index_row = pos_get.Y;
							int index_col = pos_get.X;
							_arr_block[index_row][index_col]._is_touch_state = 1;
							//_effect_wave_circle.Init(_matrix_max_row_current, _matrix_max_column_current, index_row, index_col);
						}
					}
				}

			}
			if (TOUCHS(i)->_state == TOUCH_DRAG)
			{
				if (TOUCHS(i)->_id == _index_touch_matrix)
				{
					int index_row = _current_block_choose / game->_state_gameplay._master_game._matrix_max_column_current;
					int index_col = _current_block_choose % game->_state_gameplay._master_game._matrix_max_column_current;
					if (GetCurrentBlockChoose(touch_x, touch_y, pos_get) == _current_block_choose)
					{
						_arr_block[index_row][index_col]._is_touch_state = 1;
					}
					else
					{
						_arr_block[index_row][index_col]._is_touch_state = 0;
						_index_touch_matrix = -1;
					}
				}
			}
			if (TOUCHS(i)->_state == TOUCH_UP)
			{
				if (TOUCHS(i)->_id == _index_touch_matrix)
				{
					_index_touch_matrix = -1;
					if (GetCurrentBlockChoose(touch_x, touch_y, pos_get) == _current_block_choose)
					{
						IncreaseIndexComboSound();
						int index_row = pos_get.Y;
						int index_col = pos_get.X;
						_arr_block[index_row][index_col]._state = BLOCK_TOUCH_DOWN;
						_arr_block[index_row][index_col]._effect_zoom_object_max.Default();
						printf("\tSelect[%d][%d]", index_row, index_col);
						_state_matrix = MATRIX_CLEAR_TOUCH;
						_arr_block[index_row][index_col]._is_touch_state = 0;
						_x_combo_current = 1;

						_effect_wave_circle.AddBoom(index_row, index_col, BOOM_POWER, BOOM_WEAK_PERCENT);
						if (_arr_block[index_row][index_col]._type == TYPE_CLEAR)
						{
							int num = 1 + _arr_block[index_row][index_col].GetNumbeBlockEat(false);
							game->_state_gameplay._hud_background._manager_fadei_push.Add(num, false);
							_type_current_check = TYPE_CLEAR;
						}
						else
						{
							int num = 1 + _arr_block[index_row][index_col].GetNumbeBlockEat(false);
							game->_state_gameplay._hud_background._manager_fadei_push.Add(num, false);
							_type_current_check = _arr_block[index_row][index_col]._type;
						}
						game->_state_gameplay._hud_background.StartCounterTime();
						_is_big_boom_ready = false;
					}
				}
			}
		}
	}
	if (_index_touch_matrix != -1)
	{
		return true;
	}
	else
		return false;
}

bool MatrixDraw::CheckTouchInBlock(int x, int y)
{
	ColorBorn *game = (ColorBorn*)GAME()->_current_game;
	bool ret = false;
	int x_compare = x;
	int y_compare = y;
	for (int i = 0; i < game->_state_gameplay._master_game._matrix_max_row_current; i++)
	{
		for (int j = 0; j < game->_state_gameplay._master_game._matrix_max_column_current; j++)
		{
			int x_check = _arr_block[i][j]._point_begin_pixel.X;
			int y_check = _arr_block[i][j]._point_begin_pixel.Y;
			if (CHECK_POINT_IN_RECT(x_compare, y_compare, x_check, y_check, game->_state_gameplay._master_game._matrix_block_width, game->_state_gameplay._master_game._matrix_block_height))
			{
				_arr_block[i][j]._state = BLOCK_SELECT;
				return true;
				break;
			}
		}
	}
	return ret;
}

int MatrixDraw::GetCurrentBlockChoose(int x, int y, PinePoint & pos_ret)
{
	ColorBorn *game = (ColorBorn*)GAME()->_current_game;
	pos_ret.X = -1;
	pos_ret.Y = -1;
	int ret = -1;
	int x_compare = x;
	int y_compare = y;
	for (int i = 0; i < game->_state_gameplay._master_game._matrix_max_row_current; i++)
	{
		for (int j = 0; j < game->_state_gameplay._master_game._matrix_max_column_current; j++)
		{
			int x_check = _arr_block[i][j]._point_begin_pixel.X;
			int y_check = _arr_block[i][j]._point_begin_pixel.Y;
			if (CHECK_POINT_IN_RECT(x_compare, y_compare, x_check, y_check, game->_state_gameplay._master_game._matrix_block_width, game->_state_gameplay._master_game._matrix_block_height))
			{
				pos_ret.X = j;
				pos_ret.Y = i;
				return i * game->_state_gameplay._master_game._matrix_max_column_current + j;
				break;
			}
		}
	}
	return -1;
}

int MatrixDraw::GetCurrentBlockWidth()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;

	SetValueGrap();
#if defined (ANDROID_OS)
	int ret = (game->_screen_width - (GRAP_GRID * 2 * GAME()->_game_context.ScaleX + (_matrix_max_column_current - 1) * _grap.width)) / _matrix_max_column_current;
#else
	int ret = (game->_screen_width - (GRAP_GRID * 2 + (_matrix_max_column_current - 1) * _grap.width)) / _matrix_max_column_current;
	if (game->_device_current == DEVICE_CURRENT_IPAD)
	{
		ret = (game->_screen_width - (150.0f * 2 + (_matrix_max_column_current - 1) * _grap.width)) / _matrix_max_column_current;
	}
	if (game->_device_current == DEVICE_CURRENT_I4)
	{
		ret = (game->_screen_width - (100.0f * 2 + (_matrix_max_column_current - 1) * _grap.width)) / _matrix_max_column_current;
	}
#endif
	return ret;
}

int MatrixDraw::GetCurrentBlockHeight()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;

	SetValueGrap();
#if defined (ANDROID_OS)
	int ret = (game->_screen_width - (GRAP_GRID * 2 * GAME()->_game_context.ScaleY + (_matrix_max_column_current - 1) * _grap.width)) / _matrix_max_column_current;
#else
	int ret = (game->_screen_width - (GRAP_GRID * 2 + (_matrix_max_column_current - 1) * _grap.width)) / _matrix_max_column_current;
	if (game->_device_current == DEVICE_CURRENT_IPAD)
	{
		ret = (game->_screen_width - (150.0f * 2 + (_matrix_max_column_current - 1) * _grap.width)) / _matrix_max_column_current;
	}
	if (game->_device_current == DEVICE_CURRENT_I4)
	{
		ret = (game->_screen_width - (100.0f * 2 + (_matrix_max_column_current - 1) * _grap.width)) / _matrix_max_column_current;
	}
#endif
	return ret;
}

void MatrixDraw::SetValueGrap()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	float scale_grap = 0.375f * (_matrix_max_row_current - 2);
	int get_value = (int)(GRAP_TILE_WIDTH - scale_grap * GRAP_TILE_WIDTH);
	get_value = GRAP_TILE_WIDTH;
	_grap.width = get_value;
	_grap.height = get_value;
}

COLOR MatrixDraw::GetCurrentColor(int type)
{
	COLOR ret = 0xFFFFFFFF;
	if (type == 1)
	{
		ret = TYPE_ONE_COLOR;
	}
	else if (type == 2)
	{
		ret = TYPE_TWO_COLOR;
	}
	else if (type == 3)
	{
		ret = TYPE_THREE_COLOR;
	}
	else if (type == 4)
	{
		ret = TYPE_FOUR_COLOR;
	}
	else if (type == 5)
	{
		ret = TYPE_FIVE_COLOR;
	}
	else if (type == 6)
	{
		ret = TYPE_SIX_COLOR;
	}
	else if (type == 7)
	{
		ret = TYPE_SEVEN_COLOR;
	}
	else if (type == 8)
	{
		ret = TYPE_EIGHT_COLOR;
	}
	else if (type == 9)
	{
		ret = TYPE_NINE_COLOR;
	}
	else if (type == 10)
	{
		ret = TYPE_TEN_COLOR;
	}
	else if (type == 11)
	{
		ret = TYPE_ELEVEN_COLOR;
	}
	else if (type >= 12)
	{
		ret = TYPE_TWELVE_COLOR;
	}
	return ret;
}

int MatrixDraw::GetTotalBlockLikeTypeAndState(int state, int type)
{
	int ret = 0;
	for (int i = 0; i < _matrix_max_row_current; i++)
	{
		for (int j = 0; j < _matrix_max_column_current; j++)
		{
			if (_arr_block[i][j]._state == state && _arr_block[i][j]._type == type)
			{
				ret++;
			}
		}
	}
	return ret;
}

void MatrixDraw::PlaySoundCombo(bool upgrade_sound)
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	if (!game->_state_gameplay._user._is_sound)
	{
		return;
	}
	if (upgrade_sound)
	{
		_sound_combo_index_current += 1;
		if (_sound_combo_index_current > 6)
		{
			_sound_combo_index_current = 1;
		}
	}

	switch (_sound_combo_index_current)
	{
	case 1:
		GAME()->_device.PlayQueueSFX(SFX_SCORE_01);
		//GAME()->PlaySFX(SFX_SCORE_01);
		break;
	case 2:
		GAME()->_device.PlayQueueSFX(SFX_SCORE_02);
		//GAME()->PlaySFX(SFX_SCORE_02);
		break;
	case 3:
		GAME()->_device.PlayQueueSFX(SFX_SCORE_03);
		//GAME()->PlaySFX(SFX_SCORE_03);
		break;
	case 4:
		GAME()->_device.PlayQueueSFX(SFX_SCORE_04);
		//GAME()->PlaySFX(SFX_SCORE_04);
		break;
	case 5:
		GAME()->_device.PlayQueueSFX(SFX_SCORE_05);
		//GAME()->PlaySFX(SFX_SCORE_05);
		break;
	case 6:
		GAME()->_device.PlayQueueSFX(SFX_SCORE_06);
		//GAME()->PlaySFX(SFX_SCORE_06);
		break;
	default:
		if (_sound_combo_index_current > 6)
		{
			GAME()->_device.PlayQueueSFX(SFX_SCORE_06);
			//GAME()->PlaySFX(SFX_SCORE_06);
		}
		break;
	}
	if (upgrade_sound)
	{
		_sound_combo_index_current += 1;
		if (_sound_combo_index_current > 6)
		{
			_sound_combo_index_current = 1;
		}
	}
}

void MatrixDraw::IncreaseIndexComboSound()
{
	_sound_combo_index_current += 1;
	if (_sound_combo_index_current > 6)
	{
		_sound_combo_index_current = 1;
	}
}

void MatrixDraw::EffectIdleZoom::Init(float current, float target)
{
	accleration_function.Defalt();
	value_current = current;
	value_target = target;
	state = 0;
	time_wait = CMath::RANDOM(1, 2) * 2 * 60;
}

void MatrixDraw::EffectIdleZoom::Update()
{
	//0.5		0.5
	//1.1	    0.9

	//1.1
	//0.6			0.4

	//0.6		0.4
	//1.1
	float percent = 1.0f - value_current / value_target;
	//printf("\nspeed: %f, percent %f", accleration_function.speed, percent);

	if (state == 0)
	{
		time_wait--;
		if (time_wait <= 0)
		{
			state = 1;
		}
	}

	if (state == 1)
	{
		accleration_function.UpdateAcceleration(value_current, value_target, percent, true, 1.05f, 0.932f, 0.01f, 0.01f);
		percent = 1.0f - value_current / value_target;
		accleration_function.UpdateAccelerationEnd(value_current, value_target, percent, true);
		if (accleration_function.isFinish())
		{
			state = 2;
		}
		//printf("\nvalue_current: %f", value_current);
	}
	if (state == 2)
	{
		accleration_function.UpdateAcceleration(value_current, 0.0f, percent, false, 1.05f, 0.932f, 0.01f, 0.01f);
		percent = 1.0f - value_current / value_target;
		accleration_function.UpdateAccelerationEnd(value_current, 0.0f, percent, false);
		if (accleration_function.isFinish())
		{
			state = 0;
			time_wait = CMath::RANDOM(1, 2) * 2 * 60;
		}
		//printf("\nvalue_current: %f", value_current);
	}
	//printf("\nvalue_current: %f", value_current);
}

void MatrixDraw::EffectFadeInFadeOutGrid::Default()
{
	_state = 0;
}

void MatrixDraw::EffectFadeInFadeOutGrid::Init(bool fade_in, float begin_value)
{
	if (fade_in)
	{
		_fade_in = true;
		_percent = 0.0f;
	}
	else
	{
		_fade_in = false;
		_percent = 1.0f;
	}
	_opacity_begin = begin_value;
	_speed = 0.02f;
	_state = 1;
}

void MatrixDraw::EffectFadeInFadeOutGrid::Update()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	if (_state == 1)
	{
		if (_fade_in)
		{
			_percent += _speed;
			if (_percent > 1.0f)
			{
				_percent = 1.0f;
				_state = 2;
			}
		}
		else
		{
			_percent -= _speed;
			if (_percent < 0.0f)
			{
				_percent = 0.0f;
				_state = 2;
			}
		}
	}
}

bool MatrixDraw::EffectFadeInFadeOutGrid::isFinish()
{
	if (_state == 2 || _state == 0)
	{
		return true;
	}
	else
		return false;
}

void MatrixDraw::EffectFadeInFadeOutGrid::SetOutValue(float & opacity_out)
{
	if (_state == 1)
	{
		if (_fade_in)
		{
			opacity_out = _percent *100.0f;
		}
		else
		{
			opacity_out = _percent *_opacity_begin;
		}
	}
	if (_state == 2)
	{
		if (_fade_in)
		{
			opacity_out = 100.0f;
		}
		else
		{
			opacity_out = 0.0f;
		}
	}
}

#include "pch.h"
#include "../../../GameCore/CGame.h"

void GPHudTutorial::Init()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	_index_touch = -1;
	game->_state_gameplay._hud_ingame._title_scroll_y = 140.0f;
	_point_begin.X = game->_point_o.X + game->_screen_width / 2;
	_point_begin.Y = game->_point_right_bottom.Y - 98.0f;
	_point_draw = _point_begin;
	_opacity_all = 0.0f;
	_state = 0;
	_effect_opacity_hight_light_percent = 0.0f;
	_effect_opacity_hight_light_speed = 0.01f;
	_effect_opacity_hight_light_accel.Defalt();
	_effect_opacity_hight_light_state = 0;

	_text_one_percent = 0.0f;
	_text_two_percent = 1.0f;
	_text_speed_scroll = 0.025f;

	_index_column_choose = CMath::RANDOM(0, 6);
	_flag_new_grid = false;
	_opacity_new_grid = 0.0f;
}

void GPHudTutorial::Update()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	_opacity_all += 5.0f;
	if (_opacity_all > 100.0f)
	{
		_opacity_all = 100.0f;
	}
	if (_opacity_all == 100.0f)
	{
		UpdateTouch();
	}
	if (_state == 0 || _state == 1 || _state == 2 || _state == 3)
	{
		if (_effect_opacity_hight_light_state == 0)
		{
			_effect_opacity_hight_light_accel.UpdateAcceleration(_effect_opacity_hight_light_percent, 1.0f, (1.0f - _effect_opacity_hight_light_percent), true, 1.1f, 0.85f, 0.01f, 0.01f);
			_effect_opacity_hight_light_accel.UpdateAccelerationEnd(_effect_opacity_hight_light_percent, 1.0f, (1.0f - _effect_opacity_hight_light_percent), true);
			if (_effect_opacity_hight_light_accel.isFinish())
			{
				_effect_opacity_hight_light_state = 1;
				_effect_opacity_hight_light_accel.Defalt();
			}
		}
		else if (_effect_opacity_hight_light_state == 1)
		{
			_effect_opacity_hight_light_percent -= _effect_opacity_hight_light_speed;
			_effect_opacity_hight_light_speed *= 1.05f;
			if (_effect_opacity_hight_light_percent < 0.0f)
			{
				_effect_opacity_hight_light_percent = 0.0f;
				_effect_opacity_hight_light_state = 0;
				_effect_opacity_hight_light_speed = 0.01f;
			}
		}
		else if (_effect_opacity_hight_light_state == 2)
		{
			_effect_opacity_hight_light_percent -= _effect_opacity_hight_light_speed;
			_effect_opacity_hight_light_speed *= 1.05f;
			if (_effect_opacity_hight_light_percent < 0.0f)
			{
				_effect_opacity_hight_light_percent = 0.0f;
				_effect_opacity_hight_light_speed = 0.01f;
			}
		}
	}

	if (_state != 2 && _state != 4 && _state != 6 && _state != 8 && _state != 10 && _state != 12 && _state != 14 && _state != 16 && _state != 18 && _state < 20 && _state > 0)
	{
		_text_one_percent += _text_speed_scroll;
		if (_text_one_percent >= 1.0f)
		{
			_text_one_percent = 1.0f;
		}

		_text_two_percent -= _text_speed_scroll;
		if (_text_two_percent < 0.0f)
		{
			_text_two_percent = 0.0f;
		}

		if (_state == 9 && _flag_new_grid)
		{
			game->_state_gameplay._master_game._opacity_grid = (_text_two_percent - 0.5f) / 0.5f * 100.0f;
			if (game->_state_gameplay._master_game._opacity_grid < 0.0f)
			{
				game->_state_gameplay._master_game._opacity_grid = 0.0f;
				game->_state_gameplay._master_game.InitMatrixForTutorial();
				_flag_new_grid = false;
				printf("\n \n flag_new_grid_flase \n \n");
			}
		}
		if (_state == 9 && !_flag_new_grid)
		{
			game->_state_gameplay._master_game._opacity_grid = (0.5f - _text_two_percent) / 0.5f * 100.0f;
			if (game->_state_gameplay._master_game._opacity_grid > 100.0f)
			{
				game->_state_gameplay._master_game._opacity_grid = 100.0f;
			}
			_opacity_new_grid = game->_state_gameplay._master_game._opacity_grid;
		}

		if (_state == 15 && _flag_new_grid)
		{
			game->_state_gameplay._master_game._opacity_grid = (_text_two_percent - 0.5f) / 0.5f * 100.0f;
			if (game->_state_gameplay._master_game._opacity_grid < 0.0f)
			{
				game->_state_gameplay._master_game._opacity_grid = 0.0f;
				game->_state_gameplay._master_game.InitMatrixForTutorialClear();
				_flag_new_grid = false;
				printf("\n \n flag_new_grid_flase \n \n");
			}
		}
		if (_state == 15 && !_flag_new_grid)
		{
			game->_state_gameplay._master_game._opacity_grid = (0.5f - _text_two_percent) / 0.5f * 100.0f;
			if (game->_state_gameplay._master_game._opacity_grid > 100.0f)
			{
				game->_state_gameplay._master_game._opacity_grid = 100.0f;
			}
			_opacity_new_grid = game->_state_gameplay._master_game._opacity_grid;
		}

		if (_state == 11)
		{
			_opacity_new_grid = _text_two_percent * 100.0f;
		}
		if (_state == 17)
		{
			_opacity_new_grid = _text_two_percent * 100.0f;
		}


		if (_text_one_percent == 1.0f && _text_two_percent == 0.0f)
		{
			_state++;
			_text_one_percent = 0.0f;
			_text_two_percent = 1.0f;
		}
	}
	if (_state == 19)
	{
		_text_one_percent += _text_speed_scroll;
		if (_text_one_percent >= 1.0f)
		{
			_text_one_percent = 1.0f;
		}
		game->_state_gameplay._hud_ingame._title_scroll_y = 140.0f * (1.0f - _text_one_percent);
		if (_text_one_percent == 1.0f)
		{
			_state++;
			_text_one_percent = 0.0f;
			_text_two_percent = 1.0f;
		}
	}
	if (_state == 20)
	{
		game->_state_setting_credit._hud_setting_button._flag_reset_tutorial = false;
		game->_state_gameplay._gameplay_state = 1;
		game->_state_gameplay._user._finish_tut = true;
		game->_state_gameplay._user.DataSave();
		game->_state_gameplay._hud_background._state = 0;
#ifdef MAC_OS
         //
		if (!game->_state_gameplay._user._no_ads)
		{
			//PineAdBox::ShowAdmobBanner();
		}
#endif // MAC_OS
    }
   // printf("\nState: %d", _state);
}

void GPHudTutorial::Render()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	if (_state >= 9 && _state <= 11 || _state >= 15 && _state <= 17)
	{
		float opacity_over = (_opacity_new_grid / 100.0f) * 60.0f;
		G()->SetOpacity(opacity_over);
		G()->SetColorMask(0xFF000000);
#if defined (ANDROID_OS)
		G()->SetScale(GAME()->_game_context.ScaleOutX, GAME()->_game_context.ScaleOutY, game->_point_o.X, game->_point_right_bottom.Y);
		GET_SPRITE(SPRITEID_BG_INGAME_N_COLOR)->DrawFrame(G(), 0, game->_point_o.X, game->_point_right_bottom.Y);
		G()->ClearScale();
#else
		if (game->_device_current == DEVICE_CURRENT_IPAD || game->_device_current == DEVICE_CURRENT_I4)
		{
			CMatrix4x4Util matrix_port;
			matrix_port.reNew();
			matrix_port.DoScale(GAME()->_game_context.ScaleOutX, GAME()->_game_context.ScaleOutY, game->_point_o.X, game->_point_right_bottom.Y);
			G()->SetTransform(matrix_port.toPineTranform());
			GET_SPRITE(SPRITEID_BG_INGAME_N_COLOR)->DrawFrame(G(), 0, game->_point_o.X, game->_point_right_bottom.Y);
			G()->ClearTransform();
		}
		else
		{
			GET_SPRITE(SPRITEID_BG_INGAME_N_COLOR)->DrawFrame(G(), 0, game->_point_o.X, game->_point_right_bottom.Y);
		}
#endif
		G()->ClearColorMask();
		G()->SetOpacity(100);
	}

	CMatrix4x4Util matrix_normal;
	float draw_x = 0.0f;
	float draw_y = 0.0f;

	float opacity = _effect_opacity_hight_light_percent * _opacity_all;
	G()->SetOpacity((int)opacity);
	/*Effect Text One*/
	draw_x = game->_point_o.X;
	draw_y = game->_point_o.Y;
#if defined (ANDROID_OS)
	G()->SetScale(GAME()->_game_context.ScaleOutX, GAME()->_game_context.ScaleOutY, draw_x, draw_y);
	GET_SPRITE(SPRITEID_BG_INGAME_N_COLOR)->DrawFrame(G(), 4, draw_x, draw_y);
	G()->ClearScale();
#else
	if (game->_device_current == DEVICE_CURRENT_IPAD || game->_device_current == DEVICE_CURRENT_I4)
	{
		CMatrix4x4Util matrix_port;
		matrix_port.reNew();
		matrix_port.DoScale(GAME()->_game_context.ScaleOutX, GAME()->_game_context.ScaleOutY, draw_x, draw_y);
		G()->SetTransform(matrix_port.toPineTranform());
		GET_SPRITE(SPRITEID_BG_INGAME_N_COLOR)->DrawFrame(G(), 4, draw_x, draw_y);
		G()->ClearTransform();
	}
	else
	{
		GET_SPRITE(SPRITEID_BG_INGAME_N_COLOR)->DrawFrame(G(), 4, draw_x, draw_y);
	}
#endif
	/*End*/
	G()->SetOpacity(100);

	G()->SetOpacity(_opacity_all);
	if (_state == 0)
	{
		float opacity = _opacity_all;
		float scroll_y = 0.0f;
		G()->SetOpacity((int)opacity);
		draw_x = _point_draw.X;
		draw_y = _point_draw.Y + scroll_y;
#if defined (ANDROID_OS)
		if (GAME()->_game_context.ScaleX < 0.8f || GAME()->_game_context.ScaleY < 0.8f)
		{
			GET_SPRITE(SPRITEID_HUD_TUT_I4)->DrawFrame(G(), 0, draw_x, draw_y);
		}
		else
		{
			G()->SetScale(0.5f, 0.5f, draw_x, draw_y);
			GET_SPRITE(SPRITEID_HUD_TUT)->DrawFrame(G(), 0, draw_x, draw_y);
			G()->ClearScale();
		}	
#else
		if (game->_device_current == DEVICE_CURRENT_I4)
		{
			GET_SPRITE(SPRITEID_HUD_TUT_I4)->DrawFrame(G(), 0, draw_x, draw_y);
		}
		else
		{
			matrix_normal.reNew();
			matrix_normal.DoScale(0.5f, 0.5f, draw_x, draw_y);
			G()->SetTransform(matrix_normal.toPineTranform());
			GET_SPRITE(SPRITEID_HUD_TUT)->DrawFrame(G(), 0, draw_x, draw_y);
			G()->ClearTransform();
		}
#endif
		/*Tap to countinue*/
		draw_x = _point_draw.X;
		draw_y = game->_point_right_bottom.Y - 25.0f + scroll_y;
#if defined (ANDROID_OS)
		if (GAME()->_game_context.ScaleX < 0.8f || GAME()->_game_context.ScaleY < 0.8f)
		{
			GET_SPRITE(SPRITEID_HUD_TUT_I4)->DrawFrame(G(), 10, draw_x, draw_y);
		}
		else
		{
			G()->SetScale(0.5f, 0.5f, draw_x, draw_y);
			GET_SPRITE(SPRITEID_HUD_TUT)->DrawFrame(G(), 10, draw_x, draw_y);
			G()->ClearScale();
		}	
#else
		if (game->_device_current == DEVICE_CURRENT_I4)
		{
			GET_SPRITE(SPRITEID_HUD_TUT_I4)->DrawFrame(G(), 10, draw_x, draw_y);
		}
		else
		{
			matrix_normal.reNew();
			matrix_normal.DoScale(0.5f, 0.5f, draw_x, draw_y);
			G()->SetTransform(matrix_normal.toPineTranform());
			GET_SPRITE(SPRITEID_HUD_TUT)->DrawFrame(G(), 10, draw_x, draw_y);
			G()->ClearTransform();
		}
#endif
		G()->SetOpacity(100);
		/*End*/
	}


	int frame_draw = 0;
	switch (_state)
	{
	case 0:
	case 1:
		frame_draw = 0;
		break;
	case 3:
		frame_draw = 1;
		break;
	case 5:
		frame_draw = 2;
		break;
	case 7:
		frame_draw = 3;
		break;
	case 9:
		frame_draw = 4;
		break;
	case 11:
		frame_draw = 5;
		break;
	case 13:
		frame_draw = 6;
		break;
	case 15:
		frame_draw = 7;
		break;
	case 17:
		frame_draw = 8;
		break;
	case 19:
		frame_draw = 9;
		break;
	default:
		break;
	}
	if (_state != 2 && _state != 4 && _state != 6 && _state != 8 && _state != 10 && _state != 12 && _state != 14 && _state != 16 && _state != 18 && _state < 20 && _state > 0)
	{
		float opacity = _opacity_all - (_text_one_percent / 0.4f) * _opacity_all;
		float scroll_y = _text_one_percent * 170.0f;
		G()->SetOpacity((int)opacity);
		draw_x = _point_draw.X;
		draw_y = _point_draw.Y + scroll_y;
#if defined (ANDROID_OS)
		if (GAME()->_game_context.ScaleX < 0.8f || GAME()->_game_context.ScaleY < 0.8f)
		{
			GET_SPRITE(SPRITEID_HUD_TUT_I4)->DrawFrame(G(), frame_draw, draw_x, draw_y);
		}
		else
		{
			G()->SetScale(0.5f, 0.5f, draw_x, draw_y);
			GET_SPRITE(SPRITEID_HUD_TUT)->DrawFrame(G(), frame_draw, draw_x, draw_y);
			G()->ClearScale();
		}
#else
		if (game->_device_current == DEVICE_CURRENT_I4)
		{
			GET_SPRITE(SPRITEID_HUD_TUT_I4)->DrawFrame(G(), frame_draw, draw_x, draw_y);
		}
		else
		{
			matrix_normal.reNew();
			matrix_normal.DoScale(0.5f, 0.5f, draw_x, draw_y);
			G()->SetTransform(matrix_normal.toPineTranform());
			GET_SPRITE(SPRITEID_HUD_TUT)->DrawFrame(G(), frame_draw, draw_x, draw_y);
			G()->ClearTransform();
		}
#endif
		/*Tap to countinue*/
		draw_x = _point_draw.X;
		draw_y = game->_point_right_bottom.Y - 25.0f + scroll_y;
#if defined (ANDROID_OS)
		if (GAME()->_game_context.ScaleX < 0.8f || GAME()->_game_context.ScaleY < 0.8f)
		{
			GET_SPRITE(SPRITEID_HUD_TUT_I4)->DrawFrame(G(), 10, draw_x, draw_y);
		}
		else
		{
			G()->SetScale(0.5f, 0.5f, draw_x, draw_y);
			GET_SPRITE(SPRITEID_HUD_TUT)->DrawFrame(G(), 10, draw_x, draw_y);
			G()->ClearScale();
		}
#else
		if (game->_device_current == DEVICE_CURRENT_I4)
		{
			GET_SPRITE(SPRITEID_HUD_TUT_I4)->DrawFrame(G(), 10, draw_x, draw_y);
		}
		else
		{
			matrix_normal.reNew();
			matrix_normal.DoScale(0.5f, 0.5f, draw_x, draw_y);
			G()->SetTransform(matrix_normal.toPineTranform());
			GET_SPRITE(SPRITEID_HUD_TUT)->DrawFrame(G(), 10, draw_x, draw_y);
			G()->ClearTransform();
		}
#endif
		G()->SetOpacity(100);
		/*End*/

		if (_state == 1 || _state == 3 || _state == 5 || _state == 7 || _state == 9 || _state == 11 || _state == 13 || _state == 15 || _state == 17 || _state == 19)
		{
			float opacity = _opacity_all - (_text_two_percent / 0.4f) * _opacity_all;
			float scroll_y = _text_two_percent * 170.0f;
			G()->SetOpacity((int)opacity);
			draw_x = _point_draw.X;
			draw_y = _point_draw.Y + scroll_y;
#if defined (ANDROID_OS)
			if (GAME()->_game_context.ScaleX < 0.8f || GAME()->_game_context.ScaleY < 0.8f)
			{
				GET_SPRITE(SPRITEID_HUD_TUT_I4)->DrawFrame(G(), frame_draw + 1, draw_x, draw_y);
			}
			else
			{
				G()->SetScale(0.5f, 0.5f, draw_x, draw_y);
				GET_SPRITE(SPRITEID_HUD_TUT)->DrawFrame(G(), frame_draw + 1, draw_x, draw_y);
				G()->ClearScale();
			}
#else
			if (game->_device_current == DEVICE_CURRENT_I4)
			{
				GET_SPRITE(SPRITEID_HUD_TUT_I4)->DrawFrame(G(), frame_draw + 1, draw_x, draw_y);
			}
			else
			{
				matrix_normal.reNew();
				matrix_normal.DoScale(0.5f, 0.5f, draw_x, draw_y);
				G()->SetTransform(matrix_normal.toPineTranform());
				GET_SPRITE(SPRITEID_HUD_TUT)->DrawFrame(G(), frame_draw + 1, draw_x, draw_y);
				G()->ClearTransform();
			}
#endif
			if (_state != 3 && _state != 9 && _state != 15)
			{
				/*Tap to countinue*/
				draw_x = _point_draw.X;
				draw_y = game->_point_right_bottom.Y - 25.0f + scroll_y;
#if defined (ANDROID_OS)
				if (GAME()->_game_context.ScaleX < 0.8f || GAME()->_game_context.ScaleY < 0.8f)
				{
					GET_SPRITE(SPRITEID_HUD_TUT_I4)->DrawFrame(G(), 10, draw_x, draw_y);
				}
				else
				{
					G()->SetScale(0.5f, 0.5f, draw_x, draw_y);
					GET_SPRITE(SPRITEID_HUD_TUT)->DrawFrame(G(), 10, draw_x, draw_y);
					G()->ClearScale();
				}
#else
				if (game->_device_current == DEVICE_CURRENT_I4)
				{
					GET_SPRITE(SPRITEID_HUD_TUT_I4)->DrawFrame(G(), 10, draw_x, draw_y);
				}
				else
				{
					matrix_normal.reNew();
					matrix_normal.DoScale(0.5f, 0.5f, draw_x, draw_y);
					G()->SetTransform(matrix_normal.toPineTranform());
					GET_SPRITE(SPRITEID_HUD_TUT)->DrawFrame(G(), 10, draw_x, draw_y);
					G()->ClearTransform();
				}
#endif
				G()->SetOpacity(100);
				/*End*/
			}
		}
	}
	frame_draw = 0;
	switch (_state)
	{
	case 2:
		frame_draw = 1;
		break;
	case 4:
		frame_draw = 2;
		break;
	case 6:
		frame_draw = 3;
		break;
	case 8:
		frame_draw = 4;
		break;
	case 10:
		frame_draw = 5;
		break;
	case 12:
		frame_draw = 6;
		break;
	case 14:
		frame_draw = 7;
		break;
	case 16:
		frame_draw = 8;
		break;
	case 18:
		frame_draw = 9;
		break;
	default:
		break;
	}
	if (_state == 2 || _state == 4 || _state == 6 || _state == 8 || _state == 10 || _state == 12 || _state == 14 || _state == 16 || _state == 18)
	{
		float opacity = _opacity_all;
		float scroll_y = 0.0f;
		G()->SetOpacity((int)opacity);
		draw_x = _point_draw.X;
		draw_y = _point_draw.Y + scroll_y;
#if defined (ANDROID_OS)
		if (GAME()->_game_context.ScaleX < 0.8f || GAME()->_game_context.ScaleY < 0.8f)
		{
			GET_SPRITE(SPRITEID_HUD_TUT_I4)->DrawFrame(G(), frame_draw, draw_x, draw_y);
		}
		else
		{
			G()->SetScale(0.5f, 0.5f, draw_x, draw_y);
			GET_SPRITE(SPRITEID_HUD_TUT)->DrawFrame(G(), frame_draw, draw_x, draw_y);
			G()->ClearScale();
		}
#else
		if (game->_device_current == DEVICE_CURRENT_I4)
		{
			GET_SPRITE(SPRITEID_HUD_TUT_I4)->DrawFrame(G(), frame_draw, draw_x, draw_y);
		}
		else
		{
			matrix_normal.reNew();
			matrix_normal.DoScale(0.5f, 0.5f, draw_x, draw_y);
			G()->SetTransform(matrix_normal.toPineTranform());
			GET_SPRITE(SPRITEID_HUD_TUT)->DrawFrame(G(), frame_draw, draw_x, draw_y);
			G()->ClearTransform();
		}
#endif
		if (_state != 4 && _state != 10 && _state != 16)
		{
			/*Tap to countinue*/
			draw_x = _point_draw.X;
			draw_y = game->_point_right_bottom.Y - 25.0f + scroll_y;
#if defined (ANDROID_OS)
			if (GAME()->_game_context.ScaleX < 0.8f || GAME()->_game_context.ScaleY < 0.8f)
			{
				GET_SPRITE(SPRITEID_HUD_TUT_I4)->DrawFrame(G(), 10, draw_x, draw_y);
			}
			else
			{
				G()->SetScale(0.5f, 0.5f, draw_x, draw_y);
				GET_SPRITE(SPRITEID_HUD_TUT)->DrawFrame(G(), 10, draw_x, draw_y);
				G()->ClearScale();
			}
#else
			if (game->_device_current == DEVICE_CURRENT_I4)
			{
				GET_SPRITE(SPRITEID_HUD_TUT_I4)->DrawFrame(G(), 10, draw_x, draw_y);
			}
			else
			{
				matrix_normal.reNew();
				matrix_normal.DoScale(0.5f, 0.5f, draw_x, draw_y);
				G()->SetTransform(matrix_normal.toPineTranform());
				GET_SPRITE(SPRITEID_HUD_TUT)->DrawFrame(G(), 10, draw_x, draw_y);
				G()->ClearTransform();
			}
#endif
			G()->SetOpacity(100);
			/*End*/
		}
	}

	
	G()->SetOpacity(100);

	if (_state >= 9 && _state <= 11 && !_flag_new_grid)
	{
		game->_state_gameplay._master_game.RenderBlockNormalCurrent(6, _index_column_choose, (int)_opacity_new_grid);
	}

	if (_state >= 15 && _state <= 17 && !_flag_new_grid)
	{
		game->_state_gameplay._master_game.RenderBlockNormalCurrent(6, _index_column_choose, (int)_opacity_new_grid);
	}
}

void GPHudTutorial::UpdateTouch()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	for (int i = 0; i < GAME()->_num_touches; i++)
	{
		if (TOUCHS(i)->_flag)
		{
			if (TOUCHS(i)->_state == TOUCH_DOWN)
			{
				if (_index_touch == -1)
				{
					if (_state < 19 && _state != 4 && _state != 10 && _state != 16)
					{
						_index_touch = TOUCHS(i)->_id;
						if (_state == 0 || _state == 2 || _state == 4 || _state == 6 || _state == 8 || _state == 10 || _state == 12 || _state == 14 || _state == 16 || _state == 18)
						{
							_state += 1;
						}
					
						if (_state == 3)
						{
							_effect_opacity_hight_light_state = 2;
						}
						if (_state == 9)
						{
							_flag_new_grid = true;
							printf("\n \n flag_new_grid_true \n \n");
						}
						if (_state == 15)
						{
							_flag_new_grid = true;
							printf("\n \n flag_new_grid_true \n \n");
						}
					}
				}
			}
			if (TOUCHS(i)->_state == TOUCH_DRAG)
			{
				if (TOUCHS(i)->_id == _index_touch)
				{
					
				}
			}
			if (TOUCHS(i)->_state == TOUCH_UP)
			{
				if (TOUCHS(i)->_id == _index_touch)
				{
					_index_touch = -1;
				}
			}
		}
	}
	if (_state == 4 && game->_state_gameplay._master_game._state_matrix == MATRIX_CAN_TOUCH)
	{
		game->_state_gameplay._master_game.UpdateTouchMatrix();
		if (game->_state_gameplay._master_game._state_matrix == MATRIX_CLEAR_TOUCH)
		{
			_state = 5;
		}
	}
	if (_state == 10 && game->_state_gameplay._master_game._state_matrix == MATRIX_CAN_TOUCH)
	{
		PinePoint pos_get;
		if (game->_state_gameplay._master_game._index_touch_matrix == -1)
		{
			for (int i = 0; i < GAME()->_num_touches; i++)
			{
				if (TOUCHS(i)->_flag)
				{
					int touch_x = TOUCHS(i)->x;
					int touch_y = TOUCHS(i)->y;
					if (TOUCHS(i)->_state == TOUCH_DOWN)
					{
						if (game->_state_gameplay._master_game._index_touch_matrix == -1 && game->_state_gameplay._master_game._state_matrix == MATRIX_CAN_TOUCH)
						{
							if (game->_state_gameplay._master_game._state_matrix == 1)
							{
								if (game->_state_gameplay._master_game.GetCurrentBlockChoose(touch_x, touch_y, pos_get) != -1)
								{
									int block_choose = game->_state_gameplay._master_game.GetCurrentBlockChoose(touch_x, touch_y, pos_get);
									if (block_choose == (_index_column_choose + 6 * 7))
									{
										game->_state_gameplay._master_game.UpdateTouchMatrix();
									}
								}
							}
						}
					}
				}
			}
		}
		if (game->_state_gameplay._master_game._index_touch_matrix != -1)
		{
			game->_state_gameplay._master_game.UpdateTouchMatrix();
		}
		if (game->_state_gameplay._master_game._state_matrix == MATRIX_CLEAR_TOUCH)
		{
			_state = 11;
		}
	}
	if (_state == 16 && game->_state_gameplay._master_game._state_matrix == MATRIX_CAN_TOUCH)
	{
		PinePoint pos_get;
		if (game->_state_gameplay._master_game._index_touch_matrix == -1)
		{
			for (int i = 0; i < GAME()->_num_touches; i++)
			{
				if (TOUCHS(i)->_flag)
				{
					int touch_x = TOUCHS(i)->x;
					int touch_y = TOUCHS(i)->y;
					if (TOUCHS(i)->_state == TOUCH_DOWN)
					{
						if (game->_state_gameplay._master_game._index_touch_matrix == -1 && game->_state_gameplay._master_game._state_matrix == MATRIX_CAN_TOUCH)
						{
							if (game->_state_gameplay._master_game._state_matrix == 1)
							{
								if (game->_state_gameplay._master_game.GetCurrentBlockChoose(touch_x, touch_y, pos_get) != -1)
								{
									int block_choose = game->_state_gameplay._master_game.GetCurrentBlockChoose(touch_x, touch_y, pos_get);
									if (block_choose == (_index_column_choose + 6 * 7))
									{
										game->_state_gameplay._master_game.UpdateTouchMatrix();
									}
								}
							}
						}
					}
				}
			}
		}
		if (game->_state_gameplay._master_game._index_touch_matrix != -1)
		{
			game->_state_gameplay._master_game.UpdateTouchMatrix();
		}
		if (game->_state_gameplay._master_game._state_matrix == MATRIX_CLEAR_TOUCH)
		{
			_state = 17;
		}
	}
}

bool GPHudTutorial::CheckFinishTut()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	bool ret = true;
	if (!game->_state_gameplay._user._finish_tut && !game->_state_setting_credit._hud_setting_button._flag_reset_tutorial)
	{
		ret = false;
	}
	if (game->_state_gameplay._user._finish_tut && game->_state_setting_credit._hud_setting_button._flag_reset_tutorial)
	{
		ret = false;
	}
	return ret;
}

#include "pch.h"
#include "../../../GameCore/CGame.h"

#define TIME_LIFE	(15 * 60.0f)

void GPHudBackGround::Init()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	_transform_color_bg.Default();
	_transform_color_radian.Default();
	_color_background_begin = 0xFF0A3351;
	_color_background_current = _color_background_begin;
	_color_background_end = _color_background_begin;

	_color_radian_begin = 0xFF04111D;
	_color_radian_current = _color_radian_begin;
	_color_radian_end = _color_radian_begin;
	_state = 1;

	_percent_current = 0.0f;
	_percent_target = 0.0f;

	_point_begin_fadei.X = game->_point_o.X;
	_point_begin_fadei.Y = game->_point_right_bottom.Y;
	_point_draw_fadei = _point_begin_fadei;

	_point_begin_time_symbol.X = game->_point_o.X;
	_point_begin_time_symbol.Y = game->_point_o.Y;
	_point_draw_time_symbol = _point_begin_time_symbol;

	_transform_color_bg.InitColorFollowPercent(_color_background_begin, 0xFF4B8B89);
	_transform_color_radian.InitColorFollowPercent(_color_radian_begin, 0xFF4B8B89);

	_manager_fadei_push.Default();
	_acceleration_revert.Defalt();
	_effect_hight_light_fade_time.Default();
	_speed_revert = 0.001f;
}

void GPHudBackGround::Update()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	if (game->_current_state != k_GS_PLAYGAME)
	{
		return;
	}
	_manager_fadei_push.Update();

	if (_state == 1)
	{
		if (game->_state_gameplay._hud_tutorial.CheckFinishTut())
		{
			if (!_flag_is_revert /*&& game->_state_gameplay._master_game._state_matrix == MATRIX_CAN_TOUCH*/)
			{
				_percent_current += (1.0f / TIME_LIFE);
				if (_percent_current > 1.0f)
				{
					_percent_current = 1.0f;
					_state = 2;
					/*game->_state_gameplay.InitGamePlay();*/
					game->_state_gameplay._gameplay_state = 3;
					game->_state_gameplay._master_game._effect_fade_in_fade_out_grid.Init(false, game->_state_gameplay._master_game._opacity_grid);
					game->_state_gameplay._hud_end_game.Init();
					game->_state_gameplay._hud_score.UpdateAndSubmitHightScore();
				}
			}
		}
	}
	if (_state == 2)
	{
		
	}
	if (_state == 3)
	{
		UpdateResetTimeBar();
	}
	if (_state == 4)
	{
		_percent_current -= 0.01f;
		if (_percent_current < 0.0f)
		{
			_percent_current = 0.0f;
			_state = 0;
		}
	}
	if (_state == 10)
	{
 		if (_percent_current > 0.1f)
		{
			_percent_current -= _speed_revert;
			_speed_revert *= 1.025f;
		}
		if (_percent_current <= 0.1f)
		{
			_percent_current -= _speed_revert;
			_speed_revert *= 0.86f;
			if (_speed_revert < 0.001f)
			{
				_speed_revert = 0.001f;
			}
		}
		if (_percent_current <= 0.0f)
		{
			_state = 1;
		}
		else
		{
			_manager_fadei_push.SetStateFade(1);
		}
	}

	float percent_color = 0.0f;
	if ((1.0f - _percent_current) >= 0.5f)
	{
		percent_color = 0.0f;
	}
	else
	{
		percent_color = (_percent_current - (1.0f - 0.5f)) / 0.5f;
	}
	if (percent_color >= 1.0f)
	{
		percent_color = 1.0f;
	}
	_transform_color_bg.UpdateFollowPercent(percent_color);
	_color_background_current = _transform_color_bg._draw_color;
	_transform_color_radian.UpdateFollowPercent(percent_color);
	_color_radian_current = _transform_color_radian._draw_color;


	if (!_transform_color_bg.isFinish())
	{
		_transform_color_bg.Update();
		_color_background_current = _transform_color_bg._draw_color;
		if (_transform_color_bg.isFinish())
		{
			_color_background_current = _color_background_end;
		}
	}
	if (!_transform_color_radian.isFinish())
	{
		_transform_color_radian.Update();
		_color_radian_current = _transform_color_radian._draw_color;
		if (_transform_color_radian.isFinish())
		{
			_color_radian_current = _color_radian_end;
		}
	}
	_effect_hight_light_fade_time.Update();
}

bool GPHudBackGround::RevertTime(float percent)
{
	bool ret = false;
	_percent_current = 1.0f - percent;
	if (_percent_current <= 0.0f)
	{
		ret = true;
		_percent_current = 0.0f;
	}
	return ret;
}

void GPHudBackGround::FinishRevert()
{
	_flag_is_revert = false;
}

void GPHudBackGround::Render()
{
	ColorBorn *game = (ColorBorn*)GAME()->_current_game;
	//printf("\n_percent_current: %f", _percent_current);
	float draw_x = game->_point_o.X;
	float draw_y = game->_point_o.Y + game->_state_gameplay._scroll_page_y;
#if defined (ANDROID_OS)
	G()->SetScale(GAME()->_game_context.ScaleOutX, GAME()->_game_context.ScaleOutY, draw_x, draw_y);
	GET_SPRITE(SPRITEID_BG_INGAME)->DrawFrame(G(), 0, draw_x, draw_y);
	G()->ClearScale();
#else
	if (game->_device_current == DEVICE_CURRENT_IPAD || game->_device_current == DEVICE_CURRENT_I4)

	{
		CMatrix4x4Util matrix_port;
		matrix_port.reNew();
		matrix_port.DoScale(GAME()->_game_context.ScaleOutX, GAME()->_game_context.ScaleOutY, draw_x, draw_y);
		G()->SetTransform(matrix_port.toPineTranform());
		GET_SPRITE(SPRITEID_BG_INGAME)->DrawFrame(G(), 0, draw_x, draw_y);
		G()->ClearTransform();
	}
	else
	{
		GET_SPRITE(SPRITEID_BG_INGAME)->DrawFrame(G(), 0, draw_x, draw_y);
	}
#endif

	float distance_scroll_y = (1.0f - _percent_current) * _max_distance_can_scroll;
	draw_x = _point_draw_time_symbol.X;
	draw_y = _point_draw_time_symbol.Y - distance_scroll_y + game->_state_gameplay._scroll_page_y;
	G()->SetColorMask(0xFF4B8B89);
#if defined (ANDROID_OS)
	G()->SetScale(GAME()->_game_context.ScaleOutX, GAME()->_game_context.ScaleOutY, draw_x, draw_y);
	GET_SPRITE(SPRITEID_BG_INGAME_N_COLOR)->DrawFrame(G(), 1, draw_x, draw_y);
	G()->ClearScale();
#else
	if (game->_device_current == DEVICE_CURRENT_IPAD || game->_device_current == DEVICE_CURRENT_I4)

	{
		CMatrix4x4Util matrix_port;
		matrix_port.reNew();
		matrix_port.DoScale(GAME()->_game_context.ScaleOutX, GAME()->_game_context.ScaleOutY, draw_x, draw_y);
		G()->SetTransform(matrix_port.toPineTranform());
		GET_SPRITE(SPRITEID_BG_INGAME_N_COLOR)->DrawFrame(G(), 1, draw_x, draw_y);
		G()->ClearTransform();
	}
	else
	{
		GET_SPRITE(SPRITEID_BG_INGAME_N_COLOR)->DrawFrame(G(), 1, draw_x, draw_y);
	}
#endif
	G()->ClearColorMask();
#if defined (ANDROID_OS)
	G()->SetScale(GAME()->_game_context.ScaleOutX, GAME()->_game_context.ScaleOutY, draw_x, draw_y);
	GET_SPRITE(SPRITEID_BG_INGAME)->DrawFrame(G(), 3, draw_x, draw_y);
	G()->ClearScale();
#else
	if (game->_device_current == DEVICE_CURRENT_IPAD || game->_device_current == DEVICE_CURRENT_I4)

	{
		CMatrix4x4Util matrix_port;
		matrix_port.reNew();
		matrix_port.DoScale(GAME()->_game_context.ScaleOutX, GAME()->_game_context.ScaleOutY, draw_x, draw_y);
		G()->SetTransform(matrix_port.toPineTranform());
		GET_SPRITE(SPRITEID_BG_INGAME)->DrawFrame(G(), 3, draw_x, draw_y);
		G()->ClearTransform();
	}
	else
	{
		GET_SPRITE(SPRITEID_BG_INGAME)->DrawFrame(G(), 3, draw_x, draw_y);
	}
#endif
	
	_manager_fadei_push.Render();

	
	/*Radian time symbol*/
	draw_x = game->_point_o.X;
	draw_y = game->_point_o.Y + game->_state_gameplay._scroll_page_y;
#if defined (ANDROID_OS)
	G()->SetScale(GAME()->_game_context.ScaleOutX, GAME()->_game_context.ScaleOutY, draw_x, draw_y);
	GET_SPRITE(SPRITEID_BG_INGAME)->DrawFrame(G(), 1, draw_x, draw_y);
	G()->ClearScale();
#else
	if (game->_device_current == DEVICE_CURRENT_IPAD || game->_device_current == DEVICE_CURRENT_I4)
	{
		CMatrix4x4Util matrix_port;
		matrix_port.reNew();
		matrix_port.DoScale(GAME()->_game_context.ScaleOutX, GAME()->_game_context.ScaleOutY, draw_x, draw_y);
		G()->SetTransform(matrix_port.toPineTranform());
		GET_SPRITE(SPRITEID_BG_INGAME)->DrawFrame(G(), 1, draw_x, draw_y);
		G()->ClearTransform();
	}
	else
	{
		GET_SPRITE(SPRITEID_BG_INGAME)->DrawFrame(G(), 1, draw_x, draw_y);
	}
#endif
	/*End*/
	/*Draw hightlight*/
	_effect_hight_light_fade_time.Render();
	/*End*/








	draw_x = _point_draw_fadei.X;
	draw_y = _point_draw_fadei.Y + game->_state_gameplay._scroll_page_y;
	G()->SetColorMask(_color_background_current);
#if defined (ANDROID_OS)
	G()->SetScale(GAME()->_game_context.ScaleOutX, GAME()->_game_context.ScaleOutY, draw_x, draw_y);
	GET_SPRITE(SPRITEID_BG_INGAME_N_COLOR)->DrawFrame(G(), 0, draw_x, draw_y);
	G()->ClearScale();
#else
	if (game->_device_current == DEVICE_CURRENT_IPAD || game->_device_current == DEVICE_CURRENT_I4)

	{
		CMatrix4x4Util matrix_port;
		matrix_port.reNew();
		matrix_port.DoScale(GAME()->_game_context.ScaleOutX, GAME()->_game_context.ScaleOutY, draw_x, draw_y);
		G()->SetTransform(matrix_port.toPineTranform());
		GET_SPRITE(SPRITEID_BG_INGAME_N_COLOR)->DrawFrame(G(), 0, draw_x, draw_y);
		G()->ClearTransform();
	}
	else
	{
		GET_SPRITE(SPRITEID_BG_INGAME_N_COLOR)->DrawFrame(G(), 0, draw_x, draw_y);
	}
#endif
	G()->ClearColorMask();
	
	G()->SetColorMask(_color_radian_current);
#if defined (ANDROID_OS)
	G()->SetScale(GAME()->_game_context.ScaleOutX, GAME()->_game_context.ScaleOutY, draw_x, draw_y);
	GET_SPRITE(SPRITEID_BG_INGAME)->DrawFrame(G(), 2, draw_x, draw_y);
	G()->ClearScale();
#else
	if (game->_device_current == DEVICE_CURRENT_IPAD || game->_device_current == DEVICE_CURRENT_I4)

	{
		CMatrix4x4Util matrix_port;
		matrix_port.reNew();
		matrix_port.DoScale(GAME()->_game_context.ScaleOutX, GAME()->_game_context.ScaleOutY, draw_x, draw_y);
		G()->SetTransform(matrix_port.toPineTranform());
		GET_SPRITE(SPRITEID_BG_INGAME)->DrawFrame(G(), 2, draw_x, draw_y);
		G()->ClearTransform();
	}
	else
	{
		GET_SPRITE(SPRITEID_BG_INGAME)->DrawFrame(G(), 2, draw_x, draw_y);
	}
#endif
	G()->ClearColorMask();
	

	game->_state_gameplay._effect_fish_tank.RenderManager();

	game->_state_gameplay._effect_new_game.Render();
}

void GPHudBackGround::SetColorEnd(COLOR c_end)
{
	ColorBorn *game = (ColorBorn*)GAME()->_current_game;
	_color_background_end = c_end;
	_color_radian_end = c_end;

	_transform_color_bg.Init(_color_background_current, _color_background_end, 60);
	_transform_color_radian.Init(_color_radian_current, _color_radian_end, 60);
}

void GPHudBackGround::SetNewPercent(float percent)
{
	_percent_target = percent;
}

COLOR GPHudBackGround::GetColorNewFromBegin(short r_input, short g_input, short b_input, COLOR color_begin)
{
	COLOR ret;
	short a_byte, r_byte, g_byte, b_byte;
	a_byte = ((color_begin >> 24) & 0xFF);
	r_byte = ((color_begin >> 16) & 0xFF);
	g_byte = ((color_begin >> 8) & 0xFF);
	b_byte = (color_begin & 0xFF);

	r_byte += r_input;
	if (r_byte >= 255)
	{
		r_byte = 255;
	}
	if (r_byte <= 0)
	{
		r_byte = 0;
	}
	g_byte += g_input;
	if (g_byte >= 255)
	{
		g_byte = 255;
	}
	if (g_byte <= 0)
	{
		g_byte = 0;
	}
	b_byte += b_input;
	if (b_byte >= 255)
	{
		b_byte = 255;
	}
	if (b_byte <= 0)
	{
		b_byte = 0;
	}
	int a = (((char)a_byte) << 24) & 0xFF000000;
	int r = (((char)r_byte) << 16) & 0x00FF0000;
	int g = (((char)g_byte) << 8) & 0x0000FF00;
	int b = (((char)b_byte)) & 0x000000FF;
	ret = a | r | g | b;
	return ret;
}

void GPHudBackGround::UpdateResetTimeBar()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	if (!_acceleration_revert.isFinish())
	{
		_acceleration_revert.UpdateAcceleration(_percent_current, 0.0f, (1.0f - _percent_current), false, 1.05f, 0.925f, 0.001f, 0.001f);
		_acceleration_revert.UpdateAccelerationEnd(_percent_current, 0.0f, (1.0f - _percent_current), false);
		//_acceleration_revert.PrintfSpeed();
		if (_acceleration_revert.isFinish())
		{
			_state = 1;
		}
		else
		{
			_manager_fadei_push.SetStateFade(1);
		}
	}
	else
	{
		_state = 1;
	}
}

void GPHudBackGround::SetResetTimeBar(int type)
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	_acceleration_revert.Defalt();
	_acceleration_revert.UpdateAcceleration(_percent_current, 0.0f, (1.0f - _percent_current), false, 1.1f, 0.87f, 0.001f, 0.001f);
	if (type == 1)
	{
		_state = 4;
	}
	else if (type == 0)
	{
		_state = 3;
		game->_state_gameplay._master_game._effect_fade_in_fade_out_grid.Init(true, game->_state_gameplay._master_game._opacity_grid);
	}
	else if (type == -1)
	{
		_state = 10;
		game->_state_gameplay._master_game._effect_fade_in_fade_out_grid.Init(true, game->_state_gameplay._master_game._opacity_grid);
	}
}

void GPHudBackGround::StartCounterTime()
{
	if (_state == 0)
	{
		_state = 1;
	}
}

void GPHudBackGround::FadeiPush::Init(int pow, bool pow_clear)
{
	if (pow_clear)
	{
		printf("\npow: %d, pow_clear", pow);
	}
	else
	{
		printf("\npow: %d", pow);
	}
	ColorBorn *game = (ColorBorn*)GAME()->_current_game;
	state = 1;
	percent = 0.0f;
	point_begin = game->_state_gameplay._hud_background._point_begin_fadei;
	point_draw = point_begin;
	percent_speed_weak = 10.0f;


	float begin = 0.0015f *2.7;
	if (pow_clear)
	{
		begin = 0.03f;
	}
	/*switch (pow)
	{
	case 1:
		percent_speed_weak = 20.0f;
		power_add = begin;
		break;
	case 2:
		power_add = begin * 2;
		break;
	case 3:
		power_add = begin * 3;
		break;
	case 4:
		power_add = begin * 4;
		break;
	case 5:
		power_add = begin * 5;
		break;
	case 6:
		power_add = begin * 6;
		break;
	case 7:
		power_add = begin * 7;
		break;
	default:
		if (pow > 7)
		{
			power_add = begin * 15;
		}
		break;
	}*/
	power_add = begin * pow;
	printf("\n power_add: %f", power_add);

	speed = 0.02f / 4.0f;
	if (pow_clear)
	{
		speed = 0.01f;
	}
	counter_power_add = 0.0f;
	opacity_fadei = 30;

	_color_transform.Default();
	UpdateColorCurrent();
	//_color_transform.InitColorFollowPercent(color_current, )
}

void GPHudBackGround::FadeiPush::Render()
{
	ColorBorn *game = (ColorBorn*)GAME()->_current_game;
	if (state >= 1 && state < 4)
	{
		float draw_x = point_draw.X;
		float draw_y = point_draw.Y - (game->_state_gameplay._hud_background._max_distance_can_scroll) * percent + game->_state_gameplay._scroll_page_y;
		G()->SetColorMask(color_current);
		G()->SetOpacity(opacity_fadei);
#if defined (ANDROID_OS)
		G()->SetScale(GAME()->_game_context.ScaleOutX, GAME()->_game_context.ScaleOutY, draw_x, draw_y);
		GET_SPRITE(SPRITEID_BG_INGAME_N_COLOR)->DrawFrame(G(), 0, draw_x, draw_y);
		G()->ClearScale();
#else
		if (game->_device_current == DEVICE_CURRENT_IPAD || game->_device_current == DEVICE_CURRENT_I4)
		{
			CMatrix4x4Util matrix_port;
			matrix_port.reNew();
			matrix_port.DoScale(GAME()->_game_context.ScaleOutX, GAME()->_game_context.ScaleOutY, draw_x, draw_y);
			G()->SetTransform(matrix_port.toPineTranform());
			GET_SPRITE(SPRITEID_BG_INGAME_N_COLOR)->DrawFrame(G(), 0, draw_x, draw_y);
			G()->ClearTransform();
		}
		else
		{
			GET_SPRITE(SPRITEID_BG_INGAME_N_COLOR)->DrawFrame(G(), 0, draw_x, draw_y);
		}
#endif
		G()->SetOpacity(100);
		G()->ClearColorMask();
	}
}

void GPHudBackGround::FadeiPush::Update()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	if (state == 1)
	{
		percent += speed;
		if (percent > (1.0f - game->_state_gameplay._hud_background._percent_current))
		{
			percent = 1.0f - game->_state_gameplay._hud_background._percent_current;
			state = 2;
			game->_state_gameplay._hud_background._effect_hight_light_fade_time.SetAppeare();
		}
	}
	if (state == 2)
	{
		speed *= 0.8f;
		if (speed <= (0.02f / percent_speed_weak))
		{
			speed = (0.02f / percent_speed_weak);
		}
		//printf("\nspeed: %f", speed);
		counter_power_add += speed;
		percent += speed;
		if (game->_state_gameplay._hud_background.RevertTime(percent))
		{
			state = 3;
		}
		if (percent > 1.0f)
		{
			percent = 1.0f;
		}
		if (counter_power_add > power_add)
		{
			state = 3;
		}
		
	}
	if (state == 3)
	{
		opacity_fadei -= 5;
		if (opacity_fadei <= 0)
		{
			opacity_fadei = 0;
			state = 4;
		}
	}
}

void GPHudBackGround::FadeiPush::Default()
{
	state = 0;
}

bool GPHudBackGround::FadeiPush::isFinish()
{
	if (state == 4 || state == 0)
	{
		return true;
	}
	else
		return false;
}

void GPHudBackGround::FadeiPush::UpdateColorCurrent()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	color_current = game->_state_gameplay._hud_background.GetColorNewFromBegin(10, 10, 10, game->_state_gameplay._hud_background._color_background_current);
}

void GPHudBackGround::ManagerFadeiPush::Add(int pow, bool pow_clear)
{
	if (num_push_current == 0)
	{
		if (arr_fadei != nullptr)
		{
			SAFE_DEL_ARRAY(arr_fadei);
		}
		num_push_current = 1;
		arr_fadei = new FadeiPush[num_push_current];
		arr_fadei[0].Init(pow, pow_clear);
	}
	else if(num_push_current > 0)
	{
		int last_num = num_push_current;
		FadeiPush *arr_backup;
		arr_backup = new FadeiPush[last_num];
		for (int i = 0; i < last_num; i++)
		{
			arr_backup[i] = arr_fadei[i];
		}
		if (arr_fadei != nullptr)
		{
			SAFE_DEL_ARRAY(arr_fadei);
		}
		num_push_current += 1;
		arr_fadei = new FadeiPush[num_push_current];
		for (int i = 0; i < last_num; i++)
		{
			arr_fadei[i] = arr_backup[i];
		}
		arr_fadei[last_num].Init(pow, pow_clear);
	}	
}

void GPHudBackGround::ManagerFadeiPush::Delete(int index)
{
	if (num_push_current == 1)
	{
		num_push_current = 0;
		if (arr_fadei != nullptr)
		{
			SAFE_DEL_ARRAY(arr_fadei);
		}
	}
	else if (num_push_current > 1)
	{
		int new_num = num_push_current - 1;
		FadeiPush *arr_new;
		arr_new = new FadeiPush[new_num];
		int counter = 0;
		for (int i = 0; i < num_push_current; i++)
		{
			if (i == index)
			{

			}
			else
			{
				arr_new[counter] = arr_fadei[i];
				counter++;
			}
		}
		if (arr_fadei != nullptr)
		{
			SAFE_DEL_ARRAY(arr_fadei);
		}
		num_push_current = new_num;
		arr_fadei = new FadeiPush[num_push_current];
		for (int i = 0; i < num_push_current; i++)
		{
			arr_fadei[i] = arr_new[i];
		}
		if (arr_new != nullptr)
		{
			SAFE_DEL_ARRAY(arr_new);
		}
	}
}

void GPHudBackGround::ManagerFadeiPush::Update()
{
	ColorBorn *game = (ColorBorn*)GAME()->_current_game;
	if (num_push_current > 0)
	{
		//printf("\nnum_push_current: %d", num_push_current);
		int counter = 0;
		for (int i = 0; i < num_push_current; i++)
		{
			arr_fadei[i].Update();
			if (arr_fadei[i].isFinish())
			{
				Delete(i);
			}
			if (num_push_current > 0)
			{
				if (arr_fadei[i].state == 2 || arr_fadei[i].state == 3)
				{
					counter++;
				}
			}
		}
		if (counter > 0)
		{
			game->_state_gameplay._hud_background._flag_is_revert = true;
		}
		else
		{
			game->_state_gameplay._hud_background._flag_is_revert = false;
		}
	}
	else
	{
		game->_state_gameplay._hud_background.FinishRevert();
	}
}

void GPHudBackGround::ManagerFadeiPush::SetStateFade(int index_state)
{
	if (num_push_current > 0)
	{
		for (int i = 0; i < num_push_current; i++)
		{
			if (!arr_fadei[i].isFinish())
			{
				arr_fadei[i].state = index_state;
			}
		}
	}
}

void GPHudBackGround::ManagerFadeiPush::Render()
{
	if (num_push_current > 0)
	{
		for (int i = 0; i < num_push_current; i++)
		{
			arr_fadei[i].Render();
		}
	}
}

void GPHudBackGround::ManagerFadeiPush::Default()
{
	num_push_current = 0;
	if (arr_fadei != nullptr)
	{
		SAFE_DEL_ARRAY(arr_fadei);
	}
}

void GPHudBackGround::EffectHightLightFadeTime::Default()
{
	state = 2;
	percent = 0.0f;
	speed = 0.04f;
	flag_push = false;
}

void GPHudBackGround::EffectHightLightFadeTime::Update()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	if (state == 1)
	{
		percent += speed;
		if (percent > 1.0f)
		{
			percent = 1.0f;
			state = 2;
		}
	}
	if (state == 2)
	{
		if (flag_push)
		{
			state = 1;
			flag_push = false;
		}
		percent -= (speed / 2);
		if (percent < 0.0f)
		{
			percent = 0.0f;
		}
	}
}

void GPHudBackGround::EffectHightLightFadeTime::Render()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	float distance_scroll_y = (1.0f - game->_state_gameplay._hud_background._percent_current) * game->_state_gameplay._hud_background._max_distance_can_scroll;
	float draw_x = game->_state_gameplay._hud_background._point_draw_time_symbol.X;
	float draw_y = game->_state_gameplay._hud_background._point_draw_time_symbol.Y - distance_scroll_y + game->_state_gameplay._scroll_page_y;
	float opacity = percent * 100.0f;
	G()->SetOpacity((int)opacity);
#if defined (ANDROID_OS)
	G()->SetScale(GAME()->_game_context.ScaleOutX, GAME()->_game_context.ScaleOutY, draw_x, draw_y);
	GET_SPRITE(SPRITEID_BG_INGAME)->DrawFrame(G(), 4, draw_x, draw_y);
	G()->ClearScale();
#else
	if (game->_device_current == DEVICE_CURRENT_IPAD || game->_device_current == DEVICE_CURRENT_I4)
	{
		CMatrix4x4Util matrix_port;
		matrix_port.reNew();
		matrix_port.DoScale(GAME()->_game_context.ScaleOutX, GAME()->_game_context.ScaleOutY, draw_x, draw_y);
		G()->SetTransform(matrix_port.toPineTranform());
		GET_SPRITE(SPRITEID_BG_INGAME)->DrawFrame(G(), 4, draw_x, draw_y);
		G()->ClearTransform();
	}
	else
	{
		GET_SPRITE(SPRITEID_BG_INGAME)->DrawFrame(G(), 4, draw_x, draw_y);
	}
#endif
	G()->SetOpacity(100);
}

void GPHudBackGround::EffectHightLightFadeTime::SetAppeare()
{
	flag_push = true;
}

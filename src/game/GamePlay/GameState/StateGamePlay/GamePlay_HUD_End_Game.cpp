#include "pch.h"
#include "../../../GameCore/CGame.h"

#define TIME_DELAY_BEHIND			10

void GPHudEndGame::Init()
{
	ColorBorn *game = (ColorBorn*)GAME()->_current_game;
	_acceleration_scroll.Defalt();
	_acceleration_scroll_behind.Defalt();
	_state = 1;
	_point_begin.X = game->_point_o.X + game->_screen_width / 2;
	_point_begin.Y = game->_point_o.Y + 742.0f;

	_point_draw.X = _point_begin.X + game->_screen_width;
	_point_draw.Y = _point_begin.Y;

	_percent = 0.0f;
	_time_wait_check_show_popup = 60;
	_speed = 0.01f;

	_percent_behind = 0.0f;
	_speed_behind = 0.01f;
	_time_delay_behind = TIME_DELAY_BEHIND;

	_point_begin_behind = _point_begin;
	_point_draw_behind = _point_draw;
}

void GPHudEndGame::Update()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	if (_state == 1)
	{
		_percent = (_point_draw.X - _point_begin.X) / game->_screen_width;
		_acceleration_scroll.UpdateAcceleration(_point_draw.X, _point_begin.X, 1.0f - _percent, false, 1.1f, 0.88f, 0.2f, 0.2f);
		_acceleration_scroll.UpdateAccelerationEnd(_point_draw.X, _point_begin.X, 1.0f - _percent, false);
		_time_delay_behind--;
		if (_time_delay_behind < 0)
		{
			_time_delay_behind = 0;
			_percent_behind = (_point_draw_behind.X - _point_begin_behind.X) / game->_screen_width;
			_acceleration_scroll_behind.UpdateAcceleration(_point_draw_behind.X, _point_begin_behind.X, 1.0f - _percent_behind, false, 1.1f, 0.88f, 0.2f, 0.2f);
			_acceleration_scroll_behind.UpdateAccelerationEnd(_point_draw_behind.X, _point_begin_behind.X, 1.0f - _percent_behind, false);
		}

		if (_acceleration_scroll.isFinish() && _acceleration_scroll_behind.isFinish())
		{
			_state = 2;
			game->_state_gameplay.ResetBoardGame();
		}
	}
	if (_state == 2)
	{
		_time_wait_check_show_popup--;
		if (_time_wait_check_show_popup < 0)
		{
			_time_wait_check_show_popup = 0;
			_state = 3;
			StartCheckPopUp();
			_time_delay_behind = TIME_DELAY_BEHIND;
		}
	}
	else if (_state == 3)
	{
        bool can_update = true;
#ifdef MAC_OS
		if (PineAdBox::showAdState == 1 || game->_pine_ads_plugin._state_app_download == 1 ||
			game->_state_gameplay._hud_popup._state != 3)
		{
			can_update = false;
		}
#endif // MAC_OS
        if (can_update)
        {
            _percent += _speed;
            _speed *= 1.05f;
            if (_percent > 0.5f)
            {
                _state = 4;
				game->_state_gameplay._effect_new_game.Init();
            }
            _point_draw.X = _point_begin.X - _percent * game->_screen_width;
			_time_delay_behind--;
			if (_time_delay_behind < 0)
			{
				_time_delay_behind = 0;
				_percent_behind += _speed_behind;
				_speed_behind *= 1.05f;
			}
			_point_draw_behind.X = _point_begin_behind.X - _percent_behind * game->_screen_width;
        }
	}
	if (_state == 4)
	{
		_percent += _speed;
		_speed *= 1.05f;
		if (_percent > 1.0f)
		{
			_percent = 1.0f;
		}
		_percent_behind += _speed_behind;
		_speed_behind *= 1.05f;
		if (_percent_behind > 1.0f)
		{
			_percent_behind = 1.0f;
		}
		_point_draw.X = _point_begin.X - _percent * game->_screen_width;
		_point_draw_behind.X = _point_begin_behind.X - _percent_behind * game->_screen_width;
	}
}

void GPHudEndGame::Render()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	float draw_x = _point_draw.X;
	float draw_y = _point_draw.Y - 39.0f;
	GET_SPRITE(SPRITEID_HUD_GAMEOVER)->DrawFrame(G(), 0, draw_x, draw_y);

	draw_x = _point_draw_behind.X;
	draw_y = _point_draw_behind.Y + 39.0f;
	GET_SPRITE(SPRITEID_HUD_GAMEOVER)->DrawFrame(G(), 1, draw_x, draw_y);
}

void GPHudEndGame::StartCheckPopUp()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	game->_state_gameplay._hud_popup.CheckStartPopup();
}

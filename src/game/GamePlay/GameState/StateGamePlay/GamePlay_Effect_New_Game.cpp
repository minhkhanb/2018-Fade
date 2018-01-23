#include "pch.h"
#include "../../../GameCore/CGame.h"

void EffectNewGame::Default()
{
	_state = -1;
}

void EffectNewGame::Init()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	_percent = 1.0f;
	_speed = 0.01f;
	_acceleration_scroll.Defalt();
	_opacity = 100.0f;
	_state = 0;
}

void EffectNewGame::Update()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	if (_state == 0)
	{
		_acceleration_scroll.UpdateAcceleration(_percent, 0.0f, (1.0f - _percent), false, 1.05f, 0.908f, 0.01f, 0.0001f);
		_acceleration_scroll.UpdateAccelerationEnd(_percent, 0.0f, (1.0f - _percent), false);
		//_acceleration_scroll.PrintfSpeed();
		if (_acceleration_scroll.isFinish())
		{
			_state = 1;
			game->_state_gameplay._hud_background.Init();
		}
	}
	if (_state == 1)
	{
		_opacity -= 2.0f;
		if (_opacity < 0)
		{
			_state = 2;
			game->_state_gameplay._gameplay_state = 1;
			game->_state_gameplay.ResetGamePlay();
			game->_state_gameplay._master_game._opacity_grid = 100.0f;
			if (game->_counter_game_play >= 2)
			{
#if defined (MAC_OS)
				if (game->_state_gameplay._hud_tutorial.CheckFinishTut())
				{
					if (!game->_state_gameplay._user._no_ads)
					{
						PineAdBox::ShowAdmobBanner();
					}
				}
				else
				{
					PineAdBox::CloseAdmobBanner();
				}
#elif defined (ANDROID_OS)
				if (game->_state_gameplay._hud_tutorial.CheckFinishTut())
				{
					if (!game->_state_gameplay._user._no_ads)
					{
						GAME()->ShowBannerAds();
					}
				}
				else
				{
					GAME()->HideBannerAds();
				}
#endif 
			}
		}
	}
}

void EffectNewGame::Render()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	if (_state > -1 && _state < 2)
	{
		G()->SetOpacity(_opacity);
		G()->SetColor(0xFF4B8B89);
		G()->FillFullScreen(true);
		float scroll_distance_y = _percent * game->_screen_height;


		float draw_x = game->_point_o.X;
		float draw_y = game->_point_o.Y + scroll_distance_y;
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
		G()->SetOpacity(100);



		draw_x = game->_point_o.X;
		draw_y = game->_point_right_bottom.Y + scroll_distance_y;
		G()->SetColorMask(game->_state_gameplay._hud_background._color_background_begin);
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
		G()->SetColorMask(game->_state_gameplay._hud_background._color_radian_begin);
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

		game->_state_gameplay._master_game._opacity_grid = 100.0f;
		game->_state_gameplay._master_game.RenderMatrix(0.0f, scroll_distance_y);
		game->_state_gameplay._master_game._opacity_grid = 0.0f;
	}
}

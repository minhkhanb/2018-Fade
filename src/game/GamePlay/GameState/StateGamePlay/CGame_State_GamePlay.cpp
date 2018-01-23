#include "pch.h"
#include "../../../GameCore/CGame.h"

void StateGamePlay::InitGamePlay()
{
	_gameplay_state = 1;
	_hud_background.Init();
	_hud_background._state = 0;
	_hud_score.Init();
	_hud_ingame.Init();
	_master_game.InitGrid7x7();
	_scroll_page_x = 0.0f;
	_hud_popup.Default();
	_effect_new_game.Default();
#ifdef MAC_OS
	PineGameCenterController::SubmitMyScore("fade_topplayer", _user._best_score);
#endif
	if (!_hud_tutorial.CheckFinishTut())
	{
		_gameplay_state = -10;
		_hud_tutorial.Init();
	}
	_effect_fish_tank.DefaultManager();
}

void StateGamePlay::ResetGamePlay()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	_hud_background._state = 0;
	_hud_score.Init();
	_user._retry += 1;
	game->_counter_game_play += 1;
	_user.DataSave();
    _effect_fish_tank.FreeMemory();
}

void StateGamePlay::ResetBoardGame()
{
	_master_game.ResetGrid();
}

void StateGamePlay::UpdateGamePlay()
{
	ColorBorn *game = (ColorBorn*)GAME()->_current_game;
	if (game->_sub_state == k_INIT)
	{
		InitGamePlay();
		game->_sub_state = k_LOOP;
	}
	if (game->_sub_state == k_LOOP)
	{
		UpdateScrollPageY();
		if (_gameplay_state == -20)
		{
			_hud_loading.Update();
		}
		if (_gameplay_state == -10)
		{
			_hud_tutorial.Update();
			_master_game.UpdateMatrix();
			_hud_background.Update();
		}
		if (_gameplay_state == -1)
		{
			_master_game._effect_fade_in_fade_out_grid.Update();
			_master_game._effect_fade_in_fade_out_grid.SetOutValue(_master_game._opacity_grid);
			_hud_score._opacity_current_score = (_master_game._effect_fade_in_fade_out_grid._percent) * 100.0f;
			if (_master_game._effect_fade_in_fade_out_grid.isFinish())
			{
				_hud_score._opacity_current_score = 0.0f;
				_master_game.InitMatrix();
				_gameplay_state = 0;
				_master_game._effect_fade_in_fade_out_grid.Init(true, 0.0f);
				_hud_score.Init();
				_user._retry += 1;
				game->_counter_game_play += 1;
				_user.DataSave();
				_effect_fish_tank.FreeMemory();
			}
		}
		if (_gameplay_state == 0)
		{
			_master_game._effect_fade_in_fade_out_grid.Update();
			_master_game._effect_fade_in_fade_out_grid.SetOutValue(_master_game._opacity_grid);
			_hud_score._opacity_current_score = (_master_game._effect_fade_in_fade_out_grid._percent) * 100.0f;
			if (_master_game._effect_fade_in_fade_out_grid.isFinish())
			{
				if (_hud_background._state == 0)
				{
					_hud_score._opacity_current_score = 100.0f;
					_gameplay_state = 1;
					if (game->_counter_game_play >= 2 )
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
			_hud_background.Update();
		}
		if (_gameplay_state == 1)
		{
			UpdateControl();
			_master_game.UpdateMatrix();
			_hud_background.Update();
		}
		if (_gameplay_state == 2)
		{
			_hud_share.Update();
		}
		if (_gameplay_state == 3)
		{
			if (!_master_game._effect_fade_in_fade_out_grid.isFinish())
			{
				_master_game._effect_fade_in_fade_out_grid.Update();
				_master_game._effect_fade_in_fade_out_grid.SetOutValue(_master_game._opacity_grid);
			}
			_hud_end_game.Update();
			_effect_new_game.Update();
		}
		if (_gameplay_state == 4)
		{
			_hud_popup.Update();
		}
		_effect_fish_tank.UpdateManager();
	}
}

void StateGamePlay::RenderGamePlay()
{
	_hud_background.Render();

	_hud_score.Render();
	_hud_ingame.Render();

	_master_game.RenderMatrix(0.0f, 0.0f);


	if (_gameplay_state == 2)
	{
		_hud_popup.Render();
		_hud_share.Render();
	}
	if (_gameplay_state == 3)
	{
		_hud_end_game.Render();
	}
	if (_gameplay_state == 4)
	{
		_hud_end_game.Render();
		_hud_popup.Render();
	}
	if (_gameplay_state == -10)
	{
		_hud_tutorial.Render();
	}

	if (_gameplay_state == -20)
	{
		_hud_loading.Render();
	}
#ifdef RENDER_GRID
	G()->SetColor(0xFFFFFFFF);
	G()->SetColor(0xFFFFFFFF);
	G()->DrawLine(0.0f, 177.0f, 750.0f, 177.0f);
	G()->DrawLine(0.0f, 275.0f, 750.0f, 275.0f);
	G()->DrawLine(0.0f, 320.0f, 750.0f, 320.0f);
	G()->DrawLine(0.0f, 427.0f, 750.0f, 427.0f);
	G()->DrawLine(0.0f, 463.0f, 750.0f, 463.0f);
	G()->DrawLine(0.0f, 835.0f, 750.0f, 835.0f);
	G()->DrawLine(0.0f, 747.0f, 750.0f, 747.0f);
	G()->DrawLine(0.0f, 411.0f, 750.0f, 411.0f);
#endif
}

bool StateGamePlay::UpdateControl()
{
	bool ret = false;
	if (!_master_game.UpdateTouchMatrix())
	{
		if (!_hud_ingame.UpdateButton())
		{

		}
	}
	else
	{
		ret = true;
	}
	return ret;
}

void StateGamePlay::UpdateScrollPageX()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	if (game->_current_state == k_GS_SETTING)
	{
		_scroll_page_x = game->_state_setting_credit._hud_setting_button._scroll_page_x - game->_screen_width;
	}
	else
	{
		_scroll_page_x = 0.0f;
	}
	_master_game.UpdatePosMatrix();
	_hud_ingame.UpdatePos();
	_hud_score.UpdatePos();
}

void StateGamePlay::UpdateScrollPageY()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	if (game->_current_state == k_GS_LOGO)
	{
		_scroll_page_y = game->_state_logo._scroll_page_y - game->_screen_height;
	}
	else
	{
		_scroll_page_y = 0.0f;
	}
	_master_game.UpdatePosMatrix();
	_hud_ingame.UpdatePos();
	_hud_score.UpdatePos();
}

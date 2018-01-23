#include "pch.h"
#include "../../../GameCore/CGame.h"

void StateSettingAndCredit::InitSetting()
{
#ifdef MAC_OS
	PineAdBox::CloseAdmobBanner();
#endif // MAC_OS
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	_hud_setting_button.Init();
	_effect_touch_button.Default();
	_time_cooldown_replay_function_dis_ads = 0;
	_state = 1;
}

void StateSettingAndCredit::RenderSetting()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	game->_state_gameplay.RenderGamePlay();
	_effect_touch_button.RenderManager();
	_hud_setting_button.Render();
	if (_state == -20)
	{
		game->_state_gameplay._hud_loading.Render();
	}
}

void StateSettingAndCredit::UpdateSetting()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	if (game->_sub_state == k_INIT)
	{
		InitSetting();
		game->_sub_state = k_LOOP;
	}
	if (game->_sub_state == k_LOOP)
	{
		if (_state == 1)
		{
			if (!UpdateControl())
			{

			}
			_hud_setting_button.Update();
			game->_state_gameplay.UpdateScrollPageX();
		}
		if (_state == -20)
		{
			game->_state_gameplay._hud_loading.Update();
		}
		_effect_touch_button.UpdateManager();
		_time_cooldown_replay_function_dis_ads++;
		if (_time_cooldown_replay_function_dis_ads > 30)
		{
#ifdef MAC_OS
			//PineAdBox::CloseAdmobBanner();
#endif // MAC_OS
			_time_cooldown_replay_function_dis_ads = 0;
		}
        game->_state_gameplay._effect_fish_tank.UpdateManager();
	}
}

bool StateSettingAndCredit::UpdateControl()
{
	bool ret = false;
	if (_hud_setting_button.UpdateTouch())
	{
		ret = true;
	}
	return ret;
}

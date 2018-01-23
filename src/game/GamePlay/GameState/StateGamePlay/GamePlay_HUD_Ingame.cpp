#include "pch.h"
#include "../../../GameCore/CGame.h"
#include "../../../GameCore/Os_Functions.h"

void GPHudIngame::Init()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	_state = 1;
	_point_begin.X = game->_point_o.X + game->_screen_width / 2;
	_point_begin.Y = game->_point_o.Y;
	_point_draw = _point_begin;

	/*Init Button*/

	//LeaderBoard
	float draw_x = _point_begin.X - (game->_screen_width / 2 - 36.0f);
	float draw_y = _point_begin.Y + 38.0f;
	_button_arr[0].Init(BUTTON_STATE_NORMAL, draw_x, draw_y, A_HVCENTER);
	_button_arr[0].SetAnim(SPRITEID_HUD_INGAME, 4);
	//_button_arr[0].SetSoundID(SFX_BUTTON);

	//Share
	draw_x = _point_begin.X - (game->_screen_width / 2 - 136.0f);
	draw_y = _point_begin.Y + 32.0f;
	_button_arr[1].Init(BUTTON_STATE_NORMAL, draw_x, draw_y, A_HVCENTER);
	_button_arr[1].SetAnim(SPRITEID_HUD_INGAME, 8);
	//_button_arr[0].SetSoundID(SFX_BUTTON);

	//Remove
	draw_x = _point_begin.X - (game->_screen_width / 2 - 316.0f);
	draw_y = _point_begin.Y + 29.0f;
	_button_arr[2].Init(BUTTON_STATE_NORMAL, draw_x, draw_y, A_HVCENTER);
	_button_arr[2].SetAnim(SPRITEID_HUD_INGAME, 12);
	if (game->_state_gameplay._user._no_ads)
	{
		_button_arr[2]._state = BUTTON_STATE_HIDE;
	}
	//_button_arr[0].SetSoundID(SFX_BUTTON);

	//Replay
	draw_x = _point_begin.X - (game->_screen_width / 2 - 225.0f);
	draw_y = _point_begin.Y + 28.0f;
	_button_arr[3].Init(BUTTON_STATE_NORMAL, draw_x, draw_y, A_HVCENTER);
	_button_arr[3].SetAnim(SPRITEID_HUD_INGAME, 16);
	//_button_arr[0].SetSoundID(SFX_BUTTON);

	//Menu
	/*draw_x = _point_begin.X + (399.0f - game->_screen_width / 2);
	draw_y = _point_begin.Y + 29.0f;*/
	draw_x = _point_begin.X + game->_screen_width / 2 + (702.0f - 750.0f);
	draw_y = _point_begin.Y + 28.0f;
	_button_arr[4].Init(BUTTON_STATE_NORMAL, draw_x, draw_y, A_HVCENTER);
	_button_arr[4].SetAnim(SPRITEID_HUD_INGAME, 20);
	//_button_arr[0].SetSoundID(SFX_BUTTON);

	//
	/*draw_x = _point_begin.X + game->_screen_width / 2 + (702.0f - 750.0f);
	draw_y = _point_begin.Y + 28.0f;
	_button_arr[5].Init(BUTTON_STATE_NORMAL, draw_x, draw_y, A_HVCENTER);
	_button_arr[5].SetAnim(SPRITEID_HUD_INGAME, 20);
	//_button_arr[0].SetSoundID(SFX_BUTTON);*/
	/*End*/
	_title_scroll_y = 0.0f;
	for (int i = 0; i < INGAME_BUTTON_NUM; i++)
	{
		_button_arr[i].SetSoundID(SFX_BUTTON);
	}
}

void GPHudIngame::Update()
{
	
}

void GPHudIngame::UpdatePos()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	float draw_x = 0.0f;
	float draw_y = 0.0f;
	for (int i = 0; i < INGAME_BUTTON_NUM; i++)
	{
		draw_x = _button_arr[i]._posX_con + game->_state_gameplay._scroll_page_x;
		draw_y = _button_arr[i]._posY_con + game->_state_gameplay._scroll_page_y;
		_button_arr[i].SetPos(draw_x, draw_y);
	}
}

bool GPHudIngame::UpdateButton()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
#if !defined (MAC_OS)
	if (GAME()->_isBackkeyPress && game->_state_gameplay._hud_background._state == 1)
	{
		if (_button_arr[4]._state != BUTTON_STATE_ACTIVE)
		{
			_button_arr[4]._state = BUTTON_STATE_ACTIVE;
		}
		GAME()->_isBackkeyPress = false;
	}
#endif
	bool button_touched = false;
	int index = 0;
	for (int i = 0; i < INGAME_BUTTON_NUM; i++)
	{
		if (_button_arr[i]._state == BUTTON_STATE_ACTIVE)
		{
			button_touched = true;
			index = i;
			break;
		}
	}
	if (button_touched)
	{
		if (_button_arr[index].NeedAction())
		{
			switch (index)
			{
			case 0:
//#ifdef MAC_OS
//				//PineGameCenterController::ShowLeaderAchivement();
//#endif // MAC_OS
				//leader board
#ifdef MAC_OS
				PineGameCenterController::SubmitMyScore("fade_topplayer", game->_state_gameplay._user._best_score);
				PineGameCenterController::ShowLeaderBoard("fade_topplayer");
#endif // MAC_OS
				break;
			case 1:
				game->_state_gameplay._hud_share.Init();
				//share
				break;
			case 2:
				//remove ads
				game->_state_gameplay._hud_loading.Init();
				printf("\nbutton remove");
				if (!game->_state_gameplay._user._no_ads)
				{
					//hud loading
#ifdef MAC_OS
					if (GAME()->_device.IsNetworkAvailable())
					{
						PurchaseProduct("fade_NoAds");
					}
					else
					{
						char message[512];
						sprintf(message, "Internet connection is required to complete the purchase!");
						GAME()->_pine_social->ShowMessageBox(message, "No Connection!");
					}
#endif
				}
				break;
			case 3:
				//reset
				game->_state_gameplay._hud_score.UpdateAndSubmitHightScore();
				game->_state_gameplay._gameplay_state = -1;
				game->_state_gameplay._master_game._effect_fade_in_fade_out_grid.Init(false, game->_state_gameplay._master_game._opacity_grid);
				game->_state_gameplay._hud_background.SetResetTimeBar(true);
				break;
			case 4:
				game->SetState(k_GS_SETTING);
				break;
			case 5:
				
				break;
			default:
				break;
			}
			for (int i = 0; i < INGAME_BUTTON_NUM; i++)
			{
				if (_button_arr[i]._state != BUTTON_STATE_LOCK && _button_arr[i]._state != BUTTON_STATE_HIDE)
				{
					_button_arr[i].SetState(BUTTON_STATE_NORMAL);
				}
			}
		}
		return true;
	}
	bool ret = false;
	for (int i = 0; i < GAME()->_num_touches; i++)
	{
		for (int button = 0; button < INGAME_BUTTON_NUM; button++)
		{
			if (_button_arr[button]._state == BUTTON_STATE_LOCK || _button_arr[button]._state == BUTTON_STATE_HIDE)
			{
				continue;
			}
			int x = _button_arr[button].TZ_GetX() - 20.0f;
			int y = _button_arr[button].TZ_GetY() - 20.0f;
			int w = _button_arr[button].TZ_GetWidth() + 40.0f;
			int h = _button_arr[button].TZ_GetHeight() + 40.0f;
			if (button == 5)
			{
				x = _button_arr[button].TZ_GetX() - 30.0f;
				y = _button_arr[button].TZ_GetY() - 30.0f;
				w = _button_arr[button].TZ_GetWidth() + 60.0f;
				h = _button_arr[button].TZ_GetHeight() + 60.0f;
			}
			Button *bt = &_button_arr[button];
			if (CHECK_POINT_IN_RECT(TOUCHS(i)->x, TOUCHS(i)->y, x, y, w, h))
			{
				if (TOUCHS(i)->_state == TOUCH_DOWN)
				{
					if (bt->_touch_id == -1)
					{
						//if (!_play_sound_button_gameplay)
						//{
						//_play_sound_button_gameplay = true;
						//GAME()->PlaySFX(SFX_BUTTON);
						//}
						bt->_touch_id = TOUCHS(i)->_id;
						bt->SetState(BUTTON_STATE_SELECT);
					}
				}
				else if (TOUCHS(i)->_state == TOUCH_DRAG)
				{
					if (bt->IsAction(TOUCHS(i)->_id))
					{
						//bt->SetState(BUTTON_STATE_SELECT);
					}
				}
				else if (TOUCHS(i)->_state == TOUCH_UP)
				{
					if (bt->IsAction(TOUCHS(i)->_id))
					{
						//_play_sound_button_gameplay = false;
						bt->SetState(BUTTON_STATE_ACTIVE);
						printf("\n button = %d", button);
					}
				}
				if (bt->_touch_id != -1)
				{
					ret = true;
				}
			}
			else
			{
				if (bt->IsAction(TOUCHS(i)->_id))
				{
					if (TOUCHS(i)->_state == TOUCH_UP)
					{
						//_play_sound_button_gameplay = false;
						bt->_touch_id = -1;
						bt->SetState(BUTTON_STATE_ACTIVE);
					}
					ret = true;
				}
			}
		}
	}
	return ret;
}

void GPHudIngame::Render()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	for (int i = 0; i < INGAME_BUTTON_NUM; i++)
	{
		_button_arr[i].Render(G());
		_button_arr[i].Update();
	}
	float draw_x = 0.0f;
	float draw_y = 0.0f;
	draw_x = _point_draw.X + game->_state_gameplay._scroll_page_x;
	draw_y = _point_draw.Y + game->_screen_height - 30.0f + game->_state_gameplay._scroll_page_y + _title_scroll_y;
	GET_SPRITE(SPRITEID_HUD_INGAME_TITLE)->DrawFrame(G(), 0, draw_x, draw_y);


	/*for (int i = 0; i < INGAME_BUTTON_NUM; i++)
	{
		int x = _button_arr[i].TZ_GetX() - 20.0f;
		int y = _button_arr[i].TZ_GetY() - 20.0f;
		int w = _button_arr[i].TZ_GetWidth() + 40.0f;
		int h = _button_arr[i].TZ_GetHeight() + 40.0f;
		if (i == 5)
		{
			x = _button_arr[i].TZ_GetX() - 30.0f;
			y = _button_arr[i].TZ_GetY() - 30.0f;
			w = _button_arr[i].TZ_GetWidth() + 60.0f;
			h = _button_arr[i].TZ_GetHeight() + 60.0f;
		}
		G()->SetColor(0xa7FFFF00);
		G()->FillRect(x, y, w, h, true);
	}*/
}

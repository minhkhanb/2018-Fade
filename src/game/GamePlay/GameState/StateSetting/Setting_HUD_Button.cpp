#include "pch.h"
#include "../../../GameCore/CGame.h"
#include "../../../GameCore/Os_Functions.h"

#ifdef MAC_OS
extern "C" void IapRestore();
extern "C" void SendMailSupport(const char *body, const char *title);
#else
extern "C" void SendMailSupport(const char *body, const char *title) {};
#endif

#define SETTING_FRAME_SCROLL_PAGE			20
#define SETTING_WIDTH_SCROLL_PAGE			(game->_screen_width)


void SettingHudButton::Init()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	_point_begin.X = game->_point_o.X + game->_screen_width / 2;
	_point_begin.Y = game->_point_o.Y + 85.0f;
	_point_draw = _point_begin;
	/*Init Button*/
	float draw_x = 0.0f;
	float draw_y = 0.0f;
#if defined (ANDROID_OS) || _WINDOWS
	float reduce = (10.0f + 158.0f) / 6 + 30.0f;
#else
	float reduce = 0.0f;
#endif
	PDEBUG("\n reduce:%f", reduce);
	//music
	draw_x = _point_draw.X + (-148.0f) - reduce;
	draw_y = _point_draw.Y + (251.0f - 85.0f);
	_arr_button[0].Init(BUTTON_STATE_NORMAL, draw_x, draw_y, A_HVCENTER);
	_arr_button[0].SetAnim(SPRITEID_HUD_SETTING, 0);
	//sound
	draw_x = _point_draw.X + (10.0f) - reduce;
	draw_y = _point_draw.Y + (251.0f - 85.0f);
	_arr_button[1].Init(BUTTON_STATE_NORMAL, draw_x, draw_y, A_HVCENTER);
	_arr_button[1].SetAnim(SPRITEID_HUD_SETTING, 4);
	//facebook
#if defined (ANDROID_OS) || _WINDOWS
	draw_x = _point_draw.X + (10.0f + 158.0f) - reduce;
	draw_y = _point_draw.Y + (251.0f - 85.0f);
#else
	draw_x = _point_draw.X + (-148.0f) - reduce;
	draw_y = _point_draw.Y + (405.0f - 85.0f);
#endif
	_arr_button[2].Init(BUTTON_STATE_NORMAL, draw_x, draw_y, A_HVCENTER);
	_arr_button[2].SetAnim(SPRITEID_HUD_SETTING, 8);
	//twitter
	draw_x = _point_draw.X + (10.0f);
	draw_y = _point_draw.Y + (405.0f - 85.0f);
	_arr_button[3].Init(BUTTON_STATE_NORMAL, draw_x, draw_y, A_HVCENTER);
	_arr_button[3].SetAnim(SPRITEID_HUD_SETTING, 12);
	//icloud
	draw_x = _point_draw.X + (-115.0f);
	draw_y = _point_draw.Y + (589.0f - 85.0f);
	_arr_button[4].Init(BUTTON_STATE_NORMAL, draw_x, draw_y, A_HVCENTER);
	_arr_button[4].SetAnim(SPRITEID_HUD_SETTING, 16);
	/*//remove
	draw_x = _point_draw.X + (-118.0f);
	draw_y = _point_draw.Y + (678.0f - 85.0f);
	_arr_button[5].Init(BUTTON_STATE_NORMAL, draw_x, draw_y, A_HVCENTER);
	_arr_button[5].SetAnim(SPRITEID_HUD_SETTING, 20);*/
	//reset
	draw_x = _point_draw.X + (-132.0f);
#if defined (ANDROID_OS) || _WINDOWS
	draw_y = _point_draw.Y + (589.0f - 85.0f) - 2.0f * reduce;
#else
	draw_y = _point_draw.Y + (697.0f - 85.0f) - 2.0f * reduce;
#endif
	_arr_button[5].Init(BUTTON_STATE_NORMAL, draw_x, draw_y, A_HVCENTER);
	_arr_button[5].SetAnim(SPRITEID_HUD_SETTING, 24);
	//restore
	draw_x = _point_draw.X + (-184.0f);
	draw_y = _point_draw.Y + (797.0f - 85.0f);
	_arr_button[6].Init(BUTTON_STATE_NORMAL, draw_x, draw_y, A_HVCENTER);
	_arr_button[6].SetAnim(SPRITEID_HUD_SETTING, 28);
	//contact
	draw_x = _point_draw.X + (-109.0f);
#if defined (ANDROID_OS) || _WINDOWS
	draw_y = _point_draw.Y + (697.0f - 85.0f) - 2.0f * reduce;
#else
	draw_y = _point_draw.Y + (897.0f - 85.0f) - 2.0f * reduce;
#endif
	_arr_button[7].Init(BUTTON_STATE_NORMAL, draw_x, draw_y, A_HVCENTER);
	_arr_button[7].SetAnim(SPRITEID_HUD_SETTING, 32);
	//credit
	draw_x = _point_draw.X + (-69.0f);
#if defined (ANDROID_OS) || _WINDOWS
	draw_y = _point_draw.Y + (797.0f - 85.0f) - 2.0f * reduce;
#else
	draw_y = _point_draw.Y + (997.0f - 85.0f) - 2.0f * reduce;
#endif
	_arr_button[8].Init(BUTTON_STATE_NORMAL, draw_x, draw_y, A_HVCENTER);
	_arr_button[8].SetAnim(SPRITEID_HUD_SETTING, 36);
	//back
	draw_x = game->_point_o.X + 38.0f;
	draw_y = game->_point_right_bottom.Y - (1334.0f - 1250.0f);
	_arr_button[9].Init(BUTTON_STATE_NORMAL, draw_x, draw_y, A_HVCENTER);
	_arr_button[9].SetAnim(SPRITEID_HUD_SETTING, 40);
	/*End*/

	_scroll_page_x = SETTING_WIDTH_SCROLL_PAGE;
	_state = 1;
	_speed_scroll = SETTING_WIDTH_SCROLL_PAGE / SETTING_FRAME_SCROLL_PAGE;
	_scroll_page_credit_x = SETTING_WIDTH_SCROLL_PAGE;
	_is_draw_credits = false;

	for (int i = 0; i < SETTING_NUM_BUTTON; i++)
	{
		_arr_button[i].SetSoundID(SFX_BUTTON);
	}

	//Kha update android
#if defined (ANDROID_OS) || _WINDOWS
	_arr_button[SETTING_BUTTON_TWITTER].SetState(BUTTON_STATE_HIDE);
	_arr_button[SETTING_BUTTON_ICLOUD].SetState(BUTTON_STATE_HIDE);
	_arr_button[SETTING_BUTTON_RESTORE].SetState(BUTTON_STATE_HIDE);
#endif

}

void SettingHudButton::Update()
{
	ColorBorn *game = (ColorBorn*)GAME()->_current_game;
	if (_state == 1)
	{
		_scroll_page_x -= _speed_scroll;
		if (_scroll_page_x <= 0.0f)
		{
			_scroll_page_x = 0.0f;
			_state = 2;
		}
	}
	if (_state == 3)
	{
		_scroll_page_credit_x -= _speed_scroll;
		if (_scroll_page_credit_x <= 0.0f)
		{
			_scroll_page_credit_x = 0.0f;
			_state = 4;
		}
	}
	if (_state == 5)
	{
		_scroll_page_credit_x += _speed_scroll;
		if (_scroll_page_credit_x >= SETTING_WIDTH_SCROLL_PAGE)
		{
			_scroll_page_credit_x = SETTING_WIDTH_SCROLL_PAGE;
			_state = 2;
			_is_draw_credits = false;
		}
	}
	if (_state == -1)
	{
		_scroll_page_x += _speed_scroll;
		if (_scroll_page_x > SETTING_WIDTH_SCROLL_PAGE)
		{
			_scroll_page_x = SETTING_WIDTH_SCROLL_PAGE;
			_state = 4;
			game->SetState(k_GS_PLAYGAME);
			game->SetSubState(k_LOOP);
		}
	}
	UpdatePosButton();
}

void SettingHudButton::Render()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	float draw_x = _point_draw.X + _scroll_page_x + (-160.0f) - (SETTING_WIDTH_SCROLL_PAGE - _scroll_page_credit_x);
	float draw_y = _point_draw.Y;
	GET_SPRITE(SPRITEID_HUD_SETTING)->DrawFrame(G(), 0, draw_x, draw_y);

	for (int i = 0; i < SETTING_NUM_BUTTON; i++)
	{
		if (i == 0 && !game->_state_gameplay._user._is_music)
		{
			G()->SetOpacity(30);
		}
		if (i == 1 && !game->_state_gameplay._user._is_sound)
		{
			G()->SetOpacity(30);
		}
		_arr_button[i].Render(G());
		_arr_button[i].Update();
		G()->SetOpacity(100);
	}
	if (_is_draw_credits)
	{
		RenderCredits();
	}


	/*for (int i = 0; i < SETTING_NUM_BUTTON; i++)
	{
		int x = _arr_button[i].TZ_GetX() - 20.0f;
		int y = _arr_button[i].TZ_GetY() - 20.0f;
		int w = _arr_button[i].TZ_GetWidth() + 40.0f;
		int h = _arr_button[i].TZ_GetHeight() + 40.0f;
		if (i == 9)
		{
			x = _arr_button[i].TZ_GetX() - 40.0f;
			y = _arr_button[i].TZ_GetY() - 40.0f;
			w = _arr_button[i].TZ_GetWidth() + 160.0f;
			h = _arr_button[i].TZ_GetHeight() + 80.0f;
		}
		G()->SetColor(0xa7FFFF00);
		G()->FillRect(x, y, w, h, true);
	}*/
}

void SettingHudButton::RenderCredits()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	float draw_x = _point_draw.X + _scroll_page_credit_x;
	float draw_y = _point_draw.Y;
	GET_SPRITE(SPRITEID_HUD_SETTING)->DrawFrame(G(), 45, draw_x, draw_y);
}

void SettingHudButton::UpdatePosButton()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
#if defined (ANDROID_OS) || _WINDOWS
	float reduce = (10.0f + 158.0f) / 6 + 30.0f;
#else
	float reduce = 0.0f;
#endif
	float draw_x = 0.0f - reduce;
	float draw_y = 0.0f - reduce;
	for (int i = 0; i < SETTING_NUM_BUTTON; i++)
	{
		draw_x = _arr_button[i]._posX_con + _scroll_page_x;
		if (_is_draw_credits)
		{
			if (i != 9)
			{
				draw_x = _arr_button[i]._posX_con + _scroll_page_x - (SETTING_WIDTH_SCROLL_PAGE - _scroll_page_credit_x);
			}
		}
		draw_y = _arr_button[i]._posY_con;
		_arr_button[i].SetPos(draw_x, draw_y);
	}
}

bool SettingHudButton::UpdateTouch()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
#if !defined (MAC_OS)
	if (GAME()->_isBackkeyPress)
	{
		if (_arr_button[9]._state != BUTTON_STATE_ACTIVE)
		{
			_arr_button[9]._state = BUTTON_STATE_ACTIVE;
		}
		GAME()->_isBackkeyPress = false;
	}
#endif
	bool button_touched = false;
	int index = 0;
	for (int i = 0; i < SETTING_NUM_BUTTON; i++)
	{
		if (_arr_button[i]._state == BUTTON_STATE_ACTIVE)
		{
			button_touched = true;
			index = i;
			break;
		}
	}
	if (button_touched)
	{
		if (_arr_button[index].NeedAction())
		{
			int pos_x = 0;
			int pos_y = 0;
			switch (index)
			{
			case 0:
				pos_x = _arr_button[0]._posX_con;
				pos_y = _arr_button[0]._posY_con;
				game->_state_setting_credit._effect_touch_button.AddEffect(pos_x, pos_y);
				game->_state_gameplay._user._is_music = !game->_state_gameplay._user._is_music;
				game->_state_gameplay._user.DataSave();
				GAME()->_musicEnable = game->_state_gameplay._user._is_music;
				if (game->_state_gameplay._user._is_music)
				{
					GAME()->LoadMusic(BGM_ALL);
					GAME()->PlayCurrentMusic(-1);
				}
				else
				{
					GAME()->StopCurrentMusic();
				}
				break;
			case 1:
				pos_x = _arr_button[1]._posX_con;
				pos_y = _arr_button[1]._posY_con;
				game->_state_setting_credit._effect_touch_button.AddEffect(pos_x, pos_y);
				game->_state_gameplay._user._is_sound = !game->_state_gameplay._user._is_sound;
				game->_state_gameplay._user.DataSave();
				GAME()->_soundEnable = game->_state_gameplay._user._is_sound;
				break;
			case SETTING_BUTTON_FACEBOOK:
				pos_x = _arr_button[2]._posX_con;
				pos_y = _arr_button[2]._posY_con;
				game->_state_setting_credit._effect_touch_button.AddEffect(pos_x, pos_y);
#if defined (MAC_OS)
				PineSocial::OpenURL(FACEBOOK_URL);
#elif defined (ANDROID_OS)
				OS_BrowserWebPage(FACEBOOK_URL);
#endif // MAC_OS
				break;
			case 3:
				pos_x = _arr_button[3]._posX_con;
				pos_y = _arr_button[3]._posY_con;
				game->_state_setting_credit._effect_touch_button.AddEffect(pos_x, pos_y);
#if defined (MAC_OS)
				PineSocial::OpenURL(TWITTER_URL);
#elif defined (ANDROID_OS)
				OS_BrowserWebPage(TWITTER_URL);
#endif // MAC_OS
				break;
			case 4://icloud
				game->_state_gameplay._hud_loading.Init(true);
				printf("\nbutton icloud");
				   //hud loading
#if defined (MAC_OS)
				if (GAME()->_device.IsNetworkAvailable())
				{
					GAME()->CheckICloud();
					char message[512];
					sprintf(message, "iCloud sync done!");
					GAME()->_pine_social->ShowMessageBox(message, "iCloud!");
				}
#elif defined (ANDROID_OS)
				if (!GAME()->_async_task_manager._on_process_sync_cloud)
				{
					PDEBUG("Press SETTING_BUTTON_ICLOUD\n");
					game->_state_gameplay._user.CheckLocalAndCloudSaveFile();
				}
#endif // MAC_OS
				break;
//			case 5://remove ads
//				printf("\nbutton remove");
//				if (!game->_state_gameplay._user._no_ads)
//				{
//					//hud loading
//#ifdef MAC_OS
//					if (GAME()->_device.IsNetworkAvailable())
//					{
//						PurchaseProduct("fade_NoAds");
//					}
//					else
//					{
//						char message[512];
//						sprintf(message, "Internet connection is required to complete the purchase!");
//						GAME()->_pine_social->ShowMessageBox(message, "No Connection!");
//					}
//#endif
//				}
//				break;
			case 5://reset turtorial
				_state = -1;
				ResetGamePlayToTutorial();
				printf("\nbutton Reset tutorial");
				break;
			case 6://restore purchase
				game->_state_gameplay._hud_loading.Init();
				printf("\nbutton restore");
				//hud_loading
#if defined (MAC_OS)
				if (GAME()->_device.IsNetworkAvailable())
				{
					IapRestore();
				}
				else
				{
					char message[512];
					sprintf(message, "Internet connection is required to complete the restore!");
					GAME()->_pine_social->ShowMessageBox(message, "No Connection!");
				}
#elif defined (ANDROID_OS)

#endif // MAC_OS
				break;
			case 7://contact us
#if defined (ANDROID_OS)
				sprintf(GAME()->_async_task_manager._send_email_title, "[fade!][Android]");
				sprintf(GAME()->_async_task_manager._send_email_body, "%s", "");
				GAME()->_async_task_manager.AddCommand(CAsyncTasks::enumTypeCommand::COMMAND_TYPE_ASYN_SEND_EMAIL_INTENT);
#else
				char title[1024], body[1024];
				sprintf(title, "[fade!]");
				sprintf(body, "%s", "");
				SendMailSupport(body, title);
#endif
				PDEBUG("\nbutton contact");
				break;
			case 8://
				_is_draw_credits = true;
				_state = 3;
				break;
			case 9:
				if (_is_draw_credits)
				{
					if (_state == 4)
					{
						_state = 5;
					}
				}
				else
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
#endif // MAC_OS
					_state = -1;
				}
				break;
			default:
				break;
			}
			for (int i = 0; i < SETTING_NUM_BUTTON; i++)
			{
				if (_arr_button[i]._state != BUTTON_STATE_LOCK && _arr_button[i]._state != BUTTON_STATE_HIDE)
				{
					_arr_button[i].SetState(BUTTON_STATE_NORMAL);
				}
			}
		}
		return true;
	}
	bool ret = false;
	for (int i = 0; i < GAME()->_num_touches; i++)
	{
		for (int button = 0; button < SETTING_NUM_BUTTON; button++)
		{
			if (_arr_button[button]._state == BUTTON_STATE_LOCK || _arr_button[button]._state == BUTTON_STATE_HIDE)
			{
				continue;
			}
			int x = _arr_button[button].TZ_GetX() - 20.0f;
			int y = _arr_button[button].TZ_GetY() - 20.0f;
			int w = _arr_button[button].TZ_GetWidth() + 40.0f;
			int h = _arr_button[button].TZ_GetHeight() + 40.0f;
			if (i == 9)
			{
				x = _arr_button[button].TZ_GetX() - 40.0f;
				y = _arr_button[button].TZ_GetY() - 40.0f;
				w = _arr_button[button].TZ_GetWidth() + 160.0f;
				h = _arr_button[button].TZ_GetHeight() + 80.0f;
			}
			Button *bt = &_arr_button[button];
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

void SettingHudButton::ResetGamePlayToTutorial()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	game->_state_setting_credit._hud_setting_button._flag_reset_tutorial = true;
	game->_state_gameplay._master_game.InitMatrix();
	game->_state_gameplay._hud_score.UpdateAndSubmitHightScore();
	game->_state_gameplay._hud_score._score_current = 0;
	game->_state_gameplay._hud_tutorial.Init();
	game->_state_gameplay._gameplay_state = -10;
	game->_state_gameplay._hud_background._percent_current = 0.0f;
	game->_state_gameplay._hud_background._percent_target = 0.0f;
	if (game->_counter_game_play >= 2)
	{
#ifdef MAC_OS
		PineAdBox::CloseAdmobBanner();
#endif // MAC_OS
	}
}

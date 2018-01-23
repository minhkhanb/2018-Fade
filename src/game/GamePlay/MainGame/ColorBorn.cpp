#include "pch.h"
#include "../../GameCore/CGame.h"

void ColorBorn::UpdateAndRender()
{
	G()->ClearClip();
	G()->SetOpacity(100);
	if (!GAME()->LoadGameForceground())
	{
		return;
	}
	bool no_update = false;
	if (_flag_show_pine_ads == 1)
	{
		no_update = true;
	}
	switch (_current_state)
	{
	case k_GS_LOGO:
		_state_logo.UpdateLogo();
		_state_logo.RenderLogo();
		break;
	case k_GS_PLAYGAME:
		_state_gameplay.UpdateGamePlay();
		_state_gameplay.RenderGamePlay();
		break;
	case k_GS_EXAMPLE:
		_state_example.UpdateStateTest();
		_state_example.RenderStateTest();
		break;
	case k_GS_SETTING:
		_state_setting_credit.UpdateSetting();
		_state_setting_credit.RenderSetting();
		break;
	}
	GAME()->_device.UpdateAndPlayQueueSFX();
	PineGame::UpdateAndRender();
	if (_current_state != k_GS_LOGO)
	{
		if (_flag_show_pine_ads == 0)
		{
			/*printf("\nState advert %d, %d, %d", PineAdBox::showAdState, GAME()->_advert.IsAvailable(), GAME()->_advert.HasPopup());*/
			//printf("\n_state: %d", GAME()->_advert.GetState());
		}
	}
	_pine_ads_plugin.UpdateAdvert();
}

void ColorBorn::Init()
{
	_renderLogo = true;
	PineGame::Init();
	_device_ipad_ready = false;
	//port game//
	_point_o = GAME()->_game_context.MeasureAnchor(0, 0, ANCHOR_LEFT | ANCHOR_TOP);
	_point_right_bottom = GAME()->_game_context.MeasureAnchor(0, 0, ANCHOR_RIGHT | ANCHOR_BOTTOM);
	_screen_width = _point_right_bottom.X - _point_o.X;
	_screen_height = _point_right_bottom.Y - _point_o.Y;
	PDEBUG("\n_screen_width: %f, _screen_height: %f", _screen_width, _screen_height);
	PDEBUG("\n _point_o.X: %f, _point_o.Y: %f, point_right_bottom.X: %f, point_right_bottom.Y: %f", _point_o.X, _point_o.Y, _point_right_bottom.X, _point_right_bottom.Y);
	PDEBUG("\n ScaleOutX: %f, ScaleOutY: %f, scaleX: %f, scaleY: %f, ScaleOut: %f, TranslateX: %f, TranslateY: %f", GAME()->_game_context.ScaleOutX, GAME()->_game_context.ScaleOutY, GAME()->_game_context.ScaleX, GAME()->_game_context.ScaleY, GAME()->_game_context.ScaleOut, GAME()->_game_context.TranslateX, GAME()->_game_context.TranslateY);
#if !defined (ANDROID_OS)
	float radius = _screen_width / _screen_height;
	if (radius >= 0.749f && radius <= 0.751f)
	{
		_device_ipad_ready = true;
	}
	////port game////
	_w_follow_port = (1.0f - GAME()->_game_context.ScaleOutX) * k_SCREEN_WIDTH;
	_h_follow_port = (1.0f - GAME()->_game_context.ScaleOutX) * k_SCREEN_HEIGHT;
	printf("\n width: %f, height: %f", GAME()->_device.ScreenSize.W, GAME()->_device.ScreenSize.H);

	_device_w = 750;
	_device_h = 1334;
	if (GAME()->_device.ScreenSize.W / GAME()->_device.ScreenSize.H == 0.75)
	{
		_device_w = 768;
		_device_h = 1024;
		_device_current = DEVICE_CURRENT_IPAD;
	}
	else if (GAME()->_device.ScreenSize.W == 640.0f && GAME()->_device.ScreenSize.H == 960.0f)
	{
		_device_w = 640;
		_device_h = 960;
		_device_current = DEVICE_CURRENT_I4;
	}
	else
#endif
	{
		_device_w = 750;
		_device_h = 1334;
		_device_current = DEVICE_CURRENT_I56;
	}
	//_device_current = DEVICE_CURRENT_I4;
	PDEBUG("_device_current = %d \n", _device_current);

	_first_open_build = true;
	_volumn_bgm_game = 0.0f;
	_flag_show_pine_ads = 0;
	
	_time_cool_down_check_rate = 0;
	_flag_check_ready_rate = 1;
	_counter_set_active_rating = 0;
	_allready_reset_tutorial = false;
	_first_open_rating = true;
	_first_rating = true;
}

void ColorBorn::MeasureButton(Button * button)
{
	PinePoint btpos;
	btpos.X = button->_posX + button->TZ_GetX();
	btpos.Y = button->_posY + button->TZ_GetY();
	float btn_width = button->TZ_GetWidth();
	float btn_height = button->TZ_GetHeight();
	btpos = GAME()->_game_context.MeasureDensity(btpos, btn_width, btn_height);
	button->_posX = btpos.X - button->TZ_GetX();
	button->_posY = btpos.Y - button->TZ_GetY();
	button->_posX_con = button->_posX;
	button->_posY_con = button->_posY;
}

void ColorBorn::MeasureButton(Button * button, int anchor)
{
	PinePoint btpos;
	btpos.X = button->_posX + button->TZ_GetX();
	btpos.Y = button->_posY + button->TZ_GetY();


	if ((anchor & ANCHOR_RIGHT) != 0) {
		btpos.X = btpos.X - k_SCREEN_WIDTH;
	}

	if ((anchor & ANCHOR_BOTTOM) != 0) {
		btpos.Y = btpos.Y - k_SCREEN_HEIGHT;
	}

	btpos = GAME()->_game_context.MeasureAnchor(btpos, anchor);
	button->_posX = btpos.X - button->TZ_GetX();
	button->_posY = btpos.Y - button->TZ_GetY();
}

void ColorBorn::MeasureButtonX(float posx, Button * button, BYTE anchor_horizonal)
{
	PinePoint btpos;
	btpos = GAME()->_game_context.MeasureAnchor(posx, 0, anchor_horizonal);
	float button_fixed_x = button->GetFixX();
	button->_posX = btpos.X - button_fixed_x;
}

void ColorBorn::MeasureButtonY(float posy, Button * button, BYTE anchor_vertical)
{
	PinePoint btpos;
	btpos = GAME()->_game_context.MeasureAnchor(posy, 0, anchor_vertical);
	float button_fixed_y = button->GetFixY();
	button->_posY = btpos.Y - button_fixed_y;
}

PinePoint ColorBorn::MeasureFrame(CSprite * sprite, UINT32 frameid)
{
	float framex = sprite->GetFModuleX(frameid, 0);
	float framey = sprite->GetFModuleY(frameid, 0);
	float framew = sprite->GetFModuleWidth(frameid, 0);
	float frameh = sprite->GetFModuleHeight(frameid, 0);
	return GAME()->_game_context.MeasureDensity(framex, framey, framew, frameh);
}

void ColorBorn::MeasureAnim(CAnimObject * obj)
{
	obj->CalculateCurrentAFrame();
	int fid = obj->_anim_sprite->GetFrameIDOfAFrame(obj->_current_aframes);
	PineRectangle bound = obj->_anim_sprite->GetFmoduleBound(fid, 0);
	PinePoint anim_pos = obj->_anim_sprite->GetAFramePos(obj->_current_aframes);
	PinePoint point = GAME()->_game_context.MeasureDensity(bound.X + anim_pos.X, bound.Y + anim_pos.Y, bound.W, bound.H);
	obj->_x = obj->_x + point.X - bound.X - anim_pos.X;
	obj->_y = obj->_y + point.Y - bound.Y - anim_pos.Y;
}

PinePoint ColorBorn::MeasureFrame(CSprite * sprite, UINT32 frameid, float scalex, float scaley)
{
	float framex = sprite->GetFModuleX(frameid, 0);
	float framey = sprite->GetFModuleY(frameid, 0);
	float framew = sprite->GetFModuleWidth(frameid, 0);
	float frameh = sprite->GetFModuleHeight(frameid, 0);
	float scale = scalex > scaley ? scalex : scaley;
	PinePoint point = GAME()->_game_context.MeasureDensity(framex - framex * (scale - 1), framey - framey * (scale - 1), framew * scale, frameh * scale);
	point.X -= framex;
	point.Y -= framey;
	return point;
}

PinePoint ColorBorn::MeasureFrame(CSprite * sprite, UINT32 frameid, BYTE anchor)
{
	PineRectangle bound = sprite->GetFrameBound(frameid);
	PinePoint btpos;
	if (anchor == ANCHOR_TOP)
	{
		btpos = GAME()->_game_context.MeasureAnchor(0, bound.Y, anchor);
	}

	return btpos;
}

bool ColorBorn::PushAds(int & value_state_change)
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	bool right_rule = false;
	if (!game->_state_gameplay._user._no_ads)
	{
        printf("\ngame->_flag_show_pine_ads: %d",game->_flag_show_pine_ads);
		if (game->_flag_show_pine_ads == 0)
		{
#if defined (MAC_OS)
			printf("\nState advert %d, %d, %d", PineAdBox::showAdState, GAME()->_advert.IsAvailable(), GAME()->_advert.HasPopup());
			if (GAME()->_advert.IsAvailable() && !GAME()->_advert.HasPopup() && game->_state_gameplay._user._retry > 1 && PineAdBox::showAdState == 0 && game->_first_open_build)
			{
				game->_first_open_build = false;
				game->_pine_ads_plugin.InitAdsvert();
				game->_flag_show_pine_ads = 1;

				value_state_change = 3;
				right_rule = true;
			}
#elif defined (ANDROID_OS)
			if (game->_first_open_build && game->_state_gameplay._user._retry > 1 && _counter_game_play % 3 == 0)
			{
				game->_first_open_build = false;
				return right_rule;
			}
#endif // MAC_OS
		}
		if (game->_flag_show_pine_ads == 0 || game->_flag_show_pine_ads == 3)
		{
			if (_counter_game_play % 3 == 0)
			{
#if defined (MAC_OS)
				printf("\ngame->_state_end_game._counter_show_ads: %d", game->_counter_show_ads);
				if (game->_counter_show_ads == 0)//mot lan ads thuong
				{
					PineAdBox::SetReactiveAdvert();
					PineAdBox::ShowAdvertFullScreen();
					game->_counter_show_ads++;
					right_rule = true;
				}
				else if (game->_counter_show_ads == 1)//mot lan ads video
				{
					int adboxtype = PineAdBox::HasVideoAds();
					printf("\n %d", adboxtype);
					if (adboxtype >= 0)
					{
						PineAdBox::SetReactiveAdvert();
						PineAdBox::ShowVideoAds(adboxtype);
						game->_counter_show_ads++;
						right_rule = true;
					}
					else
					{
						PineAdBox::SetReactiveAdvert();
						PineAdBox::ShowAdvertFullScreen();
						game->_counter_show_ads++;
						right_rule = true;
					}
				}
				else if (game->_counter_show_ads >= 2 && game->_counter_show_ads <= 3) //2 lan ads thuong
				{
					PineAdBox::SetReactiveAdvert();
					PineAdBox::ShowAdvertFullScreen();
					game->_counter_show_ads++;
					right_rule = true;
				}
				else if (game->_counter_show_ads >= 4)//1lan ads video
				{
					int adboxtype = PineAdBox::HasVideoAds();
					printf("\n %d", adboxtype);
					if (adboxtype >= 0)
					{
						PineAdBox::SetReactiveAdvert();
						PineAdBox::ShowVideoAds(adboxtype);
						game->_counter_show_ads = 2;
						right_rule = true;
					}
					else
					{
						PineAdBox::SetReactiveAdvert();
						PineAdBox::ShowAdvertFullScreen();
						game->_counter_show_ads++;
						right_rule = true;
					}
				}
#elif defined (ANDROID_OS)
				if (GAME()->HasAds())
				{
					GAME()->ShowAds();
				}
#endif
			}
			value_state_change = 3;
		}
		if (game->_flag_show_pine_ads == 2 && !game->_first_open_build)
		{
			game->_flag_show_pine_ads = 3;
			value_state_change = 3;
		}
	}
	return right_rule;
}

void ColorBorn::PauseEx()
{

}

void ColorBorn::ResumeEx()
{

}

void ColorBorn::ManagerNotifi::Init()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	game->_state_gameplay._user.DataLoad();
	//24, 24, 24,24,24,24,24	
	if (game->_state_gameplay._user._state_will_notifi == 2)
	{
		INT64 time_begin = 60 * 60 * 24; //cach 24 tieng
		for (int i = 0; i < 3; i++)
		{
			sprintf(arr_notifi[i].text, "Relaxing time! Don't stress your brain anymore!");
			printf("\nTime: %lld", time_begin);
			arr_notifi[i].time = time_begin;
			if (i == 0)
			{
				time_begin += 60 * 60 * 24;  //lap lai sau 2 ngay
			}
			if (i == 1)
			{
				time_begin += 60 * 60 * (24 * 5);
			}
		}
#ifdef MAC_OS
		Device::_current_num_notification = 0;
		for (int i = 0; i < 3; i++)
		{
			printf("\nstring: %s, time: %lld", arr_notifi[i].text, arr_notifi[i].time);
			Device::AddNotification(arr_notifi[i].text, arr_notifi[i].time, false);
		}
#endif // MAC_OS
	}
}

void ColorBorn::PineAdsPlugin::UpdateAdvert()
{
#if ADD_ADVERT
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	if (GAME()->_advert.HasPopup())
	{
		GAME()->_advert.Render();
		GAME()->_advert.Update();
	}
	if (_state_app_download == 1 && CGame::_this->_advert.GetAppInstallState() == PINEADS_INSTALL_STATE_DOWNLOAD_DONE)
	{
		_state_app_download = 0;
		CGame::_this->_advert.SetDownloadCompete();
		game->_flag_show_pine_ads = 2;
	}
	if (CGame::_this->_advert.GetAppInstallState() == PINEADS_INSTALL_STATE_DOWNLOAD_CANCEL && _state_app_download == 1)
	{
		_state_app_download = 0;
		game->_flag_show_pine_ads = 2;
	}
#endif
}

void ColorBorn::PineAdsPlugin::Init()
{
	_state_app_download = 0;
}

void ColorBorn::PineAdsPlugin::InitAdsvert()
{
#if	ADD_ADVERT
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	if (GAME()->_advert.IsAvailable())
	{
		GAME()->_advert.Init();
		_state_app_download = 1;
	}
#endif
}

bool ColorBorn::PineAdsPlugin::isShowingAds()
{
#if ADD_ADVERT
	if (GAME()->_advert.HasPopup())
	{
		return true;
	}
	else
	{
		return false;
	}
#else
	return false;
#endif
}

//Kha update google services
void ColorBorn::ShowLeaderBoard()
{
	ColorBorn *game = (ColorBorn*)GAME()->_current_game;
#if ANDROID_OS
	if (GAME()->_async_task_manager._is_login_google)
	{
		PDEBUG("\nGAME()->_async_task_manager._on_process_show_leaderBoard: %d", GAME()->_async_task_manager._on_process_show_leaderBoard);
		if (!GAME()->_async_task_manager._on_process_show_leaderBoard)
		{

			//GAME()->_gameBoardScoreItem.Score = game->_hight_score;
			//GAME()->_async_task_manager.AddCommand(CAsyncTasks::enumTypeCommand::COMMAND_TYPE_ASYN_GOOGLE_PLAY_POST_SCORE);
			GAME()->_async_task_manager.AddCommand(CAsyncTasks::enumTypeCommand::COMMAND_TYPE_ASYN_GOOGLE_PLAY_SHOW_LEADERBOARD);
			GAME()->_async_task_manager._on_process_show_leaderBoard = true;
		}
	}
	else
	{
		GAME()->_async_task_manager.AddCommand(CAsyncTasks::enumTypeCommand::COMMAND_TYPE_ASYN_IS_LOG_IN_GOOGLE_PLAY);
		GAME()->_async_task_manager._is_force_login_google_play = true;
		GAME()->_async_task_manager._on_process_show_leaderBoard = true;
	}
#endif
}
void ColorBorn::SyncDriver()
{
	ColorBorn *game = (ColorBorn*)GAME()->_current_game;

#if ANDROID_OS
	if (!GAME()->_async_task_manager._on_process_sync_cloud)
	{
		game->_user.CheckLocalAndCloudSaveFile(false);
	}
#endif
}

void ColorBorn::ShowAchievement()
{
#if ANDROID_OS
	if (GAME()->_async_task_manager._is_login_google)
	{
		if (!GAME()->_async_task_manager._on_process_show_achievement)
		{
			GAME()->_async_task_manager.AddCommand(CAsyncTasks::enumTypeCommand::COMMAND_TYPE_ASYN_GOOGLE_PLAY_SHOW_ACHIEVEMENTS);
			GAME()->_async_task_manager._on_process_show_achievement = true;
		}
	}
	else
	{
		GAME()->_async_task_manager.AddCommand(CAsyncTasks::enumTypeCommand::COMMAND_TYPE_ASYN_IS_LOG_IN_GOOGLE_PLAY);
		GAME()->_async_task_manager._is_force_login_google_play = true;
		GAME()->_async_task_manager._on_process_show_achievement = true;
	}
#endif
}
void ColorBorn::SubmitAchievement(char ggPlayID_ACHIEVEMENT[])
{
#if ANDROID_OS	
	if (GAME()->_async_task_manager._is_login_google)
	{
		GAME()->_async_task_manager._need_check_unlock_achievement = true;
		PDEBUG("\n############## ggPlayID_ACHIEVEMENT gggg: %s", ggPlayID_ACHIEVEMENT);
		sprintf(GAME()->_async_task_manager._achivement_id, "%s", ggPlayID_ACHIEVEMENT);
		GAME()->_async_task_manager.AddCommand(CAsyncTasks::enumTypeCommand::COMMAND_TYPE_ASYN_GOOGLE_PLAY_UNLOCK_ACHIEVEMENT);
	}

#endif
}
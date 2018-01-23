#include "pch.h"
#include "../../../GameCore/CGame.h"
#include "../../../GameCore/Os_Functions.h"
//extern "C" void InitADManager();
//extern "C" void InitADBanner();
//extern "C" void InitTakePicture();
//extern "C" void takeAPicture();
//extern "C" void LoadImageToPngFile(const char* url,const char *file_name);
extern "C" void AuthTwitter();
extern "C" void CaptureScreenshot();
extern "C" void PostScreenToTwitter();
extern "C" void charboostShowVideoReward(const char* title);
extern "C" void ShowAdmobFullScreen();
extern "C" void OS_InitCaptureViewVideo();
extern "C" void OS_ScreenCaptureVideoStart();
extern "C" void OS_ScreenCaptureVideoStop();
extern "C" int OS_GetCaptureVideoState();
extern "C" void OS_SetCaptureVideoState(int state);
extern "C" void OS_VideoPostSocial(const char* feed);
extern "C" void OS_ShowWebPage(const char* url, bool isOffline);

#define LOGO_STATE_DEFAULT			0
#define LOGO_STATE_INIT_INFO		1
#define LOGO_STATE_CHECK_NETWORK	2	
#define LOGO_STATE_SYNC_SAVE		3	
#define LOGO_STATE_LOAD_FROM_SV		4
#define LOGO_STATE_SYNC_TO_SV		5
#define LOGO_STATE_LOAD_RES			6
#define LOGO_STATE_LOAD_SOUND		7
#define LOGO_STATE_END				100
#define LOGO_FRAME_SCROLL_PAGE			20
#define LOGO_HEIGHT_SCROLL_PAGE			(game->_screen_height)


void CGame::UnloadGameBackground()
{
	//printf("\nUnload Game Back ground");
	if (!_compete_backup_stock)
	{
		_step_force_loading = 0;
		BackupAnimStock();
		for (int i = 0; i < TOTAL_SPRITE_INGAME; i++)
		{
			if (_sprite_loaded[i])
			{
				//printf("\nUnload SpriteID = %d",i);
				UnloadSpriteVer(i);
				_sprite_loaded[i] = 1;
			}
		}
		_compete_backup_stock = true;
		printf("\nUnload background");
	}

}
bool CGame::LoadGameForceground()
{

	if (_step_force_loading >= TOTAL_SPRITE_INGAME + 10)
	{
		return true;
	}

	_compete_backup_stock = false;
	//printf("\nloading force ground = %d",_step_force_loading);
	//G()->SetColor(0);
	//G()->FillRect(0,0,k_SCREEN_WIDTH,k_SCREEN_HEIGHT);


	if (_step_force_loading >= 10)
	{
		for (int i = 0; i < 100; i++)
		{

			if (_sprite_loaded[_step_force_loading - 10])
			{
				//printf("\n_step_force_loading-10 = %d",(_step_force_loading-10));
				LoadSpriteCurrentVer(_step_force_loading - 10, _sprite_antialias_loaded[_step_force_loading - 10], _sprite_optimized_loaded[_step_force_loading - 10]);
			}
			_step_force_loading++;
			if (_step_force_loading >= TOTAL_SPRITE_INGAME + 10)
			{
				RestoreAnimStock();

				return true;
			}

		}
	}
	else
	{
		_step_force_loading++;
	}
	return false;
}

void StateLogo::InitLogo()
{
	ColorBorn *game = (ColorBorn*)GAME()->_current_game;
	game->_state_gameplay._user.DataLoad();
	game->_state_setting_credit._hud_setting_button._flag_reset_tutorial = false;
	GAME()->LoadSpriteCurrentVer(SPRITEID_FONT_LOGO);
	GAME()->LoadSpriteCurrentVer(SPRITEID_HUD_DEFAULSCREEN);
	game->_pine_ads_plugin.Init();
	game->_counter_show_ads = 0;
	GAME()->LoadMusic(BGM_ALL);
	GAME()->SetVolume(0.0f);
    _percent_volumn = 0.0f;
	game->_state_gameplay._user._retry += 1;
	if (game->_state_gameplay._user._state_will_notifi == 1)
	{
		game->_state_gameplay._user._state_will_notifi = 2;
		game->_state_gameplay._user.DataSave();
	}
	game->_counter_game_play += 1;
	GAME()->_device.AskShowNotification();
	_state = 0;
	_scroll_page_y = 0.0f;
	_acceleration_scroll.Defalt();
}

void StateLogo::RenderLogo()
{
	ColorBorn *game = (ColorBorn*)GAME()->_current_game;
#if GAME_DEBUG_LOGO
	G()->SetColor(0xffffff);
	G()->FillRect(0, 0, k_SCREEN_WIDTH, k_SCREEN_HEIGHT);
	G()->SetColor(0xffff00ff);
	G()->FillRect(Device::GetCursorViewX() - 5, Device::GetCursorViewY() - 5, 10, 10);
	//_image.DrawImageWithRect(G(),0,0);
	//printf("\n AcellX = %f", Device::GetDeviceMotionX());
	//printf("\n AcellY = %f", Device::GetDeviceMotionY());
	//printf("\n AcellZ = %f", Device::GetDeviceMotionZ());
#endif // GAME_DEBUG_LOGO
	if (_state == 1)
	{
		game->_state_gameplay.RenderGamePlay();
	}

	float draw_x = game->_point_o.X;
	float draw_y = game->_point_o.Y + _scroll_page_y;
    CMatrix4x4Util matrix_normal;
    matrix_normal.reNew();
    matrix_normal.DoScale(GAME()->_game_context.ScaleOutX, GAME()->_game_context.ScaleOutY, draw_x, draw_y);
    G()->SetTransform(matrix_normal.toPineTranform());
	GET_SPRITE(SPRITEID_HUD_DEFAULSCREEN)->DrawFrame(G(), 0, draw_x, draw_y);
    G()->ClearTransform();

	draw_x = game->_point_o.X + game->_screen_width / 2 - (375.0f - 46.0f);
	draw_y = game->_point_o.Y + game->_screen_height / 2 - (667.0f - 337.0f) + _scroll_page_y;
	GET_SPRITE(SPRITEID_HUD_DEFAULSCREEN)->DrawFrame(G(), 3, draw_x, draw_y);

	draw_x = game->_point_o.X + game->_screen_width / 2 + (384.0f - 375.0f);
	draw_y = game->_point_o.Y + game->_screen_height / 2 + (811.0f - 667.0f) + _scroll_page_y;
	GET_SPRITE(SPRITEID_HUD_DEFAULSCREEN)->DrawFrame(G(), 2, draw_x, draw_y);

	draw_x = game->_point_right_bottom.X - (750.0f - 622.0f);
	draw_y = game->_point_right_bottom.Y - (1334.0f - 1201.0f) + _scroll_page_y;
	GET_SPRITE(SPRITEID_HUD_DEFAULSCREEN)->DrawFrame(G(), 1, draw_x, draw_y);

	draw_x = game->_point_right_bottom.X - (750.0f - 660.0f);
	draw_y = game->_point_o.Y + 35.0f + _scroll_page_y;
	GET_SPRITE(SPRITEID_HUD_DEFAULSCREEN)->DrawFrame(G(), 4, draw_x, draw_y);

#ifdef _WIN32
	G()->SetColorMask(0xFF3D53FF);
	GET_SPRITE(SPRITEID_FONT_LOGO)->DrawAnsiTextFormat(G(), game->_point_o.X, game->_point_o.Y + 15, _LEFT, "%d", _loading_step);
	G()->ClearColorMask();
#endif
}

void StateLogo::UpdateLogo()
{
	ColorBorn *game = (ColorBorn*)GAME()->_current_game;
	if (game->_sub_state == k_INIT)
	{
#if GAME_DEBUG_LOGO
		Device::InitDeviceMotion(k_SCREEN_WIDTH / 2, k_SCREEN_HEIGHT / 2, k_SCREEN_WIDTH, k_SCREEN_HEIGHT);
		_image.CreateImageFromPNGinBundle(G(), "icon.png");
		//OS_InitCaptureViewVideo();
		//OS_ShowWebPage("",true);
		//_pine_social = new PineFacebookController();
		//_pine_social->Init();

		//AuthTwitter();
		//Utils::Loga("update logo init\n");
		_frame_auto_stop = 10000;
#endif // GAME_DEBUG_LOGO
#if ADD_ADVERT
		/*while(!ADVERT().IsServerProssingComplete())
		{
		;
		}
		ADVERT().SetOpen(PINE_ADVERT_SCROLL_TYPE);*/
#endif
		InitLogo();
		game->_sub_state = k_LOOP;
	}
	if (game->_sub_state == k_LOOP)
	{
#if GAME_DEBUG_LOGO
		_frame_auto_stop -= DT();
		//printf("\n AcellX = %f, AcellY = %f, AcellZ = %f", Device::GetDeviceMotionX(),Device::GetDeviceMotionY(),Device::GetDeviceMotionZ());
		for (int i = 0; i < _num_touches; i++)
		{
			if (TOUCHS(i)->_flag && TOUCHS(i)->_state == TOUCH_UP)
			{
				Device::SetCurrentBalance();
				CGame::_this->ClearAllTouch();
			}
		}
#if ADD_ADVERT
		if (!ADVERT().UpdateADVERT())
		{
		}
#endif  
#endif // GAME_DEBUG_LOGO

		switch (_loading_step)
		{
		case LOGO_STATE_DEFAULT:
			_loading_step = LOGO_STATE_INIT_INFO;
#if defined (MAC_OS)
			GAME()->_pine_social = new PineGameCenterController();
			GAME()->_pine_social->Init();
#elif defined (ANDROID_OS)
			GAME()->InitAds();
#endif

			if (game->_state_gameplay._user._is_music)
			{
				GAME()->SetVolume(0.0f);
				GAME()->PlayCurrentMusic(-1);
			}
			break;
		case LOGO_STATE_INIT_INFO:
			_loading_step = LOGO_STATE_SYNC_SAVE;
			break;
		case LOGO_STATE_SYNC_SAVE:
			_loading_step = LOGO_STATE_LOAD_FROM_SV;
			break;
		case LOGO_STATE_LOAD_FROM_SV:
			_loading_step = LOGO_STATE_SYNC_TO_SV;
			break;
		case LOGO_STATE_SYNC_TO_SV:
			_loading_step = LOGO_STATE_LOAD_RES;
			break;
		case LOGO_STATE_LOAD_RES:
			/*Load Background*/
			GAME()->LoadSpriteCurrentVer(SPRITEID_BG_INGAME, 1, true);
			GAME()->LoadSpriteCurrentVer(SPRITEID_BG_INGAME_N_COLOR, 1, false);
			/*End load*/

			/*Load Effect*/
			/*End load*/

			/*Load Font*/
			GAME()->LoadSpriteCurrentVer(SPRITEID_FONT_HUD_TEXT_INGAME, 1, false);
			GAME()->LoadSpriteCurrentVer(SPRITEID_FONT_SCORE_INGAME, 1, false);	
			GAME()->LoadSpriteCurrentVer(SPRITEID_FONT_HIGHSCORE_INGAME, 1, false);
			GAME()->LoadSpriteCurrentVer(SPRITEID_FONT_SCORE_NUMBER_INGAME, 1, false);
			/*End load*/

			/*Load HUD*/
			GAME()->LoadSpriteCurrentVer(SPRITEID_HUD_INGAME, 1, false);
			GAME()->LoadSpriteCurrentVer(SPRITEID_HUD_INGAME_TITLE, 1, true);
			GAME()->LoadSpriteCurrentVer(SPRITEID_HUD_SETTING, 1, true);
			GAME()->LoadSpriteCurrentVer(SPRITEID_HUD_INGAME_SHARE, 1, true);
			GAME()->LoadSpriteCurrentVer(SPRITEID_HUD_GAMEOVER, 1,false);
			GAME()->LoadSpriteCurrentVer(SPRITEID_HUD_RATING, 1, true);
			GAME()->LoadSpriteCurrentVer(SPRITEID_HUD_HIGHSCORE, 1, true);
			GAME()->LoadSpriteCurrentVer(SPRITEID_HUD_TUT, 1, false);
			GAME()->LoadSpriteCurrentVer(SPRITEID_HUD_TUT_I4, 1, false);
			/*End load*/


			/*Load Object*/
			GAME()->LoadSpriteCurrentVer(SPRITEID_OBJECT_01, 1, true);
			GAME()->LoadSpriteCurrentVer(SPRITEID_OBJECT_01_N_COLOR, 1, false);
			GAME()->LoadSpriteCurrentVer(SPRITEID_OBJECT_02, 1, true);
			/*End load*/




			GET_SPRITE(SPRITEID_FONT_HUD_TEXT_INGAME)->SetCharSpacing(4);
			GET_SPRITE(SPRITEID_FONT_HUD_TEXT_INGAME)->SetWordSpacing(8);
			_loading_step++;
			break;
		case LOGO_STATE_LOAD_SOUND:
			for (int i = SFX_SCORE_01; i <= SFX_SHARE; i++)
			{
				GAME()->LoadSFX(i);
			}
			_loading_step++;
			break;
		case 99:
			_loading_step++;
			break;
		case LOGO_STATE_END:
			if (_state == 0)
			{
				_state = 1;
				game->_state_gameplay.InitGamePlay();
				game->_state_gameplay.UpdateScrollPageY();
			}
			break;
		default:
			_loading_step++;
			break;
		}
		if (_state == 1)
		{
			float percent = _scroll_page_y / LOGO_HEIGHT_SCROLL_PAGE;
            printf("\npercent: %f", percent);
			_acceleration_scroll.UpdateAcceleration(_scroll_page_y, LOGO_HEIGHT_SCROLL_PAGE, 1.0f - percent, true, 1.1f, 0.8557f, 0.1f, 0.1f);
			_acceleration_scroll.UpdateAccelerationEnd(_scroll_page_y, LOGO_HEIGHT_SCROLL_PAGE, 1.0f - percent, true);
			if (_acceleration_scroll.isFinish())
			{
				_scroll_page_y = LOGO_HEIGHT_SCROLL_PAGE;
				game->SetState(k_GS_PLAYGAME);
				game->_sub_state = k_LOOP;
#ifdef MAC_OS
				if (game->_state_gameplay._hud_tutorial.CheckFinishTut())
				{
					if (!game->_state_gameplay._user._no_ads)
					{
						//PineAdBox::ShowAdmobBanner();
					}
				}
				else
				{
					//PineAdBox::CloseAdmobBanner();
				}
				PineAdBox::CloseAdmobBanner();
#endif // MAC_OS
			}
			game->_state_gameplay.UpdateScrollPageY();
            
            if (game->_state_gameplay._user._is_music)
            {
                _percent_volumn += 0.03f;
                if (_percent_volumn > 1.0f)
                {
                    _percent_volumn = 1.0f;
                }
                game->_volumn_bgm_game = (_percent_volumn * 100.0f);
                if (game->_volumn_bgm_game > 100.0f)
                {
                    game->_volumn_bgm_game = 100.0f;
                }
                GAME()->SetVolume(game->_volumn_bgm_game);
            }
        }
    }
	else if (game->_sub_state == k_DESTROY)
	{
	}
}

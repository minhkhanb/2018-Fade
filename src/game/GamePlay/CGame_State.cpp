#include "pch.h"
#include "../GameCore/CGame.h"
#include "../GameCore/Os_Functions.h"
#include <stdio.h>
#include <PineEngine.h>

PE_USING_ENGINE;

extern "C" void ServerADVERTStart();
extern "C" void PurchaseProduct(const char *indentify);
extern "C" bool isChartboostAvailable();
int StateLogo::_loading_step = -1;
void CGame::OnScreenChange(PineSize size)
{
	///////////////////////////////////////////
	// INIT CONTEXT
	///////////////////////////////////////////

	//define support version
#if defined(_WINDOWS_PHONE8)
	ResVersion support_version[] = {
		{ SupportVersion::RESVER_1280_768, Orientation::Landscape_90 },
		{ SupportVersion::RESVER_800_480, Orientation::Landscape_90 }
	};
	int support_version_num = 2;
#elif defined(_WIN8)
	ResVersion support_version[] = {
		{ SupportVersion::RESVER_1366_768, Orientation::Landscape_90 }
	};
	int support_version_num = 1;
#elif defined(MAC_OS)
	ResVersion support_version[] = {
		//{ SupportVersion::RESVER_960_640, Orientation::Landscape_90 },
		//{ SupportVersion::RESVER_1024_768, Orientation::Landscape_90 },
		//{ SupportVersion::RESVER_1136_640, Orientation::Landscape_90 },
		{ SupportVersion::RESVER_1334_750, Orientation::Portrait },
	};
	int support_version_num = 1;
#elif defined(ANDROID_OS)
	ResVersion support_version[] = {
		//{ SupportVersion::RESVER_960_640, Orientation::Landscape_90 },
		//{ SupportVersion::RESVER_1024_768, Orientation::Landscape_90 },
		//{ SupportVersion::RESVER_1136_640, Orientation::Landscape_90 },
		//{ SupportVersion::RESVER_800_480, Orientation::Landscape_90 },
		{ SupportVersion::RESVER_1334_750, Orientation::Portrait },
	};
	int support_version_num = 1;
#else //windows
	ResVersion support_version[] = {
		//{ SupportVersion::RESVER_1280_768, Orientation::Landscape_90 },
		//{ SupportVersion::RESVER_800_480, Orientation::Landscape_90 },
		//{ SupportVersion::RESVER_1366_768, Orientation::Landscape_90 },
		//{ SupportVersion::RESVER_960_640, Orientation::Landscape_90 },
		//{ SupportVersion::RESVER_1024_768, Orientation::Landscape_90 },
		//{ SupportVersion::RESVER_1136_640, Orientation::Landscape_90 }
		{ SupportVersion::RESVER_1334_750, Orientation::Portrait },
	};
	int support_version_num = 1;
#endif
	//detect device version
 //   {
 //       ResVersion device_support_version[] = {
 //           { SupportVersion::RESVER_960_640, Orientation::Landscape_90 },
 //           { SupportVersion::RESVER_1024_768, Orientation::Landscape_90 },
 //           { SupportVersion::RESVER_1136_640, Orientation::Landscape_90 },
 //           { SupportVersion::RESVER_800_480, Orientation::Landscape_90 },
 //       };
 //       PineSize dvsize = { _device.ScreenSize.W, _device.ScreenSize.H };
 //       _device._version = (GetAppropriateVersion(dvsize, device_support_version, 4)).Version;
 //   }
	//if (support_version_num > 0){
	//	PineSize dvsize = { _device.ScreenSize.W, _device.ScreenSize.H };
	//	ResVersion curr_ver = GetAppropriateVersion(dvsize, support_version, support_version_num);
	//	Alignment game_align = { HorizontalAlign::Center, VerticalAlign::Middle };
	//	AlignmentContext(game_align, dvsize, curr_ver, true, 0);

	//	switch (curr_ver.Version)
	//	{
	//	case SupportVersion::RESVER_800_480:
	//		//_current_version = VERSION_480x800;
	//		break;
	//	case SupportVersion::RESVER_960_640:
	//		_current_version = VERSION_640x960;
	//		break;
	//	case SupportVersion::RESVER_1024_768:
	//		//_current_version = VERSION_768x1024;
	//		break;
	//	case SupportVersion::RESVER_1136_640:
	//		//_current_version = VERSION_750x1334;
	//		break;
	//	case SupportVersion::RESVER_1366_768:
	//		//_current_version = VERSION_1366x768;
	//		break;
	//	}
	//}
	if (support_version_num > 0) {
		PineSize dvsize = { _device.ScreenSize.W, _device.ScreenSize.H };
		ResVersion curr_ver = GetAppropriateVersion(dvsize, support_version, support_version_num);
		Alignment game_align = { HorizontalAlign::Center, VerticalAlign::Middle };
		AlignmentContext(game_align, dvsize, curr_ver, true, _HCENTER);

		_current_version = VERSION_750x1334;
	}
}
void CGame::InitEx()
{
#ifdef MAC_OS
	PineAdBox::InitAdmobBanner();
#endif // MAC_OS
	InitBuff(UNZIP_BUFFER_LENGTH_HIGH);

	_GameState = k_GS_LOGO;
	_GameSubState = k_INIT;
#ifdef MAC_OS
#if ADD_ADVERT
	ServerADVERTStart();
#endif
#endif
	_main_game = new ColorBorn();
	_main_game->Init();
	_main_game->SetState(k_GS_LOGO);
	_main_game->_game_id = APPLE_ID;
	_current_game = _main_game;
	setUseOptimizeDrawModule(true);
#if !defined (MAC_OS)
	_isBackkeyPress = false;
	_waitForProcessBackkeyCount = 0;
#endif
}

void CGame::ReleaseEx()
{

}

void CGame::PauseEx()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	if (game->_flag_check_ready_rate == 2)
	{
		game->_time_cool_down_check_rate = time(NULL);
	}
}
void CGame::ResumeEx()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	if (game->_flag_check_ready_rate == 2)
	{
		/*UINT64 time_now = time(NULL);
		INT64 second = time_now - game->_time_cool_down_check_rate;
		printf("\nsecond: %lld", second);
		if (second >= 3)
		{
			game->_flag_check_ready_rate = 1;
			game->_state_gameplay._user._push_rating = false;
			//game->_state_gameplay._user.DataSave();
		}
		else
		{
			game->_flag_check_ready_rate = 1;
		}*/
		game->_flag_check_ready_rate = 1;
	}
	if (game->_state_gameplay._user._state_will_notifi == 1)
	{
		game->_state_gameplay._user._state_will_notifi = 2;
		game->_state_gameplay._user.DataSave();
	}
#ifdef MAC_OS
	PineAdBox::InitAdmobBanner();
#endif // MAC_OS
}
bool CGame::OnBackKeyPress() {
	//Implement function when 
#if !defined (MAC_OS)
	CGame::_this->_isBackkeyPress = true;
	CGame::_this->_waitForProcessBackkeyCount = 0;
	return true;
#else
	return false;
#endif
}
void CGame::UpdateAndRender()
{
	_main_game->UpdateAndRender();
#if !defined (MAC_OS)
	if (CGame::_this->_isBackkeyPress)
	{
		if (CGame::_this->_waitForProcessBackkeyCount >= 1)
		{
			CGame::_this->_isBackkeyPress = false;
			CGame::_this->_waitForProcessBackkeyCount = 0;
			OS_Exit(false);
		}
		else
		{
			CGame::_this->_waitForProcessBackkeyCount++;
		}
	}
#if defined (ANDROID_OS)
	UpdateAds();
	_async_task_manager.Run();
#endif
#endif
}



void CGame::UpdateTouch(int xx, int yy, int touch_state, int touch_id, int tap_count)
{
	/*switch (_GameState)
	{

	}*/
}

#if defined(_WINDOWS)
void CGame::ProcessCommandLine(const char* cmd)
{

}
#endif

void CGame::PurchaseIAP(const char* strID, enumIAPResponseStatus sucessed)
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	printf("\n IAP id = %s, success = %d ", strID, sucessed);
	if (sucessed == enumIAPResponseStatus::IAP_RESPONSE_STATUS_SUCCESS || sucessed == enumIAPResponseStatus::IAP_RESPONSE_STATUS_SUCCESS_RESTORE)
	{
		if (strcmp("fade_NoAds", strID) == 0)
		{
			game->_state_gameplay._user._no_ads = true;
			game->_state_gameplay._user.DataSave();
			//turn off hud loading
			game->_state_gameplay._hud_loading._state = 2;
#ifdef MAC_OS
			PineAdBox::CloseAdmobBanner();
#endif // MAC_OS
			game->_state_gameplay._hud_ingame._button_arr[2]._state = BUTTON_STATE_HIDE;
		}
	}
	else if (sucessed == enumIAPResponseStatus::IAP_RESPONSE_STATUS_FAIL)
	{
		//turn off hud loading
		game->_state_gameplay._hud_loading._state = 2;
	}
	else if (sucessed == enumIAPResponseStatus::IAP_RESPONSE_STATUS_END_RESTORE)
	{
		char message[512];
		sprintf(message, "Your purchases have been restored.");
#if defined(MAC_OS)
		_pine_social->ShowMessageBox(message, "Restored");
#endif
		//turn off hud loading
		game->_state_gameplay._hud_loading._state = 2;
	}
	else if (sucessed == enumIAPResponseStatus::IAP_RESPONSE_STATUS_FAIL_RESTORE)
	{
		//turn off hud loading
		game->_state_gameplay._hud_loading._state = 2;
	}
}

void callback(ECloudKeyValueChangeReason reason, std::vector<std::string> keys)
{
	switch (reason)
	{
	case ECloudKeyValueChangeReason::AccountChange:
		PDEBUG("ICloud Change reason Account Change\n");
		GAME()->_icloud_state = 1;
		break;
	case ECloudKeyValueChangeReason::InitialSyncChange:
		PDEBUG("ICloud Change reason InitialSyncChange\n");
		GAME()->_icloud_state = 2;
		break;
	case ECloudKeyValueChangeReason::QuotaViolationChange:
		PDEBUG("ICloud Change reason QuotaViolationChange\n");
		GAME()->_icloud_state = 3;
		break;
	case ECloudKeyValueChangeReason::ServerChange:
		PDEBUG("ICloud Change reason ServerChange\n");
		GAME()->_icloud_state = 4;
		break;
	}

	for (int i = 0; i < keys.size(); i++)
	{
		PDEBUG("key change:%s\n", keys[i].c_str());
	}
}

void CGame::CheckICloud()
{
	ColorBorn *game = (ColorBorn*)GAME()->_current_game;
#if defined(MAC_OS)
	std::shared_ptr<CCloudKeyValueService> service = CCloud::regKeyValueService(ECloudProvider::AppleICloud, &callback);

	if (service == nullptr)
	{
		PDEBUG("icloud fail \n");
	}
	else {
		PDEBUG("icloud success\n");
		//if (_icloud_state == 0) {
		service->synchronize();
		int server_state = CheckCanPushDataSave();
		printf("\nserver_state: %d", server_state);
		if (server_state == ICLOUD_STATE_NEW_VERSION) {
			LoadFromICloud();
			game->_state_gameplay._user.CheckVersion();
			game->_state_gameplay._user.DataSave();
		}
	}
	//}
#endif
}

int CGame::CheckCanPushDataSave()
{
	ColorBorn *game = (ColorBorn*)GAME()->_current_game;
#if defined(MAC_OS)
	int state = -10;
	if (!_device.IsNetworkAvailable())
	{
		state = ICLOUD_STATE_DISCONECT;
	}
	else
	{
		std::shared_ptr<CCloudKeyValueService> service = CCloud::regKeyValueService(ECloudProvider::AppleICloud, &callback);
		if (service == nullptr)
		{
			PDEBUG("icloud fail \n");
		}
		else {
			PDEBUG("icloud success\n");
			//if (_icloud_state == 0) {
			service->synchronize();
			std::vector<BYTE> data = service->readBytes("data");
			if (data.size() > 0)
			{
				//if (_icloud_state == 0) {
				service->synchronize();
				std::vector<BYTE> data = service->readBytes("data");
				if (data.size() > 0)
				{
					char buffer[SAVE_MAX_BUFFER];
					sprintf(buffer, "");
					for (int i = 0; i < SAVE_FORMAT_LENGTH; i++)
					{
						buffer[i] = data[i];
					}
					int time = 0;
					time = GAME()->GetInt32At(buffer, SAVE_FORMAT_RETRY);
					int ver = GAME()->GetInt64At(buffer, SAVE_FORMAT_CURRENT_VERSION);
					if (time < game->_state_gameplay._user._retry)
					{
						state = ICLOUD_STATE_OLD_VERSION;
					}
					else if (time == game->_state_gameplay._user._retry)
					{
						state = ICLOUD_STATE_READY_SYNS;
					}
					else if (time > game->_state_gameplay._user._retry)
					{
						state = ICLOUD_STATE_NEW_VERSION;
					}
					if (ver < SAVE_CURRENT_VERSION)
					{
						state = ICLOUD_STATE_OLD_VERSION;
					}
				}
				//}
			}
			else
			{
				state = ICLOUD_STATE_NODATA;
			}
			//}
		}
	}
	return state;
#else
	return -10;
#endif
}

void CGame::ResetValueICloud()
{
	ColorBorn *game = (ColorBorn*)GAME()->_current_game;
#if defined(MAC_OS)
	std::shared_ptr<CCloudKeyValueService> service = CCloud::regKeyValueService(ECloudProvider::AppleICloud, &callback);

	if (service == nullptr)
	{
		PDEBUG("icloud fail \n");
	}
	else {
		PDEBUG("icloud success\n");
		if (_icloud_state == 0) {
			service->synchronize();
			std::vector<BYTE> data = service->readBytes("data");
			{
				game->_state_gameplay._user.UserDefautl();
				game->_state_gameplay._user.SaveToBuffer();
				service->write("data", game->_state_gameplay._user._buffer, SAVE_FORMAT_LENGTH);
				PDEBUG("\n\nicloud write data success\n\n");
			}
		}
	}
#endif
}

void CGame::SaveToICloud()
{
#if defined(MAC_OS)
	ColorBorn *game = (ColorBorn*)GAME()->_current_game;
	std::shared_ptr<CCloudKeyValueService> service = CCloud::regKeyValueService(ECloudProvider::AppleICloud, &callback);

	if (service == nullptr)
	{
		PDEBUG("icloud fail \n");
	}
	else {
		PDEBUG("icloud success\n");
		//if (_icloud_state == 0) {
		service->synchronize();
		int server_state = CheckCanPushDataSave();
		if (server_state == ICLOUD_STATE_READY_SYNS || server_state == ICLOUD_STATE_OLD_VERSION ||
			server_state == ICLOUD_STATE_NODATA)
		{
			game->_state_gameplay._user.SaveToBuffer();
			service->write("data", game->_state_gameplay._user._buffer, SAVE_FORMAT_LENGTH);
			PDEBUG("\n\nicloud write data success\n\n");
		}

		/*std::vector<BYTE> bytes = { 1,2,3,4,5 };

		if (service->write("test", (const char*)bytes.data(), bytes.size()))
		{
		PDEBUG("icloud write data success\n");
		std::vector<BYTE> data = service->readBytes("test");

		for (int i = 0; i< data.size(); i++)
		{
		PDEBUG("data: %d %d\n", i, data[i]);
		}
		}
		else {
		PDEBUG("icloud write data fail\n");
		}*/
		//}
	}
#endif
}

void CGame::RewriteToICloud()
{
	ColorBorn *game = (ColorBorn*)GAME()->_current_game;
#if defined(MAC_OS)
	std::shared_ptr<CCloudKeyValueService> service = CCloud::regKeyValueService(ECloudProvider::AppleICloud, &callback);

	if (service == nullptr)
	{
		PDEBUG("icloud fail \n");
	}
	else {
		PDEBUG("icloud success\n");
		game->_state_gameplay._user.SaveToBuffer();
		service->write("data", game->_state_gameplay._user._buffer, SAVE_FORMAT_LENGTH);
		PDEBUG("\n\nicloud rewrite data success\n\n");
	}
#endif
}

void CGame::DefaultICloud()
{
	ColorBorn *game = (ColorBorn*)GAME()->_current_game;
#if defined(MAC_OS)
	std::shared_ptr<CCloudKeyValueService> service = CCloud::regKeyValueService(ECloudProvider::AppleICloud, &callback);

	if (service == nullptr)
	{
		PDEBUG("icloud fail \n");
	}
	else {
		PDEBUG("icloud success\n");
		//if (_icloud_state == 0) {
		service->synchronize();
		std::vector<BYTE> data = service->readBytes("data");
		if (data.size() > 0) {
			PDEBUG("\n\nicloud read data success\n\n");
			for (int i = 0; i < SAVE_FORMAT_LENGTH; i++)
			{
				game->_state_gameplay._user._buffer[i] = data[i];
			}
			game->_state_gameplay._user.LoadFromBuffer();
		}
		else
		{
			game->_state_gameplay._user.SaveToBuffer();
			service->write("data", game->_state_gameplay._user._buffer, SAVE_FORMAT_LENGTH);
			PDEBUG("\n\nicloud write data success\n\n");
		}
		//}
	}
#endif
}

void CGame::LoadFromICloud()
{
	ColorBorn *game = (ColorBorn*)GAME()->_current_game;
#if defined(MAC_OS)
	std::shared_ptr<CCloudKeyValueService> service = CCloud::regKeyValueService(ECloudProvider::AppleICloud, &callback);

	if (service == nullptr)
	{
		PDEBUG("icloud fail \n");
	}
	else {
		PDEBUG("icloud success\n");
		//if (_icloud_state == 0) {
		service->synchronize();
		std::vector<BYTE> data = service->readBytes("data");
		if (data.size() > 0) {
			PDEBUG("\n\nicloud read data success\n\n");
			for (int i = 0; i < SAVE_FORMAT_LENGTH; i++)
			{
				game->_state_gameplay._user._buffer[i] = data[i];
			}
			game->_state_gameplay._user.LoadFromBuffer();
			printf("\n_version_get_from_cloud: %lld", game->_state_gameplay._user._version);
		}

		/*std::vector<BYTE> bytes = { 1,2,3,4,5 };

		if (service->write("test", (const char*)bytes.data(), bytes.size()))
		{
		PDEBUG("icloud write data success\n");
		std::vector<BYTE> data = service->readBytes("test");

		for (int i = 0; i< data.size(); i++)
		{
		PDEBUG("data: %d %d\n", i, data[i]);
		}
		}
		else {
		PDEBUG("icloud write data fail\n");
		}*/
		//}
	}
#endif
}

#if defined (ANDROID_OS)
bool CGame::HasAds()
{
	return _admob.isInterstitialReady()
		|| _unityads.isVideoReady();
}

bool CGame::HasVideoAds()
{
	return _admob.isInterstitialReady()
		|| _unityads.isVideoReady();

}

bool CGame::HasBannerAds()
{
	return _admob.isBannerReady();
}

bool CGame::InitAds()
{
	PDEBUG("InitAds\n");
	_show_ads_count = 0;
	_show_unity_video_ads_count = 0;
	_time_first_show_unity_video_ads = 0;
	_admob.prepareInterstitial();
	_admob.prepareBanner();
	_unityads.prepareVideo();
	return true;
}

void CGame::ShowAds()
{
	_show_ads_count++;
	//if (_adsVungle.isReady())
	{
		//PDEBUG("SHOW vungle ads");
		//_adsVungle.show();
	}
	//else 
	if (_show_ads_count <= 4)
	{
		if (_admob.isInterstitialReady())
		{
			PDEBUG("SHOW _admob showInterstitial");
			_admob.showInterstitial();
		}
	}
	else
	{
		_show_ads_count = 0;
		//if (_unityads.isAdsReady())
		{
			//PDEBUG("SHOW UNITY ADS");
			//_unityads.showAds();
		}
		//else if (_show_unity_video_ads_count < 3 && _time_first_show_unity_video_ads - GetTime() < 30 * 60 * 1000
		//&& _unityads.isVideoReady())
		{
			//PDEBUG("SHOW UNITY VIDEO");
			//_unityads.showVideo();
			//if (_show_unity_video_ads_count == 0)
			//{
			//_time_first_show_unity_video_ads = GetTime();
			//}
			//_show_unity_video_ads_count++;
		}
		//else if (_chartboost.hasRewardedVideo())
		{
			//PDEBUG("SHOW _chartboost video");
			//_chartboost.showRewardedVideo();
		}
		//else if (_chartboost.hasInterstitial())
		{
			//PDEBUG("SHOW _chartboost ads");
			//_chartboost.showInterstitial();
		}
		/*if (_unityads.isVideoReady())
		{
			_unityads.showVideo();
			_show_ads_count = 0;
		}
		else */if (_admob.isInterstitialReady())
		{
			PDEBUG("SHOW _admob showInterstitial");
			_admob.showInterstitial();
		}
	}
}

void CGame::ShowBannerAds()
{
	if (_admob.isBannerReady() && !_admob.isShowBanner())
	{
		PDEBUG("SHOW _admob banner");
		_admob.showBanner();
	}
}

void CGame::HideBannerAds()
{
	_admob.hideBanner();
}

void CGame::ShowVideoAds()
{
	if (_unityads.isVideoReady())
	{
		_unityads.showVideo();
		_show_ads_count = 0;
	}
	else
	{
		if (_admob.isInterstitialReady())
		{
			PDEBUG("SHOW _admob showInterstitial");
			_admob.showInterstitial();
			if (_is_waiting_for_reward)
			{
				_on_video_ads_reward = true;
			}
		}
	}

}

void CGame::UpdateAds()
{
	if (OS_IsNetworkAvailable())
	{
		//_adsVungle.update();
		_admob.update();
		//_chartboost.update();

		/*PineUnityAdsAsync::enumUnityAdsUpdateResult result = _unityads.update();
		switch (result)
		{
		case PineUnityAdsAsync::enumUnityAdsUpdateResult::SHOW_VIDEO_SUCCESS:
			if (_is_waiting_for_reward)
			{
				_on_video_ads_reward = true;
			}
			break;
		case PineUnityAdsAsync::enumUnityAdsUpdateResult::SHOW_VIDEO_FAIL:
			_is_waiting_for_reward = false;
			break;
		default:
			break;
		}*/
		/*if (!HasAds() && GetTime() - _time_start_wait_for_reinit_ads >= TIME_WAIT_FOR_REINIT_ADS)
		{
			_admob.prepareInterstitial();
			_time_start_wait_for_reinit_ads = GetTime();
		}*/
		if (!HasBannerAds() && GetTime() - _time_start_wait_for_reinit_ads >= TIME_WAIT_FOR_REINIT_ADS)
		{
			PDEBUG("CALL INIT BANNER ADS\n");
			_admob.prepareBanner();
			_time_start_wait_for_reinit_ads = GetTime();
		}
	}
}
#endif

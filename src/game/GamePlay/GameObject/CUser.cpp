#include "pch.h"
#include "../../GameCore/CGame.h"
#include "../../GameCore/Os_Functions.h"
#include "CUser.h"


CUser::CUser()
{
}

CUser::~CUser()
{
}
void CUser::SetUserName(const char name)
{
	sprintf(_userName, "%s", name);
}
void CUser::SetUserID(UINT64 ID)
{
	_userID = ID;
}
void CUser::SetUserGCID(UINT64 GC_ID)
{
	_user_GCID = GC_ID;
}
void CUser::SetUserFBID(UINT64 FB_ID)
{
	_user_FBID = FB_ID;
}
void CUser::SetUserTWID(UINT64 TW_ID)
{
	_user_TWID = TW_ID;
}
UINT64 CUser::GetUserID()
{
	return _userID;
}
UINT64 CUser::GetUserGCID()
{
	return _user_GCID;
}
UINT64 CUser::GetUserFBID()
{
	return _user_FBID;
}
UINT64 CUser::GetUserTWID()
{
	return _user_TWID;
}

void CUser::UserInitInfo()
{
	_userID = 0;
	_user_GCID = 0;
	_user_FBID = 0;
	_user_TWID = 0;
	sprintf(_userName, "Your Name");
}

void CUser::DataSave(bool rewrite)
{
	//return;
	SaveToBuffer();

#if defined(MAC_OS) || defined(_WINDOWS_PHONE8) || defined(ANDROID_OS)
	OS_SaveAppData(SAVE_FILE_NAME, _buffer, MAX_SAVE_BUFFER_CACHE, false);
#else

	FILE * stream = NULL;

	stream = fopen(SAVE_FILE_NAME, "wb");

	if (stream != NULL)
	{
		fwrite((void *)_buffer, sizeof(BYTE), MAX_SAVE_BUFFER_CACHE, stream);
	}

	if (stream != NULL)
	{
		fclose(stream);
	}
#endif
	if (!rewrite)
	{
		printf("\nSave to icloud");
		GAME()->SaveToICloud();
	}
	else
	{
		printf("\nReset icloud");
		GAME()->ResetValueICloud();
	}
}

void CUser::CheckVersion()
{
	ColorBorn *game = (ColorBorn*)GAME()->_current_game;
	if (_version < SAVE_CURRENT_VERSION)
	{
		//xu ly syn server
		if (_version == 0)
		{
			_state_will_notifi = 0;
		}
		/*if (_version == 6)
		{
			game->_achievement_manager.SetDefaultValue();
			GAME()->RewriteToICloud();
		}*/
	}
}

void CUser::DataLoad()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	int saved = 0;
	Buffer* buff = OS_LoadAppData(SAVE_FILE_NAME);
	if (buff != NULL)
	{
		saved = buff->Length();
		memcpy(_buffer, buff->Data(), saved);
		delete buff;
	}
	if (saved == 0)
	{
		UserDefautl();
		GAME()->DefaultICloud();
		printf("\n_version_get_from_cloud: %lld", _version);
		CheckVersion();
		DataSave();
	}
	else
	{
		LoadFromBuffer();
		if (game->_current_state == k_GS_LOGO) {
			GAME()->CheckICloud();
			printf("\n_version_get_from_cloud: %lld", _version);
			//GAME()->ResetValueICloud();
		}
		if (_version < SAVE_CURRENT_VERSION)
		{
			//xu ly syn server
			CheckVersion();
			DataSave();
		}
	}
}

void CUser::SetFlagControlMusicSoundNotifiGame()
{
	if (_is_music)
	{
		GAME()->_musicEnable = true;
	}
	else
	{
		GAME()->_musicEnable = false;
	}
	if (_is_sound)
	{
		GAME()->_soundEnable = true;
	}
	else
	{
		GAME()->_soundEnable = false;
	}
	if (_is_notifi)
	{
		GAME()->_notificationEnable = true;
	}
	else
	{
		GAME()->_notificationEnable = false;
	}
}


void CUser::UserDefautl()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	_is_sound = true;
	_is_music = true;
	_is_notifi = true;
	UserInitInfo();
	_version = 0;
	_best_score = 0;
	_retry = 0;
	_push_rating = true;
	_no_ads = false;
	_finish_tut = false;
	_state_will_notifi = 0;
}

void CUser::SaveToBuffer()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	GAME()->SetInt64At(_buffer, SAVE_FORMAT_CURRENT_VERSION, SAVE_CURRENT_VERSION);
	GAME()->SetInt64At(_buffer, SAVE_FORMAT_USER_ID, _userID);
	GAME()->SetInt64At(_buffer, SAVE_FORMAT_USER_GCID, _user_GCID);
	GAME()->SetInt64At(_buffer, SAVE_FORMAT_USER_FBID, _user_FBID);
	GAME()->SetInt64At(_buffer, SAVE_FORMAT_USER_TWID, _user_TWID);
	GAME()->SetByteAt(_buffer, SAVE_FORMAT_MUSIC_ENABLE, _is_music);
	GAME()->SetByteAt(_buffer, SAVE_FORMAT_SOUND_ENABLE, _is_sound);
	GAME()->SetByteAt(_buffer, SAVE_FORMAT_NOTIFI_ENABLE, _is_notifi);
	for (int i = 0; i < 256; i++)
	{
		GAME()->SetByteAt(_buffer, SAVE_FORMAT_USER_NAME + i, _userName[i]);
	}
	GAME()->SetInt64At(_buffer, SAVE_FORMAT_BEST_SCORE, _best_score);
	GAME()->SetInt32At(_buffer, SAVE_FORMAT_RETRY, _retry);
	GAME()->SetByteAt(_buffer, SAVE_FORMAT_PUSH_RATTING, _push_rating);
	GAME()->SetByteAt(_buffer, SAVE_FORMAT_NO_ADS, _no_ads);
	GAME()->SetByteAt(_buffer, SAVE_FORMAT_FINISH_TUT, _finish_tut);
	GAME()->SetInt32At(_buffer, SAVE_FORMAT_STATE_NOTIFI, _state_will_notifi);
}

void CUser::LoadFromBuffer()
{
	ColorBorn *game = (ColorBorn*)GAME()->_current_game;
	_version = GAME()->GetInt64At(_buffer, SAVE_FORMAT_CURRENT_VERSION);
	_userID = GAME()->GetInt64At(_buffer, SAVE_FORMAT_USER_ID);
	_user_GCID = GAME()->GetInt64At(_buffer, SAVE_FORMAT_USER_GCID);
	_user_FBID = GAME()->GetInt64At(_buffer, SAVE_FORMAT_USER_FBID);
	_user_TWID = GAME()->GetInt64At(_buffer, SAVE_FORMAT_USER_TWID);
	_is_music = GAME()->GetByteAt(_buffer, SAVE_FORMAT_MUSIC_ENABLE);
	_is_sound = GAME()->GetByteAt(_buffer, SAVE_FORMAT_SOUND_ENABLE);
	_is_notifi = GAME()->GetByteAt(_buffer, SAVE_FORMAT_NOTIFI_ENABLE);
	for (int i = 0; i < 256; i++)
	{
		_userName[i] = GAME()->GetByteAt(_buffer, SAVE_FORMAT_USER_NAME + i);
	}
	_best_score = GAME()->GetInt64At(_buffer, SAVE_FORMAT_BEST_SCORE);
	_retry = GAME()->GetInt32At(_buffer, SAVE_FORMAT_RETRY);
	_push_rating = GAME()->GetByteAt(_buffer, SAVE_FORMAT_PUSH_RATTING);
	_no_ads = GAME()->GetByteAt(_buffer, SAVE_FORMAT_NO_ADS);
	_finish_tut = GAME()->GetByteAt(_buffer, SAVE_FORMAT_FINISH_TUT);
	_state_will_notifi = GAME()->GetInt32At(_buffer, SAVE_FORMAT_STATE_NOTIFI);
	if (_no_ads)
	{
		printf("\n Da mua iap");
	}
	else
	{
		printf("\n Chua mua iap");
	}
	if (_push_rating)
	{
		printf("\n Chua rating");
	}
	else
	{
		printf("\n Da rating");
	}
	if (_finish_tut)
	{
		printf("\n Da finish tut");
	}
	else
	{
		printf("\n Chua finish tut");
	}

	if (_state_will_notifi == 0)
	{
		printf("\n Chua notifi");
	}
	if (_state_will_notifi == 1)
	{
		printf("\n Chuan bi notifi, cho dang nhap lai");
	}
	if (_state_will_notifi == 2)
	{
		printf("\n Bat dau notifi");
	}
}

void CUser::SetFloatAt(char* buffer, int offset, float value)
{
	float data = value;
	memcpy(buffer + offset, &data, 4);
}

float CUser::GetFloatAt(char* buffer, int offset)
{
	float value = 0;
	memcpy(&value, buffer + offset, 4);
	return value;
}

#if defined (ANDROID_OS)
void CUser::CheckLocalAndCloudSaveFile()
{
	if (!Device::IsNetworkAvailable())
	{
		OS_ShowMessageBox("Error!", "Connection is not available!");
		return;
	}
	if (!GAME()->_async_task_manager._is_login_google)
	{
		GAME()->_async_task_manager.AddCommand(CAsyncTasks::enumTypeCommand::COMMAND_TYPE_ASYN_IS_LOG_IN_GOOGLE_PLAY);
		GAME()->_async_task_manager._is_force_login_google_play = true;
		GAME()->_async_task_manager._on_process_sync_cloud = true;
		return;
	}
	Buffer * buff = OS_LoadAppData(CLOUD_SAVE_FILE_NAME);
	if (buff != NULL)
	{
		char* server_buff = (char*)buff->Data();
		GAME()->_async_task_manager._on_process_sync_cloud = true;

		int time = GAME()->GetInt32At(server_buff, SAVE_FORMAT_RETRY);
		int ver = GAME()->GetInt64At(server_buff, SAVE_FORMAT_CURRENT_VERSION);
		PDEBUG("\n #icloud save_version = %d, numPlay = %d", ver, time);
		if (time < _retry)
		{
			ConfirmSyncSaveToCloud();
		}
		else if (time == _retry)
		{
			OS_ShowMessageBox("Congratulations!", "Your data has been saved!");
			GAME()->_async_task_manager._on_process_sync_cloud = false;
		}
		else if (time > _retry)
		{
			ConfirmSyncSaveFromCloud();
		}
		if (ver < SAVE_CURRENT_VERSION)
		{
			ConfirmSyncSaveToCloud();
		}

		buff->Release();
	}
	else
	{
		ConfirmSyncSaveToCloud();
	}
}

void CUser::UpdateCloudSaveFile()
{
	PDEBUG("UpdateCloudSaveFile with local");
	OS_SaveAppData(CLOUD_SAVE_FILE_NAME, _buffer, MAX_SAVE_BUFFER_CACHE, false);
}

void CUser::UpdateLocalSaveFile(Buffer* buffer)
{
	PDEBUG("UpdateLocalSaveFile with cloud");
	memcpy(_buffer, buffer->Data(), SAVE_FORMAT_END);
	LoadFromBuffer();
	SaveToBuffer();
	/*int level = GAME()->GetInt16At(_buffer, SAVE_FORMAT_GAME_LEVEL);
	if (level >= MAX_ACHIEVEMENT - 1) level = MAX_ACHIEVEMENT - 1;
	for (int i = 0; i <= level; i++)
	{
		GAME()->_async_task_manager._list_id_group_achievement_need_check_unlock[i] = true;
	}
	if (level > 0)
	{
		GAME()->_async_task_manager.AddCommand(CAsyncTasks::enumTypeCommand::COMMAND_TYPE_ASYN_GOOGLE_PLAY_UNLOCK_ACHIEVEMENT);
	}
	OS_SaveAppData(SAVE_FILE_NAME, _buffer, MAX_SAVE_BUFFER_CACHE, false);
	ColorBorn* game = (ColorBorn*)(GAME()->_current_game);
	game->SetState(k_GS_MAIN_MENU);*/
}

void CUser::ConfirmSyncSaveToCloud()
{
	sprintf(GAME()->_async_task_manager._message_box_title, "%s", "Google Drive sync");
	sprintf(GAME()->_async_task_manager._message_box_message, "%s", "Do you want to safeguard your progress to Google Drive?");
	GAME()->_async_task_manager._message_box_confirm_type = CAsyncTasks::enumCloudSaveConfirmType::USE_SAVE_FROM_LOCAL;
	GAME()->_async_task_manager._on_process_sync_cloud = true;
	GAME()->_async_task_manager.AddCommand(CAsyncTasks::enumTypeCommand::COMMAND_TYPE_ASYN_SHOW_MESSAGE_BOX);
}

void CUser::ConfirmSyncSaveFromCloud()
{
	sprintf(GAME()->_async_task_manager._message_box_title, "%s", "Google Drive backup");
	sprintf(GAME()->_async_task_manager._message_box_message, "%s", "Do you want to play with your latest Google Drive Backup?");
	GAME()->_async_task_manager._message_box_confirm_type = CAsyncTasks::enumCloudSaveConfirmType::USE_SAVE_FROM_CLOUD;
	GAME()->_async_task_manager._on_process_sync_cloud = true;
	GAME()->_async_task_manager.AddCommand(CAsyncTasks::enumTypeCommand::COMMAND_TYPE_ASYN_SHOW_MESSAGE_BOX);
}
#endif
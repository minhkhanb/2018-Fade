#ifndef _CASYNC_TASKS_H
#define _CASYNC_TASKS_H

#include "../../Lib/PineSocialAsync.h"
#define MAX_COMMAND		10
#define MAX_ACHIEVEMENT	11

class  CAsyncTasks
{
public:
	CAsyncTasks()
	{
#if defined (ANDROID_OS)
		_is_login_google = false;
#endif
		for (int i = 0; i < MAX_COMMAND; i++)
		{
			_command[i]._typeCommand = enumTypeCommand::COMMAND_TYPE_NONE;
			_command[i]._stateCommand = enumStateCommand::COMMAND_STATE_NONE;
		}
	};

	enum enumTypeCommand
	{
		COMMAND_TYPE_NONE
        ,COMMAND_TYPE_ASYNC_CHECK_NETWORK_STATUS
#if defined(ANDROID_OS)
		,COMMAND_TYPE_ASYN_LOAD_IAP
		,COMMAND_TYPE_ASYN_RESTORE_PURCHASE
		,COMMAND_TYPE_ASYN_LOG_IN_GOOGLE_PLAY
		,COMMAND_TYPE_ASYN_IS_LOG_IN_GOOGLE_PLAY
		,COMMAND_TYPE_ASYN_GOOGLE_PLAY_POST_SCORE
		,COMMAND_TYPE_ASYN_GOOGLE_PLAY_SHOW_LEADERBOARD
		,COMMAND_TYPE_ASYN_GOOGLE_PLAY_SHOW_ACHIEVEMENTS
		,COMMAND_TYPE_ASYN_GOOGLE_PLAY_UNLOCK_ACHIEVEMENT
		,COMMAND_TYPE_ASYN_UPDATE_CLOUND_SAVE
		,COMMAND_TYPE_ASYN_TAKE_SCREEN_SHOT
		,COMMAND_TYPE_ASYN_SHARE_SCREEN_SHOT_INTENT
		,COMMAND_TYPE_ASYN_SEND_EMAIL_INTENT
		,COMMAND_TYPE_ASYN_SHOW_MESSAGE_BOX
		,COMMAND_TYPE_ASYN_GOOGLE_PLUS_POST
		,COMMAND_TYPE_ASYN_GOOGLE_PLUS_POST_SCREEN
#elif defined (_WINDOWS_PHONE8)
		, COMMAND_TYPE_ASYN_SHARE_LINK
		, COMMAND_TYPE_ASYN_SHARE_MEDIA
#endif
	};

	enum enumStateCommand
	{
		COMMAND_STATE_NONE,
		COMMAND_STATE_INIT,
		COMMAND_STATE_PROCESSING,
	};

	enum enumCloudSaveConfirmType
	{
		CONFIRM_TYPE_NONE,
		USE_SAVE_FROM_CLOUD,
		USE_SAVE_FROM_LOCAL,
	};
    
	struct structCommnad
	{
		enumTypeCommand _typeCommand;
		enumStateCommand _stateCommand;
	};

	structCommnad _command[MAX_COMMAND];
#if defined (ANDROID_OS)
	PineServiceHandle _svc_log_in_google_play, _svc_is_log_in_google_play, _svc_post_score_google_play, _svc_show_leaderBoard_google_play, 
		_svc_show_achievements_google_play,	_svc_unlock_achievements_google_play, _svc_google_plus_post, _svc_google_plus_post_screen, _svc_update_cloud_save,
		_svc_load_iap, _svc_retore_iap, _svc_take_screen_shot, _svc_share_screen_shot_intent, _svc_send_email_intent, _svc_show_messagebox;
	bool _list_id_group_achievement_need_check_unlock[MAX_ACHIEVEMENT] = { false };
	bool _process_unlock_achievement_done = false;
	bool _on_process_login_google_play = false;
	bool _on_process_share_screen_intent = false;

	int _id_group_achievement_current_check_unlock = 0;
	char _ach_id[128];
	char _iap_sku[128];
	char _share_screen_shot_message[256];
	char _send_email_title[128];
	char _send_email_body[256];
	char _message_box_title[64];
	char _message_box_message[128];
	bool _on_process_sync_cloud = false;
	enumCloudSaveConfirmType _message_box_confirm_type = enumCloudSaveConfirmType::CONFIRM_TYPE_NONE;
	bool _is_login_google;
	bool _is_force_login_google_play = false;
	char _current_achievement_unlock_id[128];
	bool _need_check_unlock_all_achievement = false;
	bool _is_waiting_for_post_reward = false;
	bool _is_show_game_services_menu = false;
	bool _on_post_reward = false;

	char* _list_archive[11] = {
		"CgkI_PiTovwBEAIQAQ",			//Day1
		"CgkI_PiTovwBEAIQAg",			//Day2
		"CgkI_PiTovwBEAIQAw",			//Day3
		"CgkI_PiTovwBEAIQBA",			//Day4
		"CgkI_PiTovwBEAIQBQ",			//Day5
		"CgkI_PiTovwBEAIQBg",			//Day6
		"CgkI_PiTovwBEAIQBw",			//HOME
		"CgkI_PiTovwBEAIQCQ",			//The journey begin
		"CgkI_PiTovwBEAIQCg",			//achievement_good_daddy
		"CgkI_PiTovwBEAIQCw",			//achievement_bicycling_master
		"CgkI_PiTovwBEAIQDA",			//achievement_early_challenge
	};
	char * _list_leaderBoard_id[8] = {
		"CgkI_PiTovwBEAIQCA",			//Top player
		"CgkI_PiTovwBEAIQDQ",			//day1
		"CgkI_PiTovwBEAIQDg",			//day2
		"CgkI_PiTovwBEAIQDw",			//day3
		"CgkI_PiTovwBEAIQEA",			//day4
		"CgkI_PiTovwBEAIQEQ",			//day5
		"CgkI_PiTovwBEAIQEg",			//day6
		"CgkI_PiTovwBEAIQEw",			//home
	};
	int count_retry_for_day_two = 0;
#endif

	void UpdateStateInit(int i);
	void UpdateStateProcessing(int i);
	void printfDebugType(int i);

	bool AddCommand(enumTypeCommand typeCommand);
	void EndCommand(int index);
	bool AlreadyHasCommand(enumTypeCommand typeCommand);
    void ClearAllCommand();

	void Run();
};

#endif
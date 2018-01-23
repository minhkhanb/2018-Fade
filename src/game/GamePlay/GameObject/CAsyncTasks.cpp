#include "pch.h"
#include "CAsyncTasks.h"
#include "../../GameCore/CGame.h"
#include "../../GameCore/Os_Functions.h"
#include "../Game_ExternFunctions.h"

bool CAsyncTasks::AddCommand(enumTypeCommand typeCommand)
{
	for (int i = 0; i < MAX_COMMAND; i++)
	{
		if (_command[i]._stateCommand == enumStateCommand::COMMAND_STATE_NONE)
		{			
			_command[i]._stateCommand = enumStateCommand::COMMAND_STATE_INIT;
			_command[i]._typeCommand = typeCommand;
			printf("\n=============Init task");
			printfDebugType(i);
			return true;
		}
	}
	return false;
}

bool CAsyncTasks::AlreadyHasCommand(enumTypeCommand typeCommand)
{
	for (int i = 0; i < MAX_COMMAND; i++)
	{
		if (_command[i]._typeCommand == typeCommand)
		{
			return true;
		}
	}
	return false;
}

void CAsyncTasks::ClearAllCommand()
{
	return;
	for (int i = 0; i < MAX_COMMAND; i++)
	{
		_command[i]._stateCommand = enumStateCommand::COMMAND_STATE_NONE;
		_command[i]._typeCommand = enumTypeCommand::COMMAND_TYPE_NONE;
	}
}

void CAsyncTasks::EndCommand(int i)
{
	printf("\n===============End task");
	printfDebugType(i);
	_command[i]._typeCommand = enumTypeCommand::COMMAND_TYPE_NONE;
	_command[i]._stateCommand = enumStateCommand::COMMAND_STATE_NONE;
}

void CAsyncTasks::Run()
{
	for (int i = 0; i < MAX_COMMAND; i++)
	{
		if (_command[i]._stateCommand == enumStateCommand::COMMAND_STATE_INIT)
		{
			UpdateStateInit(i);
		}
		else if (_command[i]._stateCommand == enumStateCommand::COMMAND_STATE_PROCESSING)
		{
			UpdateStateProcessing(i);
		}
	}
}

void CAsyncTasks::UpdateStateInit(int i)
{
	switch (_command[i]._typeCommand)
	{
#if defined (ANDROID_OS)
	case CAsyncTasks::COMMAND_TYPE_ASYN_LOAD_IAP:
		_svc_load_iap.reset();
		_command[i]._stateCommand = enumStateCommand::COMMAND_STATE_PROCESSING;
		break;
	case CAsyncTasks::COMMAND_TYPE_ASYN_RESTORE_PURCHASE:
		_svc_retore_iap.reset();
		_command[i]._stateCommand = enumStateCommand::COMMAND_STATE_PROCESSING;
		break;
	case CAsyncTasks::COMMAND_TYPE_ASYN_IS_LOG_IN_GOOGLE_PLAY:
		_svc_is_log_in_google_play.reset();
		_command[i]._stateCommand = enumStateCommand::COMMAND_STATE_PROCESSING;
		break;
	case CAsyncTasks::COMMAND_TYPE_ASYN_LOG_IN_GOOGLE_PLAY:
		_svc_log_in_google_play.reset();
		_command[i]._stateCommand = enumStateCommand::COMMAND_STATE_PROCESSING;
		break;
	case CAsyncTasks::COMMAND_TYPE_ASYN_GOOGLE_PLAY_POST_SCORE:
		_svc_post_score_google_play.reset();
		_command[i]._stateCommand = enumStateCommand::COMMAND_STATE_PROCESSING;
		break;
	case CAsyncTasks::COMMAND_TYPE_ASYN_GOOGLE_PLAY_SHOW_LEADERBOARD:
		_svc_show_leaderBoard_google_play.reset();
		_command[i]._stateCommand = enumStateCommand::COMMAND_STATE_PROCESSING;
		break; 
	case CAsyncTasks::COMMAND_TYPE_ASYN_GOOGLE_PLAY_SHOW_ACHIEVEMENTS:
		_svc_show_achievements_google_play.reset();
		_command[i]._stateCommand = enumStateCommand::COMMAND_STATE_PROCESSING;
		break; 
	case CAsyncTasks::COMMAND_TYPE_ASYN_GOOGLE_PLAY_UNLOCK_ACHIEVEMENT:
		for (int j = 0; j < MAX_ACHIEVEMENT; j++)
		{
			if (_list_id_group_achievement_need_check_unlock[j])
			{
				sprintf(_ach_id, "%s", _list_archive[j]);
				PDEBUG("Start Unlock achievement id: %s", _ach_id);
				_svc_unlock_achievements_google_play.reset();
				_command[i]._stateCommand = enumStateCommand::COMMAND_STATE_PROCESSING;
				_id_group_achievement_current_check_unlock = j;
				return;
			}
		}
		PDEBUG("No achievement need unlock end command");
		EndCommand(i);
		break;
	case CAsyncTasks::COMMAND_TYPE_ASYN_UPDATE_CLOUND_SAVE:
		_svc_update_cloud_save.reset();
		_command[i]._stateCommand = enumStateCommand::COMMAND_STATE_PROCESSING;
		break;
	case CAsyncTasks::COMMAND_TYPE_ASYN_TAKE_SCREEN_SHOT:
		_svc_take_screen_shot.reset();
		_command[i]._stateCommand = enumStateCommand::COMMAND_STATE_PROCESSING;
		break;
	case CAsyncTasks::COMMAND_TYPE_ASYN_SHARE_SCREEN_SHOT_INTENT:
		_svc_share_screen_shot_intent.reset();
		_command[i]._stateCommand = enumStateCommand::COMMAND_STATE_PROCESSING;
		break;
	case CAsyncTasks::COMMAND_TYPE_ASYN_SEND_EMAIL_INTENT:
		_svc_send_email_intent.reset();
		_command[i]._stateCommand = enumStateCommand::COMMAND_STATE_PROCESSING;
		break; 
	case CAsyncTasks::COMMAND_TYPE_ASYN_SHOW_MESSAGE_BOX:
		_svc_show_messagebox.reset();
		_command[i]._stateCommand = enumStateCommand::COMMAND_STATE_PROCESSING;
		break;
	case CAsyncTasks::COMMAND_TYPE_ASYN_GOOGLE_PLUS_POST:
		_svc_google_plus_post.reset();
		_command[i]._stateCommand = enumStateCommand::COMMAND_STATE_PROCESSING;
		break;
	case CAsyncTasks::COMMAND_TYPE_ASYN_GOOGLE_PLUS_POST_SCREEN:
		_svc_google_plus_post_screen.reset();
		_command[i]._stateCommand = enumStateCommand::COMMAND_STATE_PROCESSING;
		break;
#elif defined (_WINDOWS_PHONE8)
	case CAsyncTasks::COMMAND_TYPE_ASYN_SHARE_LINK:
		_svc_os_share_link.reset();
		sprintf(GAME()->_share_link_url, "http://www.windowsphone.com/s?appid=%s ", OS_GetAppId());
		//sprintf(GAME()->_share_link_message, "%s", "");
		_command[i]._stateCommand = enumStateCommand::COMMAND_STATE_PROCESSING;
		break;
	case CAsyncTasks::COMMAND_TYPE_ASYN_SHARE_MEDIA:
		_svc_os_share_media.reset();
		sprintf(GAME()->_share_media_file_name, "%s", TMP_FILE_SCREEN_CAPTURE);
		_command[i]._stateCommand = enumStateCommand::COMMAND_STATE_PROCESSING;
		break;
#endif
	default:
		break;

	}
}
void CAsyncTasks::UpdateStateProcessing(int i)
{
	switch (_command[i]._typeCommand)
	{
#if defined (ANDROID_OS)
	case CAsyncTasks::COMMAND_TYPE_ASYN_LOAD_IAP:
		OS_AsynLoadIAP(&_svc_load_iap);
		if (_svc_load_iap.Status == PineServiceResult::Responsed)
		{
			if (_svc_load_iap.ResponseStatus == 0)
			{
				PDEBUG("LOAD IAP successful");
			}
			else
			{
				PDEBUG("Load IAP fail with code: %d\n", _svc_load_iap.ResponseStatus);
			}
			EndCommand(i);
		}
		break;
	case CAsyncTasks::COMMAND_TYPE_ASYN_RESTORE_PURCHASE:
		OS_AsynRestoreIAP(&_svc_retore_iap, _iap_sku);
		if (_svc_retore_iap.Status == PineServiceResult::Responsed)
		{
			if (_svc_retore_iap.ResponseStatus == 0)
			{
				PURCHASE_FUNC(_iap_sku, enumIAPResponseStatus::IAP_RESPONSE_STATUS_SUCCESS_RESTORE);
				PDEBUG("Restore Iap successful!");
			}
			else
			{
				PDEBUG("Restore IAP fail with code: %d\n", _svc_retore_iap.ResponseStatus);
			}
			EndCommand(i);
		}
		break;
	case CAsyncTasks::COMMAND_TYPE_ASYN_IS_LOG_IN_GOOGLE_PLAY:
		OS_AsynIsLoginGooglePlay(&_svc_is_log_in_google_play);
		if (_svc_is_log_in_google_play.Status == PineServiceResult::Responsed)
		{
			if (_svc_is_log_in_google_play.ResponseStatus==0)
			{
				_is_login_google = true;
				PDEBUG("**************_is_login_google = true!");
				if (_on_process_sync_cloud)
				{
					ColorBorn* game = (ColorBorn*)(GAME()->_current_game);
					game->_state_gameplay._user.CheckLocalAndCloudSaveFile();
				}
				if (_is_show_game_services_menu)
				{
					/*ColorBorn* game = (ColorBorn*)(GAME()->_current_game);
					if (game->_current_state == k_GS_MAIN_MENU)
					{
						game->SetState(k_GS_GSM);
					}*/
				}
			}
			else
			{
				_is_login_google = false;
				PDEBUG("**************_is_login_google = false!");
				if (_is_force_login_google_play && !_on_process_login_google_play)
				{
					_on_process_login_google_play = true;
					AddCommand(CAsyncTasks::enumTypeCommand::COMMAND_TYPE_ASYN_LOG_IN_GOOGLE_PLAY);
				}
			}
			if (_is_force_login_google_play)
			{
				_is_force_login_google_play = false;
			}
			_is_show_game_services_menu = false;
			EndCommand(i);
		}
		break;
	case CAsyncTasks::COMMAND_TYPE_ASYN_LOG_IN_GOOGLE_PLAY:
		OS_AsynLoginGooglePlay(&_svc_log_in_google_play, true);
		if (_svc_log_in_google_play.Status == PineServiceResult::Responsed)
		{
			if (_svc_log_in_google_play.ResponseStatus == 0)
			{
				_is_login_google = true;
				if (_on_process_sync_cloud)
				{
					ColorBorn* game = (ColorBorn*)(GAME()->_current_game);
					game->_state_gameplay._user.CheckLocalAndCloudSaveFile();
				}
			}
			else
			{	
				if (_on_process_sync_cloud)
				{
					_on_process_sync_cloud = false;
				}
			}
			_on_process_login_google_play = false;
			EndCommand(i);
		}
		break;
	case CAsyncTasks::COMMAND_TYPE_ASYN_GOOGLE_PLAY_POST_SCORE:
		OS_AsynGooglePlayPostScore(&_svc_post_score_google_play, GAME()->_gameBoardScoreItem);
		if (_svc_post_score_google_play.Status == PineServiceResult::Responsed)
		{
			if (_svc_post_score_google_play.ResponseStatus == 0)
			{
				PDEBUG("Post score to google play success!");
			}
			else
			{
				PDEBUG("Can not post score to google play!");
			}
			EndCommand(i);
		}
		break;
	case CAsyncTasks::COMMAND_TYPE_ASYN_GOOGLE_PLAY_SHOW_LEADERBOARD:
		OS_AsynGooglePlayShowLeaderBoard(&_svc_show_leaderBoard_google_play, GAME()->_gameBoardScoreItem.BoardId);
		if (_svc_show_leaderBoard_google_play.Status == PineServiceResult::Responsed)
		{
			if (_svc_show_leaderBoard_google_play.ResponseStatus == 0)
			{
				PDEBUG("Show leader board google play done!");
			}
			else
			{
				PDEBUG("Can not show leader board google play!");
			}
			EndCommand(i);
		}
		break; 
	case CAsyncTasks::COMMAND_TYPE_ASYN_GOOGLE_PLAY_SHOW_ACHIEVEMENTS:
		OS_AsynGooglePlayShowAchievements(&_svc_show_achievements_google_play);
		if (_svc_show_achievements_google_play.Status == PineServiceResult::Responsed)
		{
			if (_svc_show_achievements_google_play.ResponseStatus == 0)
			{
				PDEBUG("Show achievements google play done!");
			}
			else
			{
				PDEBUG("Can not show achievements google play!");
			}
			EndCommand(i);
		}
		break; 
	case CAsyncTasks::COMMAND_TYPE_ASYN_GOOGLE_PLAY_UNLOCK_ACHIEVEMENT:
		OS_AsynGooglePlayUnlockAchievement(&_svc_unlock_achievements_google_play, _ach_id);
		if (_svc_unlock_achievements_google_play.Status == PineServiceResult::Responsed)
		{
			EndCommand(i);
			_list_id_group_achievement_need_check_unlock[_id_group_achievement_current_check_unlock] = false;
			if (_svc_unlock_achievements_google_play.ResponseStatus != 1)
			{
				PDEBUG("achievement google play id: %s Success!", _ach_id);
				AddCommand(COMMAND_TYPE_ASYN_GOOGLE_PLAY_UNLOCK_ACHIEVEMENT);
			}
			else
			{
				PDEBUG("Can not unlock achievement google play id: %s!", _ach_id);
			}	
		}
		break;
	case CAsyncTasks::COMMAND_TYPE_ASYN_UPDATE_CLOUND_SAVE:
		OS_AsynGoogleUpdateCloudSave(&_svc_update_cloud_save, CLOUD_SAVE_FILE_NAME);
		if (_svc_update_cloud_save.Status == PineServiceResult::Responsed)
		{
			PDEBUG("sync save to cloud done ResponseStatus = %d", _svc_update_cloud_save.ResponseStatus);
			if (_on_process_sync_cloud)
			{
				_on_process_sync_cloud = false;
			}
			if (_svc_update_cloud_save.ResponseStatus == 2)
			{
				PDEBUG("sync save to cloud conflict resolve successed reload save!");
				ColorBorn* game = (ColorBorn*)(GAME()->_current_game);
				game->_state_gameplay._user.CheckLocalAndCloudSaveFile();
			}
			else if (_svc_update_cloud_save.ResponseStatus == 0)
			{
				PDEBUG("sync save to cloud successed!");
				OS_ShowMessageBox("Congratulations!", "Your data has been saved!");
			}
			else
			{
				PDEBUG("sync save to cloud fail!");
				OS_ShowMessageBox("Error", "Error when saving data to Google Drive");
			}
			EndCommand(i);
		}
		break;
	case CAsyncTasks::COMMAND_TYPE_ASYN_TAKE_SCREEN_SHOT:
		OS_AsynCaptureScreen(&_svc_take_screen_shot, PineGraphicComplexOrientation::ComplexNone);

		if (_svc_take_screen_shot.Status == PineServiceResult::Responsed)
		{
			if (_svc_take_screen_shot.ResponseStatus == 0)
			{
				PDEBUG("Take screen shot successed!");
			}
			else
			{
				PDEBUG("Take screen shot fail!!!");
			}
			EndCommand(i);
		}
		break;
	case CAsyncTasks::COMMAND_TYPE_ASYN_SHARE_SCREEN_SHOT_INTENT:
		OS_AsynShareScreenShotIntent(&_svc_share_screen_shot_intent, _share_screen_shot_message);

		if (_svc_share_screen_shot_intent.Status == PineServiceResult::Responsed)
		{
			ColorBorn* game = (ColorBorn*)(GAME()->_current_game);
			if (_svc_share_screen_shot_intent.ResponseStatus == 0)
			{
				PDEBUG("Share screen shot successed!");
			}
			else
			{
				PDEBUG("Share screen shot fail!!!");
			}
			//game->_state_end_game._hud_share._state = 5;
			//game->_state_end_game._effect_flash_screen.SetDeactive();
			_on_process_share_screen_intent = false;
			EndCommand(i);
		}
		break;
	case CAsyncTasks::COMMAND_TYPE_ASYN_SEND_EMAIL_INTENT:
		OS_AsynSendEmailIntent(&_svc_send_email_intent, _send_email_title, _send_email_body);

		if (_svc_send_email_intent.Status == PineServiceResult::Responsed)
		{
			if (_svc_send_email_intent.ResponseStatus == 0)
			{
				PDEBUG("Send email successed!");
			}
			else
			{
				PDEBUG("Send email fail!!!");
			}
			EndCommand(i);
		}
		break; 
	case CAsyncTasks::COMMAND_TYPE_ASYN_SHOW_MESSAGE_BOX:
		OS_AsyncShowMessageBox(&_svc_show_messagebox, _message_box_title, _message_box_message);

		if (_svc_show_messagebox.Status == PineServiceResult::Responsed)
		{
			if (_svc_show_messagebox.ResponseStatus == 0)
			{
				PDEBUG("Message box user press OK!");
				if (_message_box_confirm_type == enumCloudSaveConfirmType::USE_SAVE_FROM_CLOUD)
				{
					Buffer* server_buff = OS_LoadAppData(CLOUD_SAVE_FILE_NAME);
					ColorBorn* game = (ColorBorn*)(GAME()->_current_game);
					game->_state_gameplay._user.UpdateLocalSaveFile(server_buff);
					delete server_buff;
					if (_on_process_sync_cloud)
					{
						_on_process_sync_cloud = false;
					}
					_need_check_unlock_all_achievement = true;
				}
				else if (_message_box_confirm_type == enumCloudSaveConfirmType::USE_SAVE_FROM_LOCAL)
				{
					ColorBorn* game = (ColorBorn*)(GAME()->_current_game);
					game->_state_gameplay._user.UpdateCloudSaveFile();
					GAME()->_async_task_manager.AddCommand(CAsyncTasks::enumTypeCommand::COMMAND_TYPE_ASYN_UPDATE_CLOUND_SAVE);
				}
				_message_box_confirm_type = enumCloudSaveConfirmType::CONFIRM_TYPE_NONE;
			}
			else
			{
				PDEBUG("Message box user press CANCEL!");
				if (_on_process_sync_cloud)
				{
					_on_process_sync_cloud = false;
				}
			}
			EndCommand(i);
		}
		break;
	case CAsyncTasks::COMMAND_TYPE_ASYN_GOOGLE_PLUS_POST:
		OS_AsynGooglePlayPost(&_svc_google_plus_post, _share_screen_shot_message);
		if (_svc_google_plus_post.Status == PineServiceResult::Responsed)
		{
			if (_svc_google_plus_post.ResponseStatus == 0)
			{
				PDEBUG("post google + successed!");
			}
			else
			{
				PDEBUG("Can not post google +!");
			}
			EndCommand(i);
		}
		break;
	case CAsyncTasks::COMMAND_TYPE_ASYN_GOOGLE_PLUS_POST_SCREEN:
		OS_AsynGooglePlayPostScreen(&_svc_google_plus_post_screen, _share_screen_shot_message);
		if (_svc_google_plus_post_screen.Status == PineServiceResult::Responsed)
		{
			if (_svc_google_plus_post_screen.ResponseStatus == 0)
			{
				PDEBUG("post google + successed!");
				if (_is_waiting_for_post_reward)
				{
					_on_post_reward = true;
				}
			}
			else
			{
				_is_waiting_for_post_reward = false;
				PDEBUG("post google + fail!");
			}
			EndCommand(i);
		}
		break;
#elif defined (_WINDOWS_PHONE8)
	case CAsyncTasks::COMMAND_TYPE_ASYN_SHARE_LINK:
		OS_AsyncShareLink(&_svc_os_share_link, GAME()->_stringShare, GAME()->_share_link_url, "");

		if (_svc_os_share_link.Status == PineServiceResult::Responsed)
		{
			if (_svc_os_share_link.ResponseStatus == 0)
			{
				PDEBUG("Share link successed!");
			}
			else
			{
				PDEBUG("Share link fail!!!");
			}
			EndCommand(i);
		}
		break;
	case CAsyncTasks::COMMAND_TYPE_ASYN_SHARE_MEDIA:
		OS_AsyncShareMedia(&_svc_os_share_media, GAME()->_share_media_file_name);

		if (_svc_os_share_link.Status == PineServiceResult::Responsed)
		{
			if (_svc_os_share_link.ResponseStatus == 0)
			{
				PDEBUG("Share media successed!");
			}
			else
			{
				PDEBUG("Share media fail!!!");
			}
			EndCommand(i);
		}
		break;
#endif	
	default:
		break;
	}
}

void CAsyncTasks::printfDebugType(int i)
{
	switch (_command[i]._typeCommand)
	{
#if defined (ANDROID_OS)
	case CAsyncTasks::COMMAND_TYPE_ASYN_GOOGLE_PLAY_POST_SCORE:
		printf("\t COMMAND_TYPE_ASYN_GOOGLE_PLAY_POST_SCORE");
		break;
	case CAsyncTasks::COMMAND_TYPE_ASYN_GOOGLE_PLAY_SHOW_LEADERBOARD:
		printf("\t COMMAND_TYPE_ASYN_GOOGLE_PLAY_SHOW_LEADERBOARD");
		break;
	case CAsyncTasks::COMMAND_TYPE_ASYN_GOOGLE_PLAY_SHOW_ACHIEVEMENTS:
		printf("\t COMMAND_TYPE_ASYN_GOOGLE_PLAY_SHOW_ACHIEVEMENTS");
		break;
#endif
	default:
		break;
	}
}
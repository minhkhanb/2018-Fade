#ifndef _USER_H
#define _USER_H

#define SAVE_FILE_NAME									"data.pine"
#if defined (ANDROID_OS)
#define CLOUD_SAVE_FILE_NAME							"clouddata.pine"
#endif

#define SAVE_VERSION_FIRST_VERSION						0
#define SAVE_CURRENT_VERSION							1

#define SAVE_FORMAT_CURRENT_VERSION					0 //INT_TIME
#define SAVE_FORMAT_USER_ID							(SAVE_FORMAT_CURRENT_VERSION+8) //INT_TIME
#define SAVE_FORMAT_USER_NAME						(SAVE_FORMAT_USER_ID+8) //char 128
#define SAVE_FORMAT_USER_GCID						(SAVE_FORMAT_USER_NAME+256) //INT32
#define SAVE_FORMAT_USER_FBID						(SAVE_FORMAT_USER_GCID+8) //INT_TIME
#define SAVE_FORMAT_USER_TWID						(SAVE_FORMAT_USER_FBID + 8) //INT_TIME
#define SAVE_FORMAT_SOUND_ENABLE					(SAVE_FORMAT_USER_TWID + 8) //bool
#define SAVE_FORMAT_MUSIC_ENABLE					(SAVE_FORMAT_SOUND_ENABLE + 1) //bool
#define SAVE_FORMAT_NOTIFI_ENABLE					(SAVE_FORMAT_MUSIC_ENABLE + 1) //bool
#define SAVE_FORMAT_BEST_SCORE						(SAVE_FORMAT_NOTIFI_ENABLE + 1) //UINT64
#define SAVE_FORMAT_RETRY							(SAVE_FORMAT_BEST_SCORE + 8) //int32
#define SAVE_FORMAT_PUSH_RATTING					(SAVE_FORMAT_RETRY + 4) //bool
#define SAVE_FORMAT_NO_ADS							(SAVE_FORMAT_PUSH_RATTING + 1) //bool
#define SAVE_FORMAT_FINISH_TUT						(SAVE_FORMAT_NO_ADS + 1) //bool
#define SAVE_FORMAT_STATE_NOTIFI					(SAVE_FORMAT_FINISH_TUT + 1) //int32

#define SAVE_FORMAT_END						(SAVE_FORMAT_FINISH_TUT + 1)
#define SAVE_FORMAT_LENGTH					(SAVE_FORMAT_END)


#define SAVE_MAX_BUFFER				(10000)
#define MAX_SAVE_BUFFER_CACHE		10000



#include "../../GameCore/CGame.h"
class CUser
{
public:
	CUser();
	~CUser();
	UINT64 _userID;
	char _userName[256];

	void SetUserName(const char name);
	void SetUserID(UINT64 ID);
	void SetUserGCID(UINT64 GC_ID);
	void SetUserFBID(UINT64 FB_ID);
	void SetUserTWID(UINT64 TW_ID);
	void SetFloatAt(char* buffer, int offset, float value);
	float GetFloatAt(char* buffer, int offset);
	UINT64 GetUserID();
	UINT64 GetUserGCID();
	UINT64 GetUserFBID();
	UINT64 GetUserTWID();
	void UserInitInfo();
	void UserDefautl();
	void LoadFromBuffer();
	void SaveToBuffer();
	void DataSave(bool rewrite = false);
	char _buffer[SAVE_MAX_BUFFER];
	void DataLoad();
	INT64 _version;
	bool _is_music;
	bool _is_sound;
	bool _is_notifi;

	UINT64 _best_score;
	int _retry;

	bool _push_rating;
	bool _no_ads;
	bool _finish_tut;
	int _state_will_notifi;

    int _check_syn_save_complete;
    void CheckAndSynSave();
	void SetFlagControlMusicSoundNotifiGame();
    void CheckVersion();
#if defined (ANDROID_OS)
	void CheckLocalAndCloudSaveFile();
	void UpdateCloudSaveFile();
	void UpdateLocalSaveFile(Buffer* buffer);
	void ConfirmSyncSaveToCloud();
	void ConfirmSyncSaveFromCloud();
#endif
private:
	UINT64 _user_GCID;
	UINT64 _user_FBID;
	UINT64 _user_TWID;
};
#endif
/**
*	will be included in CGame.h
*	specific vars and methods for gameplay
*/

public:
// game state	
	
private:
	
public:



	

//Save System.
void GameDataLoad();
void GameDataSave();
void GameDataDefault();
void GameDataToBuffer();
void GameLoadDataFromBuffer();

BYTE red, green, blue, alpha;
#define GAME_FILE	"pinerecord.dat"

#define GAME_VERSION				100

#define GAME_DATA_VERSION			(0)

#define GAME_DATA_LENGTH				(GAME_DATA_VERSION + 4)



char _buffer_save[GAME_DATA_LENGTH];
int _game_version;
int _rate;

//PineHighScore _pineHighScore;

 long _sys_begin_second;
 long _sys_millisecond;
 long _game_millisecond;
 long _sys_second;

void UnloadGameBackground();
bool LoadGameForceground();

bool _needresume_when_playing;


void PurchaseIAP(const char* strID, enumIAPResponseStatus sucessed);

int  _frame_auto_stop;
PineImage _image;


PineGame *_main_game;
PineGame  *_feature_game;
PineGame    *_current_game;


void ResetValueICloud();
void SaveToICloud();
void RewriteToICloud();
int CheckCanPushDataSave();
void LoadFromICloud();
void DefaultICloud();
void CheckICloud();
int _icloud_state;
#define ICLOUD_STATE_NODATA      -2
#define ICLOUD_STATE_DISCONECT   -3
#define ICLOUD_STATE_OLD_VERSION -1
#define ICLOUD_STATE_NEW_VERSION 0
#define ICLOUD_STATE_READY_SYNS  1

#if !defined (MAC_OS)
bool			_isBackkeyPress;
int				_waitForProcessBackkeyCount;
#if defined(ANDROID_OS)
//async tasks
CAsyncTasks _async_task_manager;
// admod
PineAdmobAsync _admob;
// unity ads
PineUnityAdsAsync _unityads;
bool InitAds();
bool HasAds();
bool HasVideoAds();
bool HasBannerAds();
void ShowAds();
void ShowVideoAds();
void ShowBannerAds();
void HideBannerAds();
void UpdateAds();
INT_TIME _time_start_wait_for_reinit_ads;
bool _on_video_ads_reward = false;
bool _is_waiting_for_reward = false;
int _show_ads_count;
int _show_unity_video_ads_count;
INT_TIME _time_first_show_unity_video_ads;
#define TIME_WAIT_FOR_REINIT_ADS 10*1000

BoardScoreItem		_gameBoardScoreItem;
#endif
#endif
TopeBox_PromoGame _topebox_game;
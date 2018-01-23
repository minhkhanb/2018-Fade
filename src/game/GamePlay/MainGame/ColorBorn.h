#ifndef  __COLORBORN__
#define __COLORBORN__

class ColorBorn : public PineGame
{
public:
	//GameCenter//
	////Game Center////

	void UpdateAndRender();
	void Init();
	void PauseEx();
	void ResumeEx();
	//////////////////////PORT GAME/////////
	PinePoint _point_o, _point_right_bottom;
	void MeasureButton(Button* button);
	void MeasureButton(Button* button, int anchor);
	void MeasureButtonX(float posx, Button* button, BYTE anchor_horizonal);
	void MeasureButtonY(float posy, Button* button, BYTE anchor_vertical);
	PinePoint MeasureFrame(CSprite* sprite, UINT32 frameid);
	void MeasureAnim(CAnimObject* obj);
	PinePoint MeasureFrame(CSprite* sprite, UINT32 frameid, float scalex, float scaley);
	PinePoint MeasureFrame(CSprite* sprite, UINT32 frameid, BYTE anchor);
	float _screen_width;
	float _screen_height;
	float _port_scale_x;
	float _port_scale_y;
	//////////////////////PORT GAME/////////
	//////////////////////IMPLEMENT GAMEPLAY
	bool _renderLogo;
	float _w_follow_port, _h_follow_port;
	StateLogo _state_logo;
	StateGamePlay _state_gameplay;
	StateTest _state_example;
	StateSettingAndCredit _state_setting_credit;
	int _device_current;

	int _device_w;
	int _device_h;
	bool _first_open_build;
	bool _first_rating;
	bool _first_open_rating;
	bool _device_ipad_ready;
	float _volumn_bgm_game;

	UINT64 _time_cool_down_check_rate;
	int _flag_check_ready_rate;
	int _counter_set_active_rating;

	struct Notifi
	{
		char text[1024];
		INT64 time;
	};
	struct ManagerNotifi
	{
		Notifi arr_notifi[11];
		void Init();
	};
	ManagerNotifi _manager_notifi;

	int _counter_game_play;
	struct PineAdsPlugin
	{
		int _state_app_download;
		void UpdateAdvert();
		void Init();
		void InitAdsvert();
		bool isShowingAds();
	};
	PineAdsPlugin _pine_ads_plugin;
	int _counter_show_ads;
	bool PushAds(int &value_state_change);
	int _flag_show_pine_ads;
	bool _allready_reset_tutorial;

	//Kha update google services
	void ShowLeaderBoard();
	void SyncDriver();
	void ShowAchievement();
	void SubmitAchievement(char ggPlayID_ACHIEVEMENT[]);

private:

};
#endif // ! __COLORBORN__

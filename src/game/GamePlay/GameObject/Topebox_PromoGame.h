#ifndef _TOPEBOX_PROMOGAME_H_
#define _TOPEBOX_PROMOGAME_H_

#define GAME_ICON_FILE_NAME		"gameIcon.png"

#define GAME_PROMO_RENDER_X		40
#define GAME_PROMO_RENDER_Y		(k_SCREEN_HEIGHT / 2 + 100)

#define TIME_SHOW_CLOSE_BUTTON	3 * 60

#define	PROMO_SAVE_IS_READY		0
#define PROMO_DATA_IS_READY		0


#include <string>

class TopeBox_PromoGame
{

public:
	TopeBox_PromoGame();
	~TopeBox_PromoGame();

	enum enumType
	{
		ICON,
		POPUP
	};

	enum enumPos
	{
		TOP_LEFT,
		TOP_RIGHT,
		BOT_LEFT,
		BOT_RIGHT
	};

	struct _Button
	{
		int x;
		int y;
		int w;
		int h;
	};


	enumType _type;

	bool _reGetTopeboxInfo;
	void InitPromo(float x, float y, int w, int h, enumType type, enumPos pos);
	void RenderPromo(float x, float y);
	void UpdatePromoInfo();
	void GetDataInfo();
	void GetPromoInfo();
	bool UpdateTouchPromo();
	bool PromoIsReady();
	bool PromoHasTouchDown();
	void ResetPromoInfo();
	void DisablePromo();
	void LoadImageToLocal();

	char _game_name[64], _link_store[128], _link_icon[256], _des[128], _revision[64];

	bool _is_need_reload;
	int _icon_w, _icon_h;

	bool popup_close;


	char save_file_config[256];
	bool popup_active;
	int count_show_popup;
	int count_skip_popup;
	bool popup_render;
	bool icon_render;

	enumPos _pos = enumPos::TOP_RIGHT;

	int revision;

	bool config_downloaded;

	CUser _user;

	void GetConfigData(char url[256]);
	void GetPromoData();

	float _screen_width;
	float _screen_height;


private:
	PineImage _game_icon;
	bool _is_ready;
	float _renderx, _rendery;
	int _touch_id;
	bool _has_download;

	float _icon_scaleEff, _icon_scaleEff_speed, _icon_scale_size;
	int _icon_scale_time, _icon_scale_state;
	char remote_url[256];

	_Button _button_close;

};


#endif


#ifndef __SETTING_HUD_BUTTON__
#define __SETTING_HUD_BUTTON__

class SettingHudButton
{
public:
	float _scroll_page_credit_x;
	float _scroll_page_x;
	float _speed_scroll;
	void Init();
	void Update();
	void Render();
	void RenderCredits();
	void UpdatePosButton();
	bool UpdateTouch();
	int _state;
	PinePoint _point_begin;
	PinePoint _point_draw;
#define SETTING_NUM_BUTTON		10
	Button _arr_button[SETTING_NUM_BUTTON];
	bool _is_draw_credits;
	bool _flag_reset_tutorial;
	void ResetGamePlayToTutorial();

	//Kha update android
#define SETTING_BUTTON_FACEBOOK	2
#define	SETTING_BUTTON_TWITTER	3
#define SETTING_BUTTON_ICLOUD	4
#define SETTING_BUTTON_RESTORE	6

private:

};

#endif // !__SETTING_HUD_BUTTON__

#ifndef __COLORBORN_SETTING__
#define __COLORBORN_SETTING__

class StateSettingAndCredit
{
public:
	void InitSetting();
	void RenderSetting();
	void UpdateSetting();
	bool UpdateControl();
	int _state;

	SettingHudButton _hud_setting_button;
	SettingEffectTouchButton _effect_touch_button;

	int _time_cooldown_replay_function_dis_ads;
private:

};

#endif // __COLORBORN_GAMEPLAY__

#ifndef __GAMEPLAY_HUD_INGAME__
#define __GAMEPLAY_HUD_INGAME__

class GPHudIngame
{
public:
	void Init();
	void Update();
	void UpdatePos();
	bool UpdateButton();
	void Render();
	PinePoint _point_begin;
	PinePoint _point_draw;
#define INGAME_BUTTON_NUM			5
	Button _button_arr[INGAME_BUTTON_NUM];
	int _state;
	float _title_scroll_y;
private:

};
#endif
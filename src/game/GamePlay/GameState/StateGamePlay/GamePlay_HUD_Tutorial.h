#ifndef __GAMEPLAY_HUD_TUTORIAL__
#define __GAMEPLAY_HUD_TUTORIAL__

class GPHudTutorial
{
public:
	void Init();
	void Update();
	void Render();
	void UpdateTouch();
	int _index_touch;
	PinePoint _point_begin, _point_draw;
	float _opacity_all;
	int _state;
	float _effect_opacity_hight_light_percent;
	float _effect_opacity_hight_light_speed;
	Acceleration _effect_opacity_hight_light_accel;
	int _effect_opacity_hight_light_state;

	float _text_speed_scroll;

	float _text_one_percent;
	float _text_two_percent;

	int _index_column_choose;
	bool _flag_new_grid;
	float _opacity_new_grid;
	bool CheckFinishTut();
private:

};

#endif
#ifndef __GAMEPLAY_HUD_END_GAME__
#define __GAMEPLAY_HUD_END_GAME__

class GPHudEndGame
{
public:
	void Init();
	void Update();
	void Render();
	PinePoint _point_begin, _point_draw;
	PinePoint _point_begin_behind, _point_draw_behind;
	int _state;
	float _percent;
	float _speed;
	float _percent_behind;
	float _speed_behind;
	int _time_delay_behind;
	Acceleration _acceleration_scroll;
	Acceleration _acceleration_scroll_behind;
	int _time_wait_check_show_popup;
	void StartCheckPopUp();
private:

};
#endif // __GAMEPLAY_HUD_END_GAME__

#ifndef __GAMEPLAY_HUD_SHARE__
#define __GAMEPLAY_HUD_SHARE__

class GPHudShare
{
public:
	void Init();
	void Update();
	void Render();
	float _percent;
	float _speed;
	int _state;
	PinePoint _point_begin, _point_draw;
	float _frame_height;
	int _last_state;

	float _opacity_flash;
private:

};

#endif // !__GAMEPLAY_HUD_SHARE__

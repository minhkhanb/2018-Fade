#ifndef __GAMEPLAY_HUD_LOADING__
#define __GAMEPLAY_HUD_LOADING__

class GPHudLoading
{
public:
	int _last_state_backup;
	void Init(bool auto_off = false);
	void Update();
	void Render();
	PinePoint _point_begin, _point_draw;
	int _state;
	float _percent;
	float _speed;
	int _time_counter;
	float _rotate_circle;
	float _speed_rotate;
	bool flag_auto;
	int _time_turn_off;

	struct LoadingCircle
	{
		void Init(PinePoint index);
		void Update();
		void Render();
		int _state;
		bool isFinish();
		float _percent;
		float _speed;
		PinePoint _pos_draw;
	};
	LoadingCircle *_loading_arr_circle;
	int _num_circle;
	void LoadingCircleDefault();
	void LoadingCircleAdd(PinePoint index);
	void LoadingCircleDelete(int index);
	void LoadingCircleUpdate();
	void LoadingCircleRender();
private:

};

#endif // !__GAMEPLAY_HUD_LOADING__

#ifndef __GAMEPLAY_HUD_BACK_GROUND__
#define __GAMEPLAY_HUD_BACK_GROUND__

class GPHudBackGround
{
public:
	void Init();
	void Update();
	bool RevertTime(float percent);
	void FinishRevert();
	bool _flag_is_revert;
	void Render();
	PinePoint _point_draw_fadei, _point_begin_fadei;
	PinePoint _point_draw_time_symbol, _point_begin_time_symbol;
	int _state;
	int _score_add;

	COLOR _color_background_begin;
	COLOR _color_background_current;
	COLOR _color_background_end;

	COLOR _color_radian_begin;
	COLOR _color_radian_current;
	COLOR _color_radian_end;

	TransformColor _transform_color_bg;
	TransformColor _transform_color_radian;

	void SetColorEnd(COLOR c_end);

	float _speed_revert;
	float _percent_current;
	float _percent_target;
	void SetNewPercent(float percent);

	int const _max_distance_can_scroll = 250;

	COLOR GetColorNewFromBegin(short r_input, short g_input, short b_input, COLOR color_begin);

	struct FadeiPush
	{
		PinePoint point_begin;
		PinePoint point_draw;
		PinePoint point_target;
		int state;
		float percent;
		float speed;
		void Init(int pow, bool pow_clear);
		void Render();
		void Update();
		void Default();
		bool isFinish();
		COLOR color_current;
		void UpdateColorCurrent();
		float power_add;
		float counter_power_add;
		int opacity_fadei;
		float percent_speed_weak;
		TransformColor _color_transform;
	};

	struct ManagerFadeiPush
	{
		FadeiPush *arr_fadei;
		int num_push_current;
		void Add(int pow, bool pow_clear);
		void Delete(int index);
		void Update();
		void SetStateFade(int index_state);
		void Render();
		void Default();
	};
	ManagerFadeiPush _manager_fadei_push;
	
	void UpdateResetTimeBar();
	void SetResetTimeBar(int type);
	Acceleration _acceleration_revert;
	void StartCounterTime();

	struct EffectHightLightFadeTime
	{
		void Default();
		void Update();
		void Render();
		float percent;
		float speed;
		int state;
		bool flag_push;
		void SetAppeare();
	};
	EffectHightLightFadeTime _effect_hight_light_fade_time;
private:

};

#endif // __GAMEPLAY_HUD_BACK_GROUND__

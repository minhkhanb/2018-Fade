#ifndef __EFFECT_FISH_TANK__
#define __EFFECT_FISH_TANK__

class EffectFishTank
{
public:
	struct Fish
	{
		PinePoint point_draw;
		void Init();
		void Init(float pos_x, float pos_y);
		void Update();
		void Render();
		float power_current;
		SVector2 vector_go;
		float angle_current;
		bool no_collsion;
		float last_angle;
		int state;
		float dir_like;
		int time_random;
		void UpdateDirLike();
		bool flag_bug_return_home;
		bool isFinish();

		int opacity_fish;
	};

	Fish *_arr_fish;
	int _num_fish_current;

	PinePoint _point_a, _point_b, _point_c, _point_d;
	PineRectangle _rect_a, _rect_b, _rect_c, _rect_d;

	void DefaultManager();
	void UpdateManager();
	void RenderManager();
	void Add();
	void Add(float pos_x, float pos_y);
	void Delete(int index);
	void FreeMemory();

	int _time_counter_add_fish;
private:

};

#endif // !__EFFECT_FISH_TANK__

#ifndef __GAMEPLAY_EFFECT_TYPE_CLEAR_IDLE__
#define __GAMEPLAY_EFFECT_TYPE_CLEAR_IDLE__

class EffectTypeClearIdle
{
public:
	struct TypeClearGlow
	{
		void Init(PointIndex index);
		void Update();
		void Render();
		int _state;
		bool isFinish();
		float _percent;
		float _speed;
		PointIndex _point_index;
	};
	TypeClearGlow *_wave_arr;

	void Default();
	void Add(PointIndex index);
	void Delete(int index);
	void Update();
	void Render();
	int _num_effect_current;

	int _time_counter;
	void FreeMemory();
private:

};

#endif // !__GAMEPLAY_EFFECT_TYPE_CLEAR_IDLE__

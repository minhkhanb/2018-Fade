#ifndef __SETTING_EFFECT_TOUCH_BUTTON__
#define __SETTING_EFFECT_TOUCH_BUTTON__

class SettingEffectTouchButton
{
public:
	struct EffectWaveButton
	{
		PinePoint _point_begin, _point_draw;
		void Init(float pos_x, float pos_y);
		void Update();
		void Render();
		int _state;
		bool isFinish();
		float _percent;
		float _speed;
	};
	EffectWaveButton *_wave_arr;

	void Default();
	void UpdateManager();
	void RenderManager();
	void AddEffect(float pos_x, float pos_y);
	void RemoveEffect(int index);
	int _num_effect_current;
private:

};

#endif // !__SETTING_EFFECT_TOUCH_BUTTON__

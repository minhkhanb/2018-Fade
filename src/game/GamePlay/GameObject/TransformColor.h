#ifndef __SEVENTEEN_TRANFORMS_COLOR__
#define __SEVENTEEN_TRANFORMS_COLOR__

class TransformColor
{
public:
	struct colorElement
	{
		short _byte;
		float _float;
	};
	colorElement test;
	struct colorDetal
	{
		colorElement _a, _r, _g, _b;
	};
	

	colorDetal _current_color, _target_color, _delta_color;
	COLOR _draw_color, _begin_color, _end_color;
	void Init(COLOR one, COLOR two, int num_frame);
	void Update();
	int state;
	void Default();
	bool isFinish();

	colorDetal _start_color;
	void InitColorFollowPercent(COLOR one, COLOR two);
	void UpdateFollowPercent(float percent);
private:

};
#endif // !__SEVENTEEN_TRANFORMS_COLOR__

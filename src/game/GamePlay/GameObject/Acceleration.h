#ifndef __CGAME_ACCELERATION__
#define __CGAME_ACCELERATION__

class Acceleration
{
public:
	float speed;
	int state;
	void Defalt();
	void UpdateAcceleration(float &value_out, float value_end, float percent, bool increase, float pow_max, float pow_min, float speed_min, float speed_dont_pass);
	void UpdateAccelerationEnd(float &value_out, float value_end, float percent, bool increase);
	bool isFinish();
	void PrintfSpeed();
private:

};
#endif // !__CGAME_ACCELERATION__

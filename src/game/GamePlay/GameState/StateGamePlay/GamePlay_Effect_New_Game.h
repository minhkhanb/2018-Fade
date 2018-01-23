#ifndef __GAMEPLAY_EFFECT_NEW_GAME__
#define __GAMEPLAY_EFFECT_NEW_GAME__

class EffectNewGame
{
public:
	void Default();
	void Init();
	void Update();
	void Render();
	int _state;
	float _percent;
	float _speed;
	Acceleration _acceleration_scroll;
	float _opacity;
private:

};
#endif // __GAMEPLAY_EFFECT_NEW_GAME__

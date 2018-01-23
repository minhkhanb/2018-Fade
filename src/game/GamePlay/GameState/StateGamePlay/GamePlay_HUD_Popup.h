#ifndef __GAMEPLAY_HUD_POPUP__
#define __GAMEPLAY_HUD_POPUP__

class GPHudPopup
{
public:
	PinePoint _point_begin;
	PinePoint _point_draw;
	void Default();
	void Init();
	void Update();
	void Render();
	int _state;
	float _percent;
	float _speed;
	Acceleration _acceleration_scroll;
	void CheckStartPopup();
#define RATING_NUM_BUTTON			2
	Button _button_rate[RATING_NUM_BUTTON];
#define HIGHT_SCORE_NUM_BUTTON		2
	Button _button_hight_score[HIGHT_SCORE_NUM_BUTTON];

	bool UpdateButtonRating();
	bool UpdateButtonHightScore();
	int _time_counter;
	int _state_last;
	float _opacity_shadow;

	bool _flag_play_sound_high_score;
private:

};

#endif // !__GAMEPLAY_HUD_POPUP__

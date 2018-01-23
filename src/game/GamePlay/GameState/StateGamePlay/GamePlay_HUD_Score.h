#ifndef __GAMEPLAY_HUD_SCORE__
#define __GAMEPLAY_HUD_SCORE__

class GPHudScore
{
public:
	void Init();
	void Update();
	void Render();
	PinePoint _point_begin;
	PinePoint _point_draw;
	int _state;
	int _score_add;
	INT64 _score_current;
	void AddCacheScore(int score);
	void SubmitCache();
	void UpdatePos();
	void UpdateAndSubmitHightScore();
	bool _have_hight_score;

	float _opacity_current_score;
private:

};
#endif
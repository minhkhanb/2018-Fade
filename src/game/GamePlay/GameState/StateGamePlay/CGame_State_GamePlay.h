#ifndef __COLORBORN_GAMEPLAY__
#define __COLORBORN_GAMEPLAY__

class StateGamePlay
{
public:
	void InitGamePlay();
	void ResetGamePlay();
	void ResetBoardGame();
	void UpdateGamePlay();
	void RenderGamePlay();
	bool UpdateControl();

	/*GameCore*/
	MatrixDraw _master_game;
	/*End*/

	/*Hud*/
	GPHudScore _hud_score;
	GPHudIngame _hud_ingame;
	GPHudBackGround _hud_background;
	GPHudShare _hud_share;
	GPHudEndGame _hud_end_game;
	GPHudPopup _hud_popup;
	GPHudTutorial _hud_tutorial;
	GPHudLoading _hud_loading;
	/*End*/

	/*Effect*/
	EffectNewGame _effect_new_game;
	EffectFishTank _effect_fish_tank;
	/*End*/

	float _scroll_page_x;
	float _scroll_page_y;
	void UpdateScrollPageX();
	void UpdateScrollPageY();
	//User Data Save
	CUser _user;
	int _gameplay_state;
private:

};

#endif // !__COLORBORN_GAMEPLAY__

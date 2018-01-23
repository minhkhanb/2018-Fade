#include "pch.h"
#include "../../../GameCore/CGame.h"

void GPHudScore::Init()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	_point_begin.X = game->_point_o.X + game->_screen_width / 2;
	_point_begin.Y = game->_point_o.Y + 275.0f;
	_point_draw = _point_begin;
	_score_current = 0;
	_score_add = 0;
	_state = 0;
	_have_hight_score = false;
	_opacity_current_score = 100.0f;
}

void GPHudScore::Update()
{
}

void GPHudScore::Render()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	GET_SPRITE(SPRITEID_FONT_SCORE_INGAME)->SetCharSpacing(15);
	GET_SPRITE(SPRITEID_FONT_SCORE_NUMBER_INGAME)->SetCharSpacing(15);
	CMatrix4x4Util matrix_normal;
	matrix_normal.reNew();
	matrix_normal.DoScale(0.5f, 0.5f, _point_draw.X + 5.0f, _point_draw.Y);
	G()->SetTransform(matrix_normal.toPineTranform());
	G()->SetOpacity((int)_opacity_current_score);
	GET_SPRITE(SPRITEID_FONT_SCORE_NUMBER_INGAME)->DrawAnsiTextFormat(G(), _point_draw.X + 5.0f, _point_draw.Y, _HCENTER, "%d", _score_current);
	G()->SetOpacity(100);
	G()->ClearTransform();


	INT64 hight_score = game->_state_gameplay._user._best_score;
	float draw_y = _point_draw.Y + 45.0f;
	G()->SetColorMask(0xFFFFC286);
	GET_SPRITE(SPRITEID_FONT_HIGHSCORE_INGAME)->SetCharSpacing(2);
	GET_SPRITE(SPRITEID_FONT_HIGHSCORE_INGAME)->SetWordSpacing(-25);
	matrix_normal.reNew();
	matrix_normal.DoScale(0.5f, 0.5f, _point_draw.X, draw_y);
	G()->SetTransform(matrix_normal.toPineTranform());
	GET_SPRITE(SPRITEID_FONT_HIGHSCORE_INGAME)->DrawAnsiTextFormat(G(), _point_draw.X, draw_y, _HCENTER, ": %lld", hight_score);
	G()->ClearTransform();
	G()->ClearColorMask();

	/*G()->SetColor(0xFFFFFFFF);
	G()->FillRect(_point_draw.X, _point_draw.Y, 5, 5);
	G()->FillRect(_point_draw.X, draw_y, 5, 5);*/
}

void GPHudScore::AddCacheScore(int score)
{
	_score_add += score;
}

void GPHudScore::SubmitCache()
{
	_score_current += _score_add;
	_score_add = 0;
}

void GPHudScore::UpdatePos()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	_point_draw.X = _point_begin.X + game->_state_gameplay._scroll_page_x;
	_point_draw.Y = _point_begin.Y + game->_state_gameplay._scroll_page_y;
}

void GPHudScore::UpdateAndSubmitHightScore()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	if (_score_current > game->_state_gameplay._user._best_score)
	{
		game->_state_gameplay._user._best_score = _score_current;
		game->_state_gameplay._user.DataSave();
		_have_hight_score = true;
	}
	else
	{
		_have_hight_score = false;
	}
	//Submit score to server
#ifdef MAC_OS
	PineGameCenterController::SubmitMyScore("fade_topplayer", game->_state_gameplay._user._best_score);
#endif // MAC_OS
}

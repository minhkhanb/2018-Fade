#include "pch.h"
#include "../../../GameCore/CGame.h"

#if defined(MAC_OS)
extern "C" void GoToReviewPage();
#elif defined (ANDROID_OS)
extern "C" void	OS_Rating();
#else
extern "C" void GoToReviewPage() {};
#endif

void GPHudPopup::Default()
{
	_state = -1;
	_flag_play_sound_high_score = false;
}

void GPHudPopup::Init()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	_point_begin.X = game->_point_o.X + game->_screen_width / 2;
	_point_begin.Y = game->_point_o.Y + game->_screen_height / 2;

	_point_draw.X = _point_begin.X + game->_screen_width;
	_point_draw.Y = _point_begin.Y;
	_acceleration_scroll.Defalt();
	_percent = 1.0f;

	float draw_x = _point_draw.X - (375.0f - 242.0f);
	float draw_y = _point_draw.Y + (942.0f - 750.0f);
	_button_rate[0].Init(BUTTON_STATE_NORMAL, draw_x, draw_y, A_HVCENTER);
	_button_rate[0].SetAnim(SPRITEID_HUD_RATING, 0);

	draw_x = _point_draw.X + (449.0f - 375.0f);
	draw_y = _point_draw.Y + (942.0f - 750.0f);
	_button_rate[1].Init(BUTTON_STATE_NORMAL, draw_x, draw_y, A_HVCENTER);
	_button_rate[1].SetAnim(SPRITEID_HUD_RATING, 4);

	draw_x = _point_draw.X - (375.0f - 212.0f);
	draw_y = _point_draw.Y + (945.0f - 750.0f);
	_button_hight_score[0].Init(BUTTON_STATE_NORMAL, draw_x, draw_y, A_HVCENTER);
	_button_hight_score[0].SetAnim(SPRITEID_HUD_HIGHSCORE, 0);

	draw_x = _point_draw.X + (444.0f - 375.0f);
	draw_y = _point_draw.Y + (945.0f - 750.0f);
	_button_hight_score[1].Init(BUTTON_STATE_NORMAL, draw_x, draw_y, A_HVCENTER);
	_button_hight_score[1].SetAnim(SPRITEID_HUD_HIGHSCORE, 4);

	_state_last = game->_state_gameplay._gameplay_state;
	game->_state_gameplay._gameplay_state = 4;
	_speed = 0.005f;
	_opacity_shadow = 0.0f;

	for (int i = 0; i < RATING_NUM_BUTTON; i++)
	{
		_button_rate[i].SetSoundID(SFX_BUTTON);
	}
	for (int i = 0; i < HIGHT_SCORE_NUM_BUTTON; i++)
	{
		_button_hight_score[i].SetSoundID(SFX_BUTTON);
	}
}

void GPHudPopup::Update()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	if (_state != -1 && _state != 3)
	{
		if (_state == 0 || _state == 10)
		{
			_percent = (_point_draw.X - _point_begin.X) / game->_screen_width;
			if (_flag_play_sound_high_score && _percent < 0.5f)
			{
				GAME()->PlaySFX(SFX_NEW_HIGHSCORE);
				_flag_play_sound_high_score = false;
			}
			_acceleration_scroll.UpdateAcceleration(_point_draw.X, _point_begin.X, 1.0f - _percent, false, 1.1f, 0.88f, 0.2f, 0.2f);
			_acceleration_scroll.UpdateAccelerationEnd(_point_draw.X, _point_begin.X, 1.0f - _percent, false);
			_opacity_shadow = (1.0f - _percent) * 100.0f;
			if (_acceleration_scroll.isFinish())
			{
				_state++;
				_opacity_shadow = 100.0f;
			}
		}
		if (_state == 1 || _state == 11)
		{
			if (_state == 1)
			{
				UpdateButtonRating();
			}
			if (_state == 11)
			{
				UpdateButtonHightScore();
			}
		}
		else if (_state == 2 || _state == 12)
		{
			_percent+= _speed;
			_speed *= 1.1f;
			if (_percent > 1.0f)
			{
				_percent = 1.0f;
				_state = 3;
				game->_state_gameplay._gameplay_state = _state_last;
			}
			_point_draw.X = _point_begin.X - _percent * game->_screen_width;
			_opacity_shadow = (1.0f - _percent) * 100.0f;
		}
		float draw_x = _point_draw.X - (375.0f - 242.0f);
		float draw_y = _point_draw.Y + (942.0f - 750.0f);
		//printf("\ndraw_x: %f, draw_y: %f", draw_x, draw_y);
		_button_rate[0].SetPos(draw_x, draw_y);

		draw_x = _point_draw.X + (449.0f - 375.0f);
		draw_y = _point_draw.Y + (942.0f - 750.0f);
		_button_rate[1].SetPos(draw_x, draw_y);

		draw_x = _point_draw.X - (375.0f - 212.0f);
		draw_y = _point_draw.Y + (945.0f - 750.0f);
		_button_hight_score[0].SetPos(draw_x, draw_y);

		draw_x = _point_draw.X + (444.0f - 375.0f);
		draw_y = _point_draw.Y + (945.0f - 750.0f);
		_button_hight_score[1].SetPos(draw_x, draw_y);
	}
}

void GPHudPopup::Render()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	if (_state != -1 && _state != 3)
	{
		G()->SetOpacity((int)_opacity_shadow);
		G()->SetColor(0xFF0A0F18);
		G()->FillFullScreen(true);
		G()->SetOpacity(100);

		float draw_x = _point_draw.X;
		float draw_y = _point_draw.Y;
		GET_SPRITE(SPRITEID_HUD_RATING)->DrawFrame(G(), 0, draw_x, draw_y);

		if (_state >= 0 && _state < 3)
		{
			draw_x = _point_draw.X;
			draw_y = _point_draw.Y - 55.0f;
			GET_SPRITE(SPRITEID_HUD_RATING)->DrawFrame(G(), 1, draw_x, draw_y);
			for (int i = 0; i < RATING_NUM_BUTTON; i++)
			{
				_button_rate[i].Render(G());
				_button_rate[i].Update();
			}
		}
		if (_state >= 10)
		{
			draw_x = _point_draw.X;
			draw_y = _point_draw.Y - 24.0f;
			GET_SPRITE(SPRITEID_HUD_HIGHSCORE)->DrawFrame(G(), 1, draw_x, draw_y);

			draw_y += 110.0f;
			CMatrix4x4Util matrix_normal;
			matrix_normal.reNew();
			matrix_normal.DoScale(1.0f, 1.0f, draw_x, draw_y);
			G()->SetTransform(matrix_normal.toPineTranform());
			GET_SPRITE(SPRITEID_FONT_SCORE_INGAME)->DrawAnsiTextFormat(G(), draw_x, draw_y, _HCENTER, "%lld", game->_state_gameplay._user._best_score);
			G()->ClearTransform();
			
			for (int i = 0; i < HIGHT_SCORE_NUM_BUTTON; i++)
			{
				_button_hight_score[i].Render(G());
				_button_hight_score[i].Update();
			}
		}
	}
}

void GPHudPopup::CheckStartPopup()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	bool right_rule = false;
	_flag_play_sound_high_score = false;
	if (_state == -1 || _state == 3)
	{
#if defined (MAC_OS) || defined (ANDROID_OS)
		if (!GAME()->_device.IsNetworkAvailable())
		{
			_state = 3;
			return;
		}
#endif // MAC_OS
		bool ready = false;
		if (game->_state_gameplay._hud_score._have_hight_score)
		{
			_state = 10;
			Init();
			ready = true;
			right_rule = true;
			_flag_play_sound_high_score = true;
		}
		if (game->_state_gameplay._user._push_rating && !ready)
		{
            printf("\n_retry: %d", game->_state_gameplay._user._retry);
			if (game->_first_rating)
			{
				if (game->_state_gameplay._user._retry % 10 == 0)
				{
					_state = 0;
					Init();
					right_rule = true;
					game->_first_rating = false;
				}
			}
			else
			{
				if (game->_state_gameplay._user._retry % 5 == 0)
				{
					_state = 0;
					Init();
					right_rule = true;
					game->_first_rating = false;
				}
			}
		}
		if (_state != 10 && _state != 0)
		{
			_state = 3;
		}
		if (_state == -1 || _state == 3)
		{
			right_rule = game->PushAds(_state);
		}
	}
	if (right_rule)
	{
		//clear touch_id
	}
}

bool GPHudPopup::UpdateButtonRating()
{
	ColorBorn *game = (ColorBorn*)GAME()->_current_game;
	bool button_touched = false;
	int index = 0;
	for (int i = 0; i < RATING_NUM_BUTTON; i++)
	{
		if (_button_rate[i]._state == BUTTON_STATE_ACTIVE)
		{
			button_touched = true;
			index = i;
			break;
		}
	}
	if (button_touched)
	{
		//printf("\n setting button_touched = %d", index);
		if (_button_rate[index].NeedAction())
		{
			switch (index)
			{
			case 0:// cancle
				_state++;
				break;
			case 1:// rate
				game->_flag_check_ready_rate = 2;
				if (game->_state_gameplay._user._state_will_notifi == 0)
				{
					game->_state_gameplay._user._state_will_notifi = 1;
				}
				game->_state_gameplay._user._push_rating = false;
				game->_state_gameplay._user.DataSave();
#if defined(MAC_OS)
				GoToReviewPage();
#elif defined (ANDROID_OS)
				OS_Rating();
#endif
				_state++;
				break;
			default:
				break;
			}
			for (int i = 0; i < RATING_NUM_BUTTON; i++)
			{
				if (_button_rate[i]._state != BUTTON_STATE_LOCK && _button_rate[i]._state != BUTTON_STATE_HIDE)
				{
					_button_rate[i].SetState(BUTTON_STATE_NORMAL);
				}
			}
		}
		return true;
	}
	bool ret = false;
	for (int i = 0; i < GAME()->_num_touches; i++)
	{
		for (int button = 0; button < RATING_NUM_BUTTON; button++)
		{
			if (_button_rate[button]._state == BUTTON_STATE_LOCK || _button_rate[button]._state == BUTTON_STATE_HIDE)
			{
				continue;
			}
			int x = _button_rate[button].TZ_GetX() - 20;
			int y = _button_rate[button].TZ_GetY() - 20;
			int w = _button_rate[button].TZ_GetWidth() + 40;
			int h = _button_rate[button].TZ_GetHeight() + 40;
			Button *bt = &_button_rate[button];
			if (CHECK_POINT_IN_RECT(TOUCHS(i)->x, TOUCHS(i)->y, x, y, w, h))
			{
				if (TOUCHS(i)->_state == TOUCH_DOWN)
				{
					if (bt->_touch_id == -1)
					{
						//if (!_play_sound_button_gameplay)
						//{
						//_play_sound_button_gameplay = true;
						//GAME()->PlaySFX(SFX_BUTTON);
						//}
						bt->_touch_id = TOUCHS(i)->_id;
						bt->SetState(BUTTON_STATE_SELECT);
					}
				}
				else if (TOUCHS(i)->_state == TOUCH_DRAG)
				{
					if (bt->IsAction(TOUCHS(i)->_id))
					{
						//bt->SetState(BUTTON_STATE_SELECT);
					}
				}
				else if (TOUCHS(i)->_state == TOUCH_UP)
				{
					if (bt->IsAction(TOUCHS(i)->_id))
					{
						//_play_sound_button_gameplay = false;
						bt->SetState(BUTTON_STATE_ACTIVE);
						printf("\n button = %d", button);
					}
				}
				if (bt->_touch_id != -1)
				{
					ret = true;
				}
			}
			else
			{
				if (bt->IsAction(TOUCHS(i)->_id))
				{
					if (TOUCHS(i)->_state == TOUCH_UP)
					{
						//_play_sound_button_gameplay = false;
						bt->_touch_id = -1;
						bt->SetState(BUTTON_STATE_ACTIVE);
					}
					ret = true;
				}
			}
		}
	}
	return ret;
}

bool GPHudPopup::UpdateButtonHightScore()
{
	ColorBorn *game = (ColorBorn*)GAME()->_current_game;
	bool button_touched = false;
	int index = 0;
	for (int i = 0; i < HIGHT_SCORE_NUM_BUTTON; i++)
	{
		if (_button_hight_score[i]._state == BUTTON_STATE_ACTIVE)
		{
			button_touched = true;
			index = i;
			break;
		}
	}
	if (button_touched)
	{
		//printf("\n setting button_touched = %d", index);
		if (_button_hight_score[index].NeedAction())
		{
			switch (index)
			{
			case 0:// cancle
				game->_state_gameplay._hud_score._have_hight_score = false;
				_state++;
				break;
			case 1:// rate
				game->_state_gameplay._hud_share.Init();
				game->_state_gameplay._hud_score._have_hight_score = false;
				_state++;
				break;
			default:
				break;
			}
			for (int i = 0; i < HIGHT_SCORE_NUM_BUTTON; i++)
			{
				if (_button_hight_score[i]._state != BUTTON_STATE_LOCK && _button_hight_score[i]._state != BUTTON_STATE_HIDE)
				{
					_button_hight_score[i].SetState(BUTTON_STATE_NORMAL);
				}
			}
		}
		return true;
	}
	bool ret = false;
	for (int i = 0; i < GAME()->_num_touches; i++)
	{
		for (int button = 0; button < HIGHT_SCORE_NUM_BUTTON; button++)
		{
			if (_button_hight_score[button]._state == BUTTON_STATE_LOCK || _button_hight_score[button]._state == BUTTON_STATE_HIDE)
			{
				continue;
			}
			int x = _button_hight_score[button].TZ_GetX() - 20;
			int y = _button_hight_score[button].TZ_GetY() - 20;
			int w = _button_hight_score[button].TZ_GetWidth() + 40;
			int h = _button_hight_score[button].TZ_GetHeight() + 40;
			Button *bt = &_button_hight_score[button];
			if (CHECK_POINT_IN_RECT(TOUCHS(i)->x, TOUCHS(i)->y, x, y, w, h))
			{
				if (TOUCHS(i)->_state == TOUCH_DOWN)
				{
					if (bt->_touch_id == -1)
					{
						//if (!_play_sound_button_gameplay)
						//{
						//_play_sound_button_gameplay = true;
						//GAME()->PlaySFX(SFX_BUTTON);
						//}
						bt->_touch_id = TOUCHS(i)->_id;
						bt->SetState(BUTTON_STATE_SELECT);
					}
				}
				else if (TOUCHS(i)->_state == TOUCH_DRAG)
				{
					if (bt->IsAction(TOUCHS(i)->_id))
					{
						//bt->SetState(BUTTON_STATE_SELECT);
					}
				}
				else if (TOUCHS(i)->_state == TOUCH_UP)
				{
					if (bt->IsAction(TOUCHS(i)->_id))
					{
						//_play_sound_button_gameplay = false;
						bt->SetState(BUTTON_STATE_ACTIVE);
						printf("\n button = %d", button);
					}
				}
				if (bt->_touch_id != -1)
				{
					ret = true;
				}
			}
			else
			{
				if (bt->IsAction(TOUCHS(i)->_id))
				{
					if (TOUCHS(i)->_state == TOUCH_UP)
					{
						//_play_sound_button_gameplay = false;
						bt->_touch_id = -1;
						bt->SetState(BUTTON_STATE_ACTIVE);
					}
					ret = true;
				}
			}
		}
	}
	return ret;
}

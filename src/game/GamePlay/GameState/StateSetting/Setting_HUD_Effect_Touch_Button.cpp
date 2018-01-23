#include "pch.h"
#include "../../../GameCore/CGame.h"

void SettingEffectTouchButton::EffectWaveButton::Init(float pos_x, float pos_y)
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	_point_begin.X = pos_x;
	_point_begin.Y = pos_y;
	_point_draw = _point_begin;
	_state = 1;
	_percent = 0.0f;
	_speed = 0.03f;
}

void SettingEffectTouchButton::EffectWaveButton::Update()
{
	if (_state == 1)
	{
		_percent += _speed;
		if (_percent > 1.0f)
		{
			_percent = 1.0f;
			_state = 2;
		}
	}
}

void SettingEffectTouchButton::EffectWaveButton::Render()
{
	float frame_width = GET_SPRITE(SPRITEID_HUD_SETTING)->GetFrameWidth(1);
	float frame_height = GET_SPRITE(SPRITEID_HUD_SETTING)->GetFrameHeight(1);
	float radius = frame_width / 2.0f + _percent * (frame_width / 4.0f);
	int opacity = 40.0f * (1.0f - _percent);//100.0f * (1.0f - _percent) / 0.8f;
	if (_state == 1)
	{
		float draw_x = _point_draw.X + frame_width / 2;
		float draw_y = _point_draw.Y + frame_height / 2;

		G()->SetColor(0xFFFFFFFF);
		G()->SetOpacity(opacity);
		for (float i = radius - 3.0f; i <= radius; i += 0.5f)
		{
			G()->DrawCircle(draw_x, draw_y, i, 10, true);
		}
		G()->SetOpacity(100);
	}
}

bool SettingEffectTouchButton::EffectWaveButton::isFinish()
{
	if (_state == 2)
	{
		return true;
	}
	else
	return false;
}

void SettingEffectTouchButton::Default()
{
	_num_effect_current = 0;
}

void SettingEffectTouchButton::UpdateManager()
{
	if (_num_effect_current > 0)
	{
		for (int i = 0; i < _num_effect_current; i++)
		{
			_wave_arr[i].Update();
			if (_wave_arr[i].isFinish())
			{
				RemoveEffect(i);
			}
		}
	}
}

void SettingEffectTouchButton::RenderManager()
{
	if (_num_effect_current > 0)
	{
		for (int i = 0; i < _num_effect_current; i++)
		{
			_wave_arr[i].Render();
		}
	}
}

void SettingEffectTouchButton::AddEffect(float pos_x, float pos_y)
{
	if (_num_effect_current == 0)
	{
		_num_effect_current = 1;
		if (_wave_arr != nullptr)
		{
			SAFE_DEL_ARRAY(_wave_arr);
		}
		_wave_arr = new EffectWaveButton[_num_effect_current];
		_wave_arr[0].Init(pos_x, pos_y);
	}
	else if (_num_effect_current > 0)
	{
		int last_num = _num_effect_current;
		EffectWaveButton *arr_backup;
		arr_backup = new EffectWaveButton[last_num];
		for (int i = 0; i < last_num; i++)
		{
			arr_backup[i] = _wave_arr[i];
		}
		_num_effect_current++;
		if (_wave_arr != nullptr)
		{
			SAFE_DEL_ARRAY(_wave_arr);
		}
		_wave_arr = new EffectWaveButton[_num_effect_current];
		for (int i = 0; i < last_num; i++)
		{
			_wave_arr[i] = arr_backup[i];
		}
		_wave_arr[last_num].Init(pos_x, pos_y);
		if (arr_backup != nullptr)
		{
			SAFE_DEL_ARRAY(arr_backup);
		}
	}
}

void SettingEffectTouchButton::RemoveEffect(int index)
{
	if (_num_effect_current == 1)
	{
		_num_effect_current = 0;
		if (_wave_arr != nullptr)
		{
			SAFE_DEL_ARRAY(_wave_arr);
		}
	}
	else if (_num_effect_current > 1)
	{
		EffectWaveButton *new_arr;
		int new_num = _num_effect_current - 1;
		new_arr = new EffectWaveButton[new_num];
		int counter = 0;
		for (int i = 0; i < _num_effect_current; i++)
		{
			if (i == index)
			{

			}
			else
			{
				new_arr[counter] = _wave_arr[i];
				counter++;
			}
		}
		if (_wave_arr != nullptr)
		{
			SAFE_DEL_ARRAY(_wave_arr);
		}
		_wave_arr = new EffectWaveButton[new_num];
		for (int i = 0; i < new_num; i++)
		{
			_wave_arr[i] = new_arr[i];
		}
		_num_effect_current = new_num;
		if (new_arr != nullptr)
		{
			SAFE_DEL_ARRAY(new_arr);
		}
	}
}

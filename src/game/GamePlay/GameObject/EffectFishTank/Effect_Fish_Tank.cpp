#include "pch.h"
#include "../../../GameCore/CGame.h"

#define BEGIN_HEIGHT_CHECK		425.0f
#define WIDTH_COLLISION			440.0f

void EffectFishTank::DefaultManager()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	_point_a.X = game->_point_o.X + 40;
	_point_a.Y = game->_point_o.Y + BEGIN_HEIGHT_CHECK + 40;
	_point_b.X = game->_point_right_bottom.X - 40;
	_point_b.Y = game->_point_o.Y + BEGIN_HEIGHT_CHECK + 40;
	_point_d.X = game->_point_o.X + 40;
	_point_d.Y = game->_point_right_bottom.Y - 40;
	_point_c.X = game->_point_right_bottom.X - 40;
	_point_c.Y = game->_point_right_bottom.Y - 40;

	_rect_a.X = _point_a.X - WIDTH_COLLISION;
	_rect_a.Y = _point_a.Y - WIDTH_COLLISION;
	_rect_a.W = game->_screen_width + WIDTH_COLLISION * 2;
	_rect_a.H = WIDTH_COLLISION;

	_rect_b.X = _point_b.X;
	_rect_b.Y = _point_b.Y;
	_rect_b.W = WIDTH_COLLISION;
	_rect_b.H = (game->_screen_height - BEGIN_HEIGHT_CHECK);
	
	_rect_c.X = _point_d.X - WIDTH_COLLISION;
	_rect_c.Y = _point_d.Y;
	_rect_c.W = game->_screen_width + WIDTH_COLLISION * 2;
	_rect_c.H = WIDTH_COLLISION;

	_rect_d.X = _point_a.X - WIDTH_COLLISION;
	_rect_d.Y = _point_a.Y;
	_rect_d.W = WIDTH_COLLISION;
	_rect_d.H = (game->_screen_height - BEGIN_HEIGHT_CHECK);

	_num_fish_current = 0;
	if (_arr_fish != nullptr)
	{
		SAFE_DEL_ARRAY(_arr_fish);
	}

	_time_counter_add_fish = 360;
}

void EffectFishTank::UpdateManager()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	if (_num_fish_current > 0)
	{
		for (int i = 0; i < _num_fish_current; i++)
		{
			_arr_fish[i].Update();
			if (_arr_fish[i].isFinish())
			{
				Delete(i);
			}
		}
	}

	/*_time_counter_add_fish--;
	if (_time_counter_add_fish < 0)
	{
		_time_counter_add_fish = 360;
		Add();
	}*/
}

void EffectFishTank::RenderManager()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	/*Render Tank Collision*/
	/*G()->SetColor(0xFFFFFFFF);
	G()->DrawLine(_point_a.X, _point_a.Y, _point_b.X, _point_b.Y);
	G()->SetColor(0xFFFFFFFF);
	G()->DrawLine(_point_b.X, _point_b.Y, _point_c.X, _point_c.Y);
	G()->SetColor(0xFFFFFFFF);
	G()->DrawLine(_point_c.X, _point_c.Y, _point_d.X, _point_d.Y);
	G()->SetColor(0xFFFFFFFF);
	G()->DrawLine(_point_d.X, _point_d.Y, _point_a.X, _point_a.Y);*/
	/*End*/

	//G()->FillRect(_rect_d.X, _rect_d.Y, _rect_d.W, _rect_d.H);

	if (_num_fish_current > 0)
	{
		for (int i = 0; i < _num_fish_current; i++)
		{
			_arr_fish[i].Render();
		}
	}

	//G()->SetColor(0xFFFFFFFF);
	//G()->FillRect(game->_point_o.X + game->_screen_width / 2, game->_point_o.Y + game->_screen_height / 2 + BEGIN_HEIGHT_CHECK / 2, 10, 10);
}

void EffectFishTank::Add()
{
	if (_num_fish_current == 0)
	{
		_num_fish_current = 1;
		if (_arr_fish != nullptr)
		{
			SAFE_DEL_ARRAY(_arr_fish);
		}
		_arr_fish = new Fish[_num_fish_current];
		_arr_fish[0].Init();
	}
	else if (_num_fish_current > 0)
	{
		int last_num = _num_fish_current;
		Fish *arr_backup;
		arr_backup = new Fish[last_num];
		for (int i = 0; i < last_num; i++)
		{
			arr_backup[i] = _arr_fish[i];
		}
		_num_fish_current++;
		if (_arr_fish != nullptr)
		{
			SAFE_DEL_ARRAY(_arr_fish);
		}
		_arr_fish = new Fish[_num_fish_current];
		for (int i = 0; i < last_num; i++)
		{
			_arr_fish[i] = arr_backup[i];
		}
		_arr_fish[last_num].Init();
		if (arr_backup != nullptr)
		{
			SAFE_DEL_ARRAY(arr_backup);
		}
	}
}

void EffectFishTank::Add(float pos_x, float pos_y)
{
	if (_num_fish_current == 0)
	{
		_num_fish_current = 1;
		if (_arr_fish != nullptr)
		{
			SAFE_DEL_ARRAY(_arr_fish);
		}
		_arr_fish = new Fish[_num_fish_current];
		_arr_fish[0].Init(pos_x, pos_y);
	}
	else if (_num_fish_current > 0)
	{
		int last_num = _num_fish_current;
		Fish *arr_backup;
		arr_backup = new Fish[last_num];
		for (int i = 0; i < last_num; i++)
		{
			arr_backup[i] = _arr_fish[i];
		}
		_num_fish_current++;
		if (_arr_fish != nullptr)
		{
			SAFE_DEL_ARRAY(_arr_fish);
		}
		_arr_fish = new Fish[_num_fish_current];
		for (int i = 0; i < last_num; i++)
		{
			_arr_fish[i] = arr_backup[i];
		}
		_arr_fish[last_num].Init(pos_x, pos_y);
		if (arr_backup != nullptr)
		{
			SAFE_DEL_ARRAY(arr_backup);
		}
	}
}

void EffectFishTank::Delete(int index)
{
	if (_num_fish_current == 1)
	{
		_num_fish_current = 0;
		if (_arr_fish != nullptr)
		{
			SAFE_DEL_ARRAY(_arr_fish);
		}
	}
	else if (_num_fish_current > 1)
	{
		Fish *new_arr;
		int new_num = _num_fish_current - 1;
		new_arr = new Fish[new_num];
		int counter = 0;
		for (int i = 0; i < _num_fish_current; i++)
		{
			if (i == index)
			{

			}
			else
			{
				new_arr[counter] = _arr_fish[i];
				counter++;
			}
		}
		if (_arr_fish != nullptr)
		{
			SAFE_DEL_ARRAY(_arr_fish);
		}
		_arr_fish = new Fish[new_num];
		for (int i = 0; i < new_num; i++)
		{
			_arr_fish[i] = new_arr[i];
		}
		_num_fish_current = new_num;
		if (new_arr != nullptr)
		{
			SAFE_DEL_ARRAY(new_arr);
		}
	}
}

void EffectFishTank::FreeMemory()
{
	_num_fish_current = 0;
	if (_arr_fish != nullptr)
	{
		SAFE_DEL_ARRAY(_arr_fish);
	}
}

void EffectFishTank::Fish::Init()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	point_draw.X = game->_point_o.X + game->_screen_width / 2;
	point_draw.Y = game->_point_o.Y + game->_screen_height / 2 + BEGIN_HEIGHT_CHECK / 2;
	angle_current = CMath::RANDOM(0, 350);
	power_current = 0.5f;
	vector_go.x = MCOS(angle_current) * power_current;
	vector_go.y = MSIN(angle_current) * power_current;
	state = 1;
	dir_like = CMath::RANDOM(0, 1) == 0 ? -1.0f : 1.0f;
	time_random = CMath::RANDOM(4, 8) * 60;
	last_angle = angle_current;
	no_collsion = true;
	flag_bug_return_home = false;
	opacity_fish = 0;
}

void EffectFishTank::Fish::Init(float pos_x, float pos_y)
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	point_draw.X = pos_x;
	point_draw.Y = pos_y;
	angle_current = CMath::RANDOM(0, 350);
	power_current = 0.5f;
	vector_go.x = MCOS(angle_current) * power_current;
	vector_go.y = MSIN(angle_current) * power_current;
	state = 1;
	dir_like = CMath::RANDOM(0, 1) == 0 ? -1.0f : 1.0f;
	time_random = CMath::RANDOM(4, 8) * 60;
	last_angle = angle_current;
	no_collsion = true;
	flag_bug_return_home = false;
	opacity_fish = 0;
}

void EffectFishTank::Fish::Update()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	int num_collision = 0;
	if (state == 1)
	{
		opacity_fish += 2;
		if (opacity_fish > 100)
		{
			opacity_fish = 100;
		}
		PinePoint point_check;
		point_check = point_draw;
		int collision = 0;
		if (CHECK_POINT_IN_RECT(point_check.X, point_check.Y, game->_state_gameplay._effect_fish_tank._rect_a.X, game->_state_gameplay._effect_fish_tank._rect_a.Y, game->_state_gameplay._effect_fish_tank._rect_a.W, game->_state_gameplay._effect_fish_tank._rect_a.H))
		{
			if (no_collsion)
			{
				no_collsion = false;
				last_angle = angle_current + 180.0f;
				if (last_angle > 360.0f)
				{
					last_angle -= 360.0f;
				}
			}
			collision = 1;
			if (CMath::ABSOLUTE_VALUE(angle_current - last_angle) <= 0.0f)
			{

			}
			else
			{
				if (!flag_bug_return_home)
				{
					angle_current += dir_like;
				}
			}
			if (angle_current > 360.0f)
			{
				angle_current -= 360.0f;
			}
			if (angle_current < 0.0f)
			{
				angle_current += 360.0f;
			}
			num_collision++;
		}
		if (CHECK_POINT_IN_RECT(point_check.X, point_check.Y, game->_state_gameplay._effect_fish_tank._rect_b.X, game->_state_gameplay._effect_fish_tank._rect_b.Y, game->_state_gameplay._effect_fish_tank._rect_b.W, game->_state_gameplay._effect_fish_tank._rect_b.H))
		{
			if (no_collsion)
			{
				no_collsion = false;
				last_angle = angle_current + 180.0f;
				if (last_angle > 360.0f)
				{
					last_angle -= 360.0f;
				}
			}
			collision = 2;
			if (CMath::ABSOLUTE_VALUE(angle_current - last_angle) <= 0.0f)
			{

			}
			else
			{
				if (!flag_bug_return_home)
				{
					angle_current += dir_like;
				}
			}
			if (angle_current > 360.0f)
			{
				angle_current -= 360.0f;
			}
			if (angle_current < 0.0f)
			{
				angle_current += 360.0f;
			}
			num_collision++;
		}
		if (CHECK_POINT_IN_RECT(point_check.X, point_check.Y, game->_state_gameplay._effect_fish_tank._rect_c.X, game->_state_gameplay._effect_fish_tank._rect_c.Y, game->_state_gameplay._effect_fish_tank._rect_c.W, game->_state_gameplay._effect_fish_tank._rect_c.H))
		{
			if (no_collsion)
			{
				no_collsion = false;
				last_angle = angle_current + 180.0f;
				if (last_angle > 360.0f)
				{
					last_angle -= 360.0f;
				}
			}
			collision = 3;
			if (CMath::ABSOLUTE_VALUE(angle_current - last_angle) <= 0.0f)
			{

			}
			else
			{
				if (!flag_bug_return_home)
				{
					angle_current += dir_like;
				}
			}
			if (angle_current > 360.0f)
			{
				angle_current -= 360.0f;
			}
			if (angle_current < 0.0f)
			{
				angle_current += 360.0f;
			}
			num_collision++;
		}
		if (CHECK_POINT_IN_RECT(point_check.X, point_check.Y, game->_state_gameplay._effect_fish_tank._rect_d.X, game->_state_gameplay._effect_fish_tank._rect_d.Y, game->_state_gameplay._effect_fish_tank._rect_d.W, game->_state_gameplay._effect_fish_tank._rect_d.H))
		{
			if (no_collsion)
			{
				no_collsion = false;
				last_angle = angle_current + 180.0f;
				if (last_angle > 360.0f)
				{
					last_angle -= 360.0f;
				}
			}
			collision = 4;
			if (CMath::ABSOLUTE_VALUE(angle_current - last_angle) <= 0.0f)
			{

			}
			else
			{
				if (!flag_bug_return_home)
				{
					angle_current += dir_like;
				}
			}
			if (angle_current > 360.0f)
			{
				angle_current -= 360.0f;
			}
			if (angle_current < 0.0f)
			{
				angle_current += 360.0f;
			}
			num_collision++;
		}

		if (num_collision != 0)
		{
			power_current += 0.009f;
			if (power_current > 2.5f)
			{
				power_current = 2.5f;
			}
		}
		else
		{
			flag_bug_return_home = false;
			no_collsion = true;
			last_angle = angle_current;
			power_current -= 0.005f;
			if (power_current < 0.5f)
			{
				power_current = 0.5f;
			}

			time_random--;
			if (time_random < 0)
			{
				dir_like = CMath::RANDOM(0, 1) == 0 ? -1.0f : 1.0f;
				time_random = CMath::RANDOM(4, 8) * 60;
			}
		}

		float distance = CMath::DISTANCE(point_draw.X, point_draw.Y, game->_point_o.X + game->_screen_width / 2, game->_point_o.Y + game->_screen_height / 2 + BEGIN_HEIGHT_CHECK / 2);
		if (distance >(game->_screen_height * 0.8f) && !flag_bug_return_home)
		{
			flag_bug_return_home = true;
			angle_current = CMath::ANGLE(point_draw.X, point_draw.Y, game->_point_o.X + game->_screen_width / 2, game->_point_o.Y + game->_screen_height / 2 + BEGIN_HEIGHT_CHECK / 2);
		}


		vector_go.x = MCOS(angle_current) * power_current;
		vector_go.y = MSIN(angle_current) * power_current;
		point_draw.X += vector_go.x;
		point_draw.Y += vector_go.y;
	}
}

void EffectFishTank::Fish::Render()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	float draw_x = point_draw.X;
	float draw_y = point_draw.Y;

	float angle = 0.0f;
	SVector2 vecter_a;
	vecter_a.x = 0.0f;
	vecter_a.y = -1.0f;

	angle = CMath::ANGLE_OF_2_VECTOR(vecter_a.x, vecter_a.y, vector_go.x, vector_go.y);
	float opacity = (opacity_fish / 100.0f) * game->_state_gameplay._master_game._opacity_grid;
	float decrease = (BEGIN_HEIGHT_CHECK + 150.0f) - draw_y;
	if (decrease >= 0.0f)
	{
		decrease = 20.0f / decrease;
		opacity *= decrease;
		if (opacity < 10.0f)
		{
			opacity = 0.0f;
		}
	}
	
	float scale = 1.0f;
	float percent_scale_loss = ((1.0f * game->_state_gameplay._master_game._opacity_grid) - opacity) / (1.0f * game->_state_gameplay._master_game._opacity_grid);
	if (percent_scale_loss < 0.0f)
	{
		percent_scale_loss = 0.0f;
	}
	scale -= percent_scale_loss * 0.1f;
	//printf("\nscale: %f", scale);

	G()->SetOpacity((int)opacity);
	CMatrix4x4Util matrix_fish;
	matrix_fish.reNew();
	matrix_fish.DoScale(scale, scale, draw_x, draw_y);
	matrix_fish.DoRotate(angle, draw_x, draw_y);
	G()->SetTransform(matrix_fish.toPineTranform());
	/*if (dir_like == -1)
	{
		G()->SetColorMask(0xFFFF0000);
	}*/
	GET_SPRITE(SPRITEID_OBJECT_02)->DrawFrame(G(), 0, draw_x, draw_y);
	G()->ClearColorMask();
	G()->ClearTransform();
	G()->SetOpacity(100);
}

void EffectFishTank::Fish::UpdateDirLike()
{
}

bool EffectFishTank::Fish::isFinish()
{
	return false;
}

#include "pch.h"
#include "../../../GameCore/CGame.h"

void StateTest::UpdateStateTest()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	if (game->_sub_state == k_INIT)
	{
		InitStateTest();
		game->_sub_state = k_LOOP;
	}
	if (game->_sub_state == k_LOOP)
	{
		_effect_wave_circle.Update();
		game->_state_gameplay._hud_background.Update();
	}
}

void StateTest::RenderStateTest()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	//matrix_game.Render();
	game->_state_gameplay._hud_background.Render();
}

bool StateTest::UpdateControl()
{
	return false;
}

void StateTest::InitStateTest()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	matrix_game.Init();
	PointIndex point_center_wave;
	point_center_wave.column = 3;
	point_center_wave.row = 3;
	_effect_wave_circle.Default(7, 7);

	game->_state_gameplay._hud_background.Init();
	//game->_state_gameplay._hud_background.SetColorEnd(0xFF488C87);
}

void StateTest::Matrix::Render()
{
	for (int i = 0; i < max_row; i++)
	{
		for (int j = 0; j < max_colum; j++)
		{
			arr_draw[i][j].Render();
		}
	}
}

void StateTest::Matrix::Update()
{
	
}

void StateTest::Matrix::Init()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	max_row = 7;
	max_colum = 7;


	float scale_grap = 0.375f * (max_row - 2);
	int get_value = 15;
	grap.width = get_value;
	grap.height = get_value;

	int width = (game->_screen_width - (GRAP_GRID * 2 + (max_colum - 1) * grap.width)) / max_colum;
	int height = width;
	block_width = width;
	block_height = height;


	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			arr_draw[i][j].Init(j, i);
		}
	}
}

void StateTest::Block::Render()
{
	ColorBorn *game = (ColorBorn*)GAME()->_current_game;
	float draw_x = point_begin_pixel.X + game->_state_example.matrix_game.block_width / 2;
	float draw_y = point_begin_pixel.Y + game->_state_example.matrix_game.block_height / 2;
	draw_x += game->_state_example._effect_wave_circle._matrix_pos_current[point_begin.row][point_begin.column].X;
	draw_y += game->_state_example._effect_wave_circle._matrix_pos_current[point_begin.row][point_begin.column].Y;
	G()->SetColor(0xFFFFFFFF);
	G()->FillCircle(draw_x, draw_y, 20, 5, true);
}

void StateTest::Block::Update()
{
}

void StateTest::Block::Init(int column, int row)
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;

	point_begin.column = column;
	point_begin.row = row;

	int grid_w = game->_state_example.matrix_game.max_colum * game->_state_example.matrix_game.block_width + game->_state_example.matrix_game.grap.width * (game->_state_example.matrix_game.max_colum - 1);
	int grid_h = game->_state_example.matrix_game.max_row * game->_state_example.matrix_game.block_height + game->_state_example.matrix_game.grap.height * (game->_state_example.matrix_game.max_row - 1);

	int new_x = game->_point_o.X + game->_screen_width / 2 - grid_w / 2;
	int new_y = game->_point_o.Y + game->_screen_height / 2 - grid_h / 2;
	point_begin_pixel.X = point_begin.column * (game->_state_example.matrix_game.block_width + game->_state_example.matrix_game.grap.width) + new_x;
	point_begin_pixel.Y = point_begin.row * (game->_state_example.matrix_game.block_height + game->_state_example.matrix_game.grap.height) + new_y;
}

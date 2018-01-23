#include "pch.h"
#include "../../../GameCore/CGame.h"

void GPHudShare::Init()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	_state = -1;
	_percent = 0.0f;
	_speed = 0.1f;
	_frame_height = GET_SPRITE(SPRITEID_HUD_INGAME_SHARE)->GetFrameHeight(0);
	_point_begin.X = game->_point_o.X;
	_point_begin.Y = game->_point_o.Y + game->_screen_height / 2 - _frame_height / 2;
	_point_draw = _point_begin;
	_last_state = game->_state_gameplay._gameplay_state;
	game->_state_gameplay._gameplay_state = 2;

	_opacity_flash = 0.0f;
	GAME()->PlaySFX(SFX_SHARE);
}

void GPHudShare::Update()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	if (_state == -1)
	{
		_opacity_flash += 10.0f;
		if (_opacity_flash > 120.0f)
		{
			_state = 0;
			_percent = 1.0f;
		}
	}
	if (_state == 0)
	{
		_opacity_flash -= 3.0f;
		if (_opacity_flash < 0.0f)
		{
			_opacity_flash = 0.0f;
			_state = 1;
		}
	}
	if (_state == 1)
	{
		_percent += _speed;
		if (_percent > 1.0f)
		{
			_percent = 1.0f;
			_state = 2;
			float draw_x = _point_draw.X;
			float draw_y = _point_draw.Y;
#if defined (MAC_OS)
			PineSocial::SaveScreenToDocument("fadeCapture", draw_x, draw_y, game->_screen_width, _frame_height);
#elif defined (ANDROID_OS)
			sprintf(GAME()->_async_task_manager._share_screen_shot_message, "This game is surprisingly awesome!");
			GAME()->_async_task_manager.AddCommand(CAsyncTasks::enumTypeCommand::COMMAND_TYPE_ASYN_SHARE_SCREEN_SHOT_INTENT);
#endif // MAC_OS
		}
	}
	if (_state == 2)
	{
		_percent += 0.01f;
		if (_percent >= 1.2f)
		{
			_state = 3;
		}
	}
	if (_state == 3)
	{
#ifdef MAC_OS
		char text_share[512];
		sprintf(text_share, "This game is surprisingly awesome! #fade #faded https://itunes.apple.com/us/app/id%d", APPLE_ID);
		PineSocial::ShareImageWithURLDocument(text_share, "fadeCapture");
#endif // MAC_OS
		_state = 4;
	}
	if (_state == 4)
	{
		_percent -= 0.1f;
		if (_percent < 0.0f)
		{
			_percent = 0.0f;
			_state = 5;
			game->_state_gameplay._gameplay_state = _last_state;
		}
	}
}

void GPHudShare::Render()
{
	ColorBorn *game = (ColorBorn *)GAME()->_current_game;
	int opacity = (int)(60.0f * _percent);
	if (opacity > 100.0f)
	{
		opacity = 100.0f;
	}
	G()->SetOpacity(opacity);
	G()->SetColor(0xFF000000);
	G()->FillFullScreen(true);
	G()->SetOpacity(100);
	
	opacity = (int)(100.0f * _percent);
	if (opacity > 100.0f)
	{
		opacity = 100.0f;
	}
	G()->SetOpacity(opacity);
	float draw_x = _point_draw.X;
	float draw_y = _point_draw.Y;
	if (game->_device_current == DEVICE_CURRENT_IPAD || game->_device_current == DEVICE_CURRENT_I4)
	{
		CMatrix4x4Util matrix_port;
		matrix_port.reNew();
		matrix_port.DoScale(GAME()->_game_context.ScaleOutX, 1.0f, draw_x, draw_y);
		G()->SetTransform(matrix_port.toPineTranform());
		GET_SPRITE(SPRITEID_HUD_INGAME_SHARE)->DrawFrame(G(), 0, draw_x, draw_y);
		G()->ClearTransform();
	}
	else
	{
		GET_SPRITE(SPRITEID_HUD_INGAME_SHARE)->DrawFrame(G(), 0, draw_x, draw_y);
	}
	draw_x = _point_draw.X + 20.0f;
	draw_y = _point_draw.Y + 64.0f;
	GET_SPRITE(SPRITEID_HUD_INGAME_SHARE)->DrawFrame(G(), 1, draw_x, draw_y);
	draw_x = _point_draw.X + 19.0f;
	draw_y = _point_draw.Y + 128.0f;
	GET_SPRITE(SPRITEID_HUD_INGAME_SHARE)->DrawFrame(G(), 2, draw_x, draw_y);
	draw_x = game->_point_right_bottom.X - (750.0f - 594.0f);
	draw_y = _point_draw.Y + 20.0f;
	GET_SPRITE(SPRITEID_HUD_INGAME_SHARE)->DrawFrame(G(), 3, draw_x, draw_y);
	draw_x = game->_point_right_bottom.X - (750.0f - 594.0f);
	draw_y = _point_draw.Y + 77.0f;
	GET_SPRITE(SPRITEID_HUD_INGAME_SHARE)->DrawFrame(G(), 4, draw_x, draw_y);


	float f_width = GET_SPRITE(SPRITEID_HUD_INGAME_SHARE)->GetFrameWidth(1);
	float f_height = GET_SPRITE(SPRITEID_HUD_INGAME_SHARE)->GetFrameHeight(1);
	draw_x = _point_draw.X + 20.0f + f_width + 10.0f;
	draw_y = _point_draw.Y + 64.0f + f_height;
	CMatrix4x4Util matrix_normal;
	matrix_normal.reNew();
	matrix_normal.DoScale(0.475f, 0.475f, draw_x, draw_y);
	G()->SetTransform(matrix_normal.toPineTranform());
	GET_SPRITE(SPRITEID_FONT_SCORE_INGAME)->DrawAnsiTextFormat(G(), draw_x, draw_y, _LEFT, "%lld", game->_state_gameplay._user._best_score);
	G()->ClearTransform();

	G()->SetOpacity(100);

	/*Flash screen*/
	G()->SetOpacity((int)_opacity_flash);
	G()->SetColor(0xFFFFFFFF);
	G()->FillFullScreen(true);
	G()->SetOpacity(100);
	/*End*/
}

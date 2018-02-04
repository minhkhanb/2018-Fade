#include "pch.h"
#include "../../GameCore/CGame.h"
#include "../../GameCore/Os_Functions.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <memory>
#include <functional>

using std::string;
using std::cout;
using std::endl;
using std::function;

using namespace std;
using namespace Pine::Platform;
using namespace Pine::Io::Interface;
using namespace Pine::Io;
using namespace Pine::ServiceShell;

TopeBox_PromoGame::TopeBox_PromoGame()
{

}

TopeBox_PromoGame::~TopeBox_PromoGame()
{

}

void TopeBox_PromoGame::ResetPromoInfo()
{
	_is_ready = false;
	_renderx = 0;
	_rendery = 0;
	_touch_id = -1;
	_has_download = false;
	sprintf(_link_store, "%s", "linkStore");
	_is_need_reload = false;
	_icon_scale_state = 0;
	_icon_scale_time = 1.5f*FPS_MAX;
	_icon_scaleEff_speed = 0.02f;
	_icon_scaleEff = 0;
	_reGetTopeboxInfo = false;
}
void TopeBox_PromoGame::InitPromo(float x, float y, int w, int h, enumType type, enumPos pos)
{
	_is_ready = false;
	_renderx = 0;
	_rendery = 0;
	_touch_id = -1;
	_icon_w = w;
	_icon_h = h;
	_has_download = false;
	sprintf(_link_store, "%s", "linkStore");
	_is_need_reload = false;
	_icon_scale_state = 0;
	_icon_scale_time = 1.5f*FPS_MAX;
	_icon_scaleEff_speed = 0.02f;
	_icon_scaleEff = 0;
	_reGetTopeboxInfo = false;
	_type = type;
	popup_close = false;
	popup_active = false;
	count_show_popup = 0;

	_button_close.x = -10;
	_button_close.y = 10;
	_button_close.w = 60;
	_button_close.h = 60;

	count_show_popup = 0;
	popup_render = false;
	icon_render = false;
	_pos = pos;
}
void TopeBox_PromoGame::RenderPromo(float x, float y)
{
	if (_is_need_reload)
	{
		LoadImageToLocal();
		_is_need_reload = false;
	}

	if (_reGetTopeboxInfo)
	{
		_reGetTopeboxInfo = false;
		GetPromoInfo();
	}

	if (!_is_ready)
	{
		return;
	}

	float scaleEff;

	if (_type == enumType::ICON)
	{
		_renderx = x;
		_rendery = y;

		scaleEff = 1.0f;
		if (_touch_id != -1)
		{
			scaleEff = 1.1f;
		}
		else
		{
			switch (_icon_scale_state)
			{
			case 0://normal
				_icon_scale_time--;
				if (_icon_scale_time <= 0)
				{
					_icon_scale_state = 1;
					_icon_scaleEff_speed = 0.02f;
				}
				break;
			case 1://zoom in
				_icon_scaleEff += _icon_scaleEff_speed;
				if (_icon_scaleEff >= 0.2f)
				{
					_icon_scaleEff = 0.2f;
					_icon_scale_state = 2;
					_icon_scaleEff_speed = 0.0075f;
				}
				break;
			case 2:// zoom out
				_icon_scaleEff += -_icon_scaleEff_speed;
				_icon_scaleEff_speed *= 1.1f;
				if (_icon_scaleEff <= 0)
				{
					_icon_scaleEff = 0;
					_icon_scale_state = 0;
					_icon_scale_time = 2.0f * FPS_MAX;
				}
				break;
			default:
				break;
			}
		}

		G()->SetScale((scaleEff + _icon_scaleEff) *_icon_scale_size, (scaleEff + _icon_scaleEff) * _icon_scale_size, _renderx + (_icon_w / 2), _rendery + (_icon_h / 2));
		_game_icon.DrawImageWithRect(G(), _renderx, _rendery);
		G()->ClearScale();
		GET_SPRITE(SPRITEID_FONT_SCORE_INGAME)->_char_spacing = 2;
		G()->SetScale((scaleEff + _icon_scaleEff) *_icon_scale_size*1.2f, (scaleEff + _icon_scaleEff) *_icon_scale_size*1.2f, (_renderx + 55 + _icon_w) - 75, _rendery + _icon_h * 1.3f + 25);
		GET_SPRITE(SPRITEID_FONT_SCORE_INGAME)->DrawAnsiTextFormat(G(), _renderx + 55 + _icon_w - 70, _rendery + _icon_h * 1.3f + 25, _HCENTER | _VCENTER, "%s", _des);
		G()->ClearScale();

	}


	if (_type == enumType::POPUP)
	{


		if (_icon_w < k_SCREEN_WIDTH)
		{
			_renderx = k_SCREEN_WIDTH / 2 - _icon_w / 2;
		}
		else
		{
			_renderx = 0;
		}

		if (_icon_h < k_SCREEN_HEIGHT)
		{
			_rendery = k_SCREEN_HEIGHT / 2 - _icon_h / 2;
		}
		else
		{
			_rendery = 0;
		}

		scaleEff = 1.0f;

		G()->SetScale(1.0f *_icon_scale_size, 1.0f * _icon_scale_size, _renderx, _rendery);
		_game_icon.DrawImageWithRect(G(), _renderx, _rendery);
		G()->ClearScale();

		if (count_show_popup == 0)
		{
			count_show_popup = TIME_SHOW_CLOSE_BUTTON;
		}
		if ((int)count_show_popup / 60 == 0)
		{
#if (PROMO_DATA_IS_READY)
			GET_SPRITE(SPRITEID_HUD_PROMO)->DrawFrame(G(), 0, _button_close.x, _button_close.y);
#endif
		}
	}


}
bool TopeBox_PromoGame::UpdateTouchPromo()
{
	bool ret = false;
	if (!_is_ready)
	{
		return ret;
	}

	for (int i = GAME()->_num_touches - 1; i >= 0; i--)
	{
		if (_type == enumType::ICON && icon_render)
		{
			if (CHECK_POINT_IN_RECT(TOUCHS(i)->x, TOUCHS(i)->y, _renderx, _rendery, _icon_w * 2, _icon_h * 2))
			{
				if (TOUCHS(i)->_state == TOUCH_DOWN)
				{
					if (_touch_id == -1 && !_has_download)
					{
						_touch_id = TOUCHS(i)->_id;
					}
				}
				else if (TOUCHS(i)->_state == TOUCH_DRAG)
				{

				}
				else if (TOUCHS(i)->_state == TOUCH_UP)
				{
					if (_touch_id == TOUCHS(i)->_id)
					{
						_touch_id = -1;
						ret = true;
						_has_download = true;
						icon_render = false;
					}

				}
			}
			else
			{
				if (_touch_id == TOUCHS(i)->_id)
				{
					if (TOUCHS(i)->_state == TOUCH_UP)
					{
						_touch_id = -1;
						ret = true;
					}
				}
			}
		}

		if (_type == enumType::POPUP)
		{
			if (CHECK_POINT_IN_RECT(TOUCHS(i)->x, TOUCHS(i)->y, _button_close.x, _button_close.y, _button_close.w, _button_close.h) && popup_render)
			{
				if (TOUCHS(i)->_state == TOUCH_DOWN)
				{
					_touch_id = TOUCHS(i)->_id;
				}
				else if (TOUCHS(i)->_state == TOUCH_DRAG)
				{

				}
				else if (TOUCHS(i)->_state == TOUCH_UP)
				{
					if (_touch_id == TOUCHS(i)->_id)
					{
						_touch_id = -1;
						ret = true;
						popup_close = true;
						popup_render = false;
						count_skip_popup++;
						TOUCHS(i)->_state = TOUCH_DRAG;
					}
				}

			}

			if (CHECK_POINT_IN_RECT(TOUCHS(i)->x, TOUCHS(i)->y, _renderx, _rendery, _icon_w, _icon_h) && popup_render)
			{

				if (TOUCHS(i)->_state == TOUCH_DOWN)
				{
					if (_touch_id == -1 && !_has_download)
					{
						_touch_id = TOUCHS(i)->_id;
					}
				}
				else if (TOUCHS(i)->_state == TOUCH_DRAG)
				{

				}
				else if (TOUCHS(i)->_state == TOUCH_UP)
				{
					if (_touch_id == TOUCHS(i)->_id)
					{
						_touch_id = -1;
						ret = true;
						_has_download = true;

					}

				}
			}
			else
			{
				if (TOUCHS(i)->_state == TOUCH_DOWN)
				{
					//PDEBUG("\n touch modal bg");
				}
			}

		}



	}
	if (_touch_id != -1)
	{
		ret = true;
	}
	return ret;
}
bool TopeBox_PromoGame::PromoIsReady()
{
	return _is_ready;
}

bool TopeBox_PromoGame::PromoHasTouchDown()
{
	return _has_download;
}

void TopeBox_PromoGame::UpdatePromoInfo() {
	revision = 0;
#if defined (ANDROID_OS)
	if (Device::RemoteConfigGetInteger("GamePromoteVersion") != NULL)
	{
		revison = (int)Device::RemoteConfigGetInteger("GamePromoteVersion");
	}
	else {
		revison = USER()._game_promo_revision;
	}
#endif
#if (PROMO_SAVE_IS_READY)
	if (revision != USER()._game_promo_revision && revision >= 0)
	{
		USER()._game_promo_revision = revision;
		USER()._game_promo_has_show = true;
		USER().DataSave();
		GetPromoData();

	}
	else
#endif
	{
		_is_need_reload = true;
		config_downloaded = true;
		popup_active = true;
	}
}

void TopeBox_PromoGame::GetConfigData(char url[256]) {
#if defined (ANDROID_OS)
	sprintf(save_file_config, "%s", url);
	GAME()->_async_task_manager._firebase_file_type = CAsyncTasks::enumFirebaseDownloadFileType::FIREBASE_TYPE_CONFIG;
	GAME()->_async_task_manager.AddCommand(CAsyncTasks::enumTypeCommand::COMMAND_TYPE_ASYN_FIREBASE_DOWNLOAD_CONFIG);
#endif
}

void TopeBox_PromoGame::GetPromoData() {
#if defined (ANDROID_OS)
	//PDEBUG("\n DOWNLOAD_ICON");
	GAME()->_async_task_manager._firebase_file_type = CAsyncTasks::enumFirebaseDownloadFileType::FIREBASE_TYPE_ICON;
	GAME()->_async_task_manager.AddCommand(CAsyncTasks::enumTypeCommand::COMMAND_TYPE_ASYN_FIREBASE_DOWNLOAD_ICON);
#endif
}

void TopeBox_PromoGame::LoadImageToLocal() {
	_game_icon.FreeTexture(G());
	_game_icon.SetTextureMaxSize(_icon_w, _icon_h);

	if (_game_icon.CreateImageFromPNGinDocument(G(), GAME_ICON_FILE_NAME) > 0)
	{
		if (_type == enumType::ICON)
		{
			_icon_scale_size = (float)96 / _game_icon.GetWidth();
		}
		if (_type == enumType::POPUP)
		{
			_icon_scale_size = 1.0f;

			float scaleX, scaleY;
			if (_screen_width > _screen_height)
			{
				scaleX = _screen_width / 960.0f;
				scaleY = _screen_height / 640.0f;
			}
			else
			{
				scaleX = _screen_width / 640.0f;
				scaleY = _screen_height / 960.0f;

			}
			_icon_scale_size = scaleX;
			if (scaleX > scaleY)
			{
				_icon_scale_size = scaleY;
			}

		}
		_icon_w = (int)(_game_icon.GetWidth() * _icon_scale_size);
		_icon_h = (int)(_game_icon.GetHeight() * _icon_scale_size);
		_is_ready = true;
		config_downloaded = true;
		popup_active = true;
	}
	else {
		GetPromoData();
	}
}

void TopeBox_PromoGame::GetDataInfo() {

#if defined (ANDROID_OS)
	if (Device::RemoteConfigGetString("GamePromoting") != NULL)
	{
		if (!ICON_PROMO)
		{
			sprintf(remoteConfigUrl, "%s", Device::RemoteConfigGetString("GamePromoting"));
		}
		else
		{
			sprintf(remoteConfigUrl, "%s", FIREBASE_ICON);
		}
		GAME()->_topebox_game.GetDataRemoteConfig(remoteConfigUrl);
	}
	else {
		GAME()->time_get_remote_config = TIME_REMOTE_CONFIG;
	}
#endif
}

void TopeBox_PromoGame::GetPromoInfo() {
#if !defined (_WINDOWS)
	if (!Device::IsNetworkAvailable())
	{
		return;
	}
#endif
	GAME()->_topebox_game.UpdatePromoInfo();
}



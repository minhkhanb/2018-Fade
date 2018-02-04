/**
*	will be included in CGame.h
*	for include specific *.h
*/
//#include "some_classes.h"

#include "../GamePlay/GameObject/MenuSystem.h"
#include "../GamePlay/GameObject/SpriteList.h"
#include "../GamePlay/GameObject/WorldGame.h"
#include "../GamePlay/GameObject/Jumper.h"

#include "../Lib/PineHighScore.h"
#include "../Lib/DataType/BufferStream.h"

#include "../GameCore/PineGame.h"

//include game object
#include "../GamePlay/GameObject/SMath/SVector2.h"
#include "../GamePlay/GameObject/SMath/SMath.h"
#include "../GamePlay/GameObject/CMaxtrix4x4Util.h"
#include "../GamePlay/GameObject/CUser.h"
#include "../GamePlay/GameObject/Pine_Date_Time.h"

#include "../GamePlay/GameObject/TransformColor.h"
#include "../GamePlay/GameObject/Acceleration.h"
#include "../GamePlay/GameObject/WaveCircle.h"
#include "../GamePlay/GameObject/EffectFishTank/Effect_Fish_Tank.h"
#include "../GamePlay/GameState/StateGamePlay/GamePlay_Effect_New_Game.h"
#include "../GamePlay/GameState/StateGamePlay/GamePlay_Effect_Type_Clear_Idle.h"
#include "../GamePlay/GameState/StateGamePlay/GamePlay_HUD_BackGround.h"
#include "../GamePlay/GameState/StateGamePlay/GamePlay_HUD_Share.h"
#include "../GamePlay/GameState/StateGamePlay/GamePlay_HUD_Ingame.h"
#include "../GamePlay/GameState/StateGamePlay/GamePlay_HUD_Score.h"
#include "../GamePlay/GameState/StateGamePlay/GamePlay_HUD_End_Game.h"
#include "../GamePlay/GameState/StateGamePlay/GamePlay_HUD_Popup.h"
#include "../GamePlay/GameState/StateGamePlay/GamePlay_HUD_Tutorial.h"
#include "../GamePlay/GameState/StateGamePlay/GamePlay_HUD_Loading.h"
#include "../GamePlay/GameState/StateGamePlay/CGame_GamePlay_Block_Grid.h"
#include "../GamePlay/GameState/StateGamePlay/CGame_GamePlay_Maxtrix_Draw.h"

#include "../GamePlay/GameState/StateSetting/Setting_HUD_Button.h"
#include "../GamePlay/GameState/StateSetting/Setting_HUD_Effect_Touch_Button.h"


//include gameplay
#include "../GamePlay/MainGame/CGame_ColorBorn_Define_Const.h"
#include "../GamePlay/GameState/StateExample/CGame_State_Test.h"
#include "../GamePlay/GameState/StateLogo/CGame_State_Logo.h"
#include "../GamePlay/GameState/StateGamePlay/CGame_State_GamePlay.h"
#include "../GamePlay/GameState/StateSetting/CGame_Setting.h"

#include "../GamePlay/MainGame/ColorBorn.h"

#include "../GamePlay/GameObject/Topebox_PromoGame.h"


//include lib
#include "../Lib/PineAdBox.h"

#if defined (ANDROID_OS)
#include "../GamePlay/GameObject/CAsyncTasks.h"
#include "../Lib/PineAdmobAsync.h"
#include "../Lib/PineUnityAdsAsync.h"
#endif




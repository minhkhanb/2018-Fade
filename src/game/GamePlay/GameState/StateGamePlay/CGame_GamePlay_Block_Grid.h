#ifndef __GAMEPLAY_BLOCK_GRID__
#define __GAMEPLAY_BLOCK_GRID__

class BlockGrid
{
public:
	/*Define State*/
#define BLOCK_NORMAL				1
#define BLOCK_WILL_SELECT			2
#define BLOCK_TOUCH_DOWN			3
#define BLOCK_SELECT				4
#define BLOCK_WILL_INVI				5
#define BLOCK_INVI					6
#define BLOCK_REBORN				7
#define BLOCK_TARGET_JOIN			8
#define BLOCK_REFILL_COLOR			9

	/*Define Color*/
#define TYPE_TWELVE_COLOR	     0xFFEE475A
#define TYPE_ELEVEN_COLOR        0xFFF28692
#define TYPE_TEN_COLOR			 0xFF9180EA
#define TYPE_NINE_COLOR          0xFFC1B7F6
#define TYPE_EIGHT_COLOR         0xFF00FF9C
#define TYPE_SEVEN_COLOR         0xFFFE88B2
#define TYPE_SIX_COLOR           0xFFFF5CBC
#define TYPE_FIVE_COLOR          0xFFBD44FB
#define TYPE_FOUR_COLOR          0xFFFA9500
#define TYPE_THREE_COLOR         0xFF0081F0
#define TYPE_TWO_COLOR           0xFF99E10A
#define TYPE_ONE_COLOR           0xFFD4276D

	/*Define Type*/
#define TYPE_CLEAR					-1
#define TYPE_EMPTY					0

#define SCROLL_DOWN_GRID_FAKE		(135.0f)

	COLOR _color;
	void Init(int index_c, int index_r, int type_block);
	
	void RenderBlockNormal(float pos_x = 0.0f, float pos_y = 0.0f);
	void RenderBlockScaleIn(float pos_x = 0.0f, float pos_y = 0.0f);
	void RenderBlockScaleOut(float pos_x = 0.0f, float pos_y = 0.0f);
	void RenderBlockReborn(float pos_x = 0.0f, float pos_y = 0.0f);


	void UpdateStateSelect();
	void UpdateStateTargetJoin();
	void UpdateStateScaleOut();
	void UpdateReborn();

	void CheckCanJoin();

	int GetNumbeBlockEat(bool type_clear);

	void UpdatePos();

	int _state;
	int _type;
	PointIndex _point_begin;
	PinePoint _point_begin_pixel;
	PinePoint _point_draw_pixel;
	TransformColor _transform_color;
	int _is_touch_state;

	struct EffectZoomObjectMax
	{
		int state;
		void Default();
		void Init(int row, int column, int p_bonus);
		void Render(float pos_x = 0.0f, float pos_y = 0.0f);
		void Update();
		bool isZoomFinish();
		bool isOverPercent(float percent);
		float getCurrentPercent();
		bool isRunning();
		bool isFinish();

		PointIndex effect_point_begin;
		PinePoint effect_point_begin_pixel;
		PinePoint effect_point_draw_pixel;
		int effect_is_touch_state;
		int effect_state_block;
		int effect_type;
		COLOR effect_color;

		float effect_radius_begin;
		float effect_radius;
		float effect_radius_target;
		float effect_speed;
		int point_bonus;
		bool is_type_clear;
		COLOR effect_type_clear_color_target;
		void DefaultEffectTypeClear();
		void InitEffectTypeClear();
		void UpdateEffectTypeClear();
		int effect_type_clear_type_color;
		TransformColor effect_type_clear_transform_color;
		void SetBigRadius();
	};
	EffectZoomObjectMax _effect_zoom_object_max;

	struct EffectZoomObjectScaleIn
	{
		int state;
		void Default();
		int point_bonus;
		void InitPointBonus(int point);
		void Init(int row, int column);
		void Render(float pos_x = 0.0f, float pos_y = 0.0f);
		void Update();
		bool isRunning();
		bool isFinish();

		PointIndex effect_point_begin;
		PinePoint effect_point_begin_pixel;
		PinePoint effect_point_draw_pixel;
		int effect_is_touch_state;
		int effect_state_block;
		int effect_type;
		COLOR effect_color;

		float effect_radius;
		float effect_speed;
		float effect_radius_target;

		float percent;
		float speed;
	};
	EffectZoomObjectScaleIn _effect_zoom_object_scale_in;


	struct EffectZoomObjectReborn
	{
		int state;
		void Default();
		void Init(int row, int column, int type);
		void Render(float pos_x = 0.0f, float pos_y = 0.0f);
		void Update();
		bool isRunning();
		bool isFinish();

		PointIndex effect_point_begin;
		PinePoint effect_point_begin_pixel;
		PinePoint effect_point_draw_pixel;
		int effect_is_touch_state;
		int effect_state_block;
		int effect_type;
		COLOR effect_color;

		float effect_radius;
		float effect_speed;
		float effect_radius_target;

		float getPercent();
	};
	EffectZoomObjectReborn _effect_zoom_object_reborn;
private:

};
#endif
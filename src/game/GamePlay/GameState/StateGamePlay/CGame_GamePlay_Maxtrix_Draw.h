#ifndef __GAMEPLAY_MATRIX_DRAW__
#define __GAMEPLAY_MATRIX_DRAW__

class MatrixDraw
{
public:
#define TILE_WIDTH				113
#define TILE_HEIGHT				113

#define GRAP_GRID				36

#define GRAP_TILE_WIDTH			24.0f
#define GRAP_TILE_HEIGHT		24.0f

#define MATRIX_CAN_TOUCH			1
#define MATRIX_CLEAR_TOUCH			2

#define MATRIX_LOOP_CHECK_FILL		3
#define MATRIX_REFILL				4
#define MATRIX_STUN				    5
#define MATRIX_SHUFFLE				6

	BlockGrid _arr_block_test[10][10];
	BlockGrid **_arr_block;
	BlockGrid **_private_arr_block_input;
	void ResetGrid();
	void InitGrid7x7();
	void InitMatrix();
	void InitMatrixForTutorial();
	void InitMatrixForTutorialClear();
	void UpdateMatrix();

	void UpdateCheckAllFinishEffectEplant();

	void UpdatePosMatrix();
	void RenderMatrix(float pos_x, float pos_y);
	void RenderBlockNormalCurrent(int index_r, int index_c, int opacity_input, float pos_x = 0.0f, float pos_y = 0.0f);
	bool UpdateTouchMatrix();
	int _index_touch_matrix;
	bool CheckTouchInBlock(int x, int y);
	int GetCurrentBlockChoose(int x, int y, PinePoint &pos_ret);
	int GetCurrentBlockWidth();
	int GetCurrentBlockHeight();
	void SetValueGrap();
	int _current_block_choose;
	int _state_matrix;
	COLOR GetCurrentColor(int type);
	int _matrix_max_row_current;
	int _matrix_max_column_current;

	int _matrix_block_width;
	int _matrix_block_height;

	struct GrapBlockInGame
	{
		float width;
		float height;
	};
	GrapBlockInGame _grap;

	struct EffectIdleZoom
	{
		float value_current;
		float value_target;
		float speed;
		int state;
		void Init(float current, float target);
		void Update();
		Acceleration accleration_function;
		int time_wait;
	};
	EffectIdleZoom _effect_idle_zoom;
	

	struct SumaryInfo
	{
		int state;
		int stt;
		float percent;
		bool is_finish;
	};
	WaveCircle _effect_wave_circle;
	int _x_combo_current;
	int _type_current_check;
	int GetTotalBlockLikeTypeAndState(int state, int type);
	void PlaySoundCombo(bool upgrade_sound);
	void IncreaseIndexComboSound();
	int _sound_combo_index_current;
	EffectTypeClearIdle _effect_type_clear_idle;

	float _opacity_grid;
	struct EffectFadeInFadeOutGrid
	{
		void Default();
		void Init(bool fade_in, float begin_value);
		void Update();
		int _state;
		bool isFinish();
		bool _fade_in;
		void SetOutValue(float &opacity_out);
		float _percent;
		float _speed;
		float _opacity_begin;
	};
	EffectFadeInFadeOutGrid _effect_fade_in_fade_out_grid;
	bool _is_big_boom_ready;
	int _time_counter_stun;
private:

};
#endif
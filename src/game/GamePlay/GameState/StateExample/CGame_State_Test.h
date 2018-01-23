#ifndef __COLORBORN_EXAMPLE__
#define __COLORBORM_EXAMPLE__

class StateTest
{
public:
	void UpdateStateTest();
	void RenderStateTest();
	bool UpdateControl();

	void InitStateTest();

	struct Block
	{
		PointIndex point_begin;
		PinePoint point_begin_pixel;
		PinePoint point_draw_pixel;
		void Render();
		void Update();
		void Init(int column, int row);
	};


	struct GrapBlockInGame
	{
		float width;
		float height;
	};
	struct Matrix
	{
		Block arr_draw[7][7];
		void Render();
		void Update();
		void Init();

		int max_row;
		int max_colum;
		int block_width;
		int block_height;
		GrapBlockInGame grap;
	};

	Matrix matrix_game;

	struct SumaryInfo
	{
		int state;
		int stt;
		float percent;
		bool is_finish;
	};

	WaveCircle _effect_wave_circle;
private:

};
#endif
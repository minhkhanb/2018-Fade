#ifndef __CGAME_WAVE_CIRCLE__
#define __CGAME_WAVE_CIRCLE__

class PointIndex
{
public:
	int row;
	int column;
private:

};

class BoomInfo
{
public:
	PointIndex _point_center_begin_wave;

	float _power;
	float _weak_percent;
	void Update();
	float getCurrentPower();
	bool isDie();
	void Init(int touch_r, int touch_c, float pow, float wek);
private:

};

class WaveCircle
{
public:
	SVector2 _vectorBegin;
	SVector2 _vectorTest;
	void Default(int row, int column);
	void Update();
	void AddVectorPush(SVector2 v, PointIndex point);
	void SubmitVectorPush();
	

	PinePoint **_matrix_pos_begin;
	PinePoint **_matrix_pos_current;
	SVector2 **_matrix_vector;
	struct VectorPush
	{
		SVector2 vector_push;
		PointIndex point_effect;
	};
#if defined (OPTIMIZE_ANDROID)
	VectorPush _matrix_vector_push[50];
#else 
	VectorPush *_matrix_vector_push;
#endif
	int _num_vector_push;

	int _current_row;
	int _current_column;
	int _state;



	float _speed;

	bool _flag_add_vector;
	int _time_delay_change;


	/*Test push luc*/
	int _num_boom_current;
#if defined (OPTIMIZE_ANDROID)
	BoomInfo _matrix_boom_current[50];
#else
	BoomInfo *_matrix_boom_current;
#endif
	void BoomDefault();
	void AddBoom(int touch_r, int touch_c, float pow, float wek);
	void UpdateBoom();
	void UpdateAffectBoomInMatrixVector(int index);
	void DelBoom(int index);
private:

};

#endif
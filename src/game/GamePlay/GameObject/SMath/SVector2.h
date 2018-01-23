#if !_SVECTOR2_H
#define _SVECTOR2_H 1
class SVector2
{
private:


public:

	float x;
	float y;

	SVector2();
	~SVector2();
	float X();
	float Y();
	void Init(float x, float y);
	void Normalized();
	/*SVector2 & operator=(const SVector2 &);
	SVector2 & operator+(const SVector2 &);
	SVector2 & operator+=(const SVector2 &);
	SVector2 & operator-(const SVector2 &);
	SVector2 & operator*(const float);
	SVector2 & operator*(const SVector2 &);*/

	SVector2 operator=(const SVector2);
	SVector2 operator+(const SVector2);
	SVector2 operator+=(const SVector2);
	SVector2 operator-(const SVector2);
	SVector2 operator*(const float);
	SVector2 operator/(const float);
	SVector2 operator*(const SVector2);
	bool operator==(const SVector2);
	bool operator!=(const SVector2);

	static SVector2 CreateVector(float x, float y);
	static float Magnitude(SVector2 v);
	static float Dot(SVector2 start, SVector2 end);
	static SVector2 Lerp(SVector2 start, SVector2 end, float percent);
	static SVector2 SLerp(SVector2 start, SVector2 end, float percent);
};
#endif
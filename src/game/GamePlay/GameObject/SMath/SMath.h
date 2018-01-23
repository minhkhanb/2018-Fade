#if !_SMATH_H
#define _SMATH_H 1

class SRect
{
public:
	SRect();
	~SRect();
	float x;
	float y;
	float w;
	float h;

	void Init(float xx, float yy, float ww, float hh)
	{
		x = xx;
		y = yy;
		w = ww;
		h = hh;
	}

	bool IsNull()
	{
		return (w <= 0 || h <= 0);
	}

	void Render()
	{
		//G()->SetColor(0xffff0000);
		//G()->FillRect(x, y, w, h, true);
	}
};

class SMath
{
public:
	static float Max(float a, float b);
	static float Min(float a, float b);
	static void Normalize(float &x, float &y);
	static float Absolute(float x);
	static float Clamp(float x, float min, float max);
	static float Signum(float f);
	static double Fabs(double d);

	static SVector2 CrossProduct(SVector2 a, SVector2 b);
	static int DotProduct(SVector2 a, SVector2 b);
	static bool SameSide(SVector2 p1, SVector2 p2, SVector2 a, SVector2 b);

	static float Sign(SVector2 p1, SVector2 p2, SVector2 p3);
	static bool PointInTriangle(SVector2 pt, SVector2 v1, SVector2 v2, SVector2 v3);

	static bool CircleHitCircle(float cx1, float cy1, float r1, float cx2, float cy2, float r2);
	//static bool PointInRect(float px, float py, float x, float y, float w, float h);
	static bool PointInRect(float px, float py, float pr, float x, float y, float w, float h);
	static bool PointInRect(float px, float py, float x, float y, float w, float h);

	static bool RectHitRect(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2);
	static bool RectHitRect(SRect rect1, SRect rect2);
	static SRect RectInRect(SRect rect1, SRect rect2);
};

#endif
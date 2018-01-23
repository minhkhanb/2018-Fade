#include "pch.h"
#include "../../../GameCore/CGame.h"
#include "SMath.h"

SRect::SRect()
{
	x = 0;
	y = 0;
	w = 0;
	h = 0;
}

SRect::~SRect()
{

}

float SMath::Max(float a, float b)
{
	return (a>b ? a : b);
}

float SMath::Min(float a, float b)
{
	return (a>b ? b : a);
}

void SMath::Normalize(float &x, float &y)
{
	float lenght = CMath::SQRT(x*x + y*y);
	x = x / lenght;
	y = y / lenght;
}

float SMath::Absolute(float x)
{
	if (x >= 0)
	{
		return x;
	}
	else 
	{
		return -x;
	}
}

double SMath::Fabs(double d)
{
	if (d >= 0)
	{
		return d;
	}
	else
	{
		return -d;
	}
}

float SMath::Clamp(float x, float min, float max)
{
	if (x < min)
	{
		x = min;
	}
	else if (x > max)
	{
		x = max;
	}

	return x;
}

float SMath::Signum(float f)
{
	float result = 0;
	if (f == 0)
	{
		result = 0.0f;
	}
	else if (f > 0)
	{
		result = 1.0f;
	}
	else if (f < 0)
	{
		result = -1.0f;
	}
	return result;
}

int SMath::DotProduct(SVector2 a, SVector2 b)
{
	return (a.x * b.x + a.y * b.y);
}

float SMath::Sign(SVector2 p1, SVector2 p2, SVector2 p3)
{
	return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool SMath::PointInTriangle(SVector2 pt, SVector2 v1, SVector2 v2, SVector2 v3)
{
	bool b1, b2, b3;

#if SHOW_TRIANGLE_COLLISION
	G()->SetColor(0xffffff00);
	G()->FillRect(pt.x, pt.y, 5, 5, true);

	G()->SetColor(0xffff0000);
	G()->FillTriangle(v1.x, v1.y, v2.x, v2.y, v3.x, v3.y);
#endif

	float sign1 = Sign(pt, v1, v2);
	float sign2 = Sign(pt, v2, v3);
	float sign3 = Sign(pt, v3, v1);

	b1 = Sign(pt, v1, v2) < 0.0f;
	b2 = Sign(pt, v2, v3) < 0.0f;
	b3 = Sign(pt, v3, v1) < 0.0f;

	if ((b1 == b2) && (b2 == b3))
	{
		printf("\n Hit");
	}

	return ((b1 == b2) && (b2 == b3));
}

bool SMath::CircleHitCircle(float cx1, float cy1, float r1, float cx2, float cy2, float r2)
{
	bool hit = false;
	float distance1 = CMath::DISTANCE(cx1, cy1, cx2, cy2);
	float distance2 = r1 + r2;

	return distance1 <= distance2;
}

bool SMath::RectHitRect(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2)
{
	if (x1 < x2 + w2 && x1 + w1 > x2 &&
		y1 < y2 + h2 && y1 + h1 > y2)
	{
		return true;
	}

	/*G()->SetColor(0xffffff00);
	G()->FillRect(x1, y1, w1, h1, true);

	G()->SetColor(0xffffff00);
	G()->FillRect(x2, y2, w2, h2, true);*/

	return false;
};

bool SMath::RectHitRect(SRect rect1, SRect rect2)
{
	if (rect1.x < rect2.x + rect2.w && rect1.x + rect1.w > rect2.x &&
		rect1.y < rect2.y + rect2.h && rect1.y + rect1.h > rect2.y)
	{
		return true;
	}

	/*G()->SetColor(0xffffff00);
	G()->FillRect(x1, y1, w1, h1, true);

	G()->SetColor(0xffffff00);
	G()->FillRect(x2, y2, w2, h2, true);*/

	return false;
};

SRect SMath::RectInRect(SRect rect1, SRect rect2)
{

	SRect result;

	// find intersection:
	float xL = Max(rect1.x, rect2.x);
	float xR = Min(rect1.x + rect1.w, rect2.x + rect2.w);
	if (xR <= xL)
	{
		result.Init(0, 0, -1, -1);
		return result;
	}
	else
	{
		int yT = Max(rect1.y, rect2.y);
		int yB = Min(rect1.y + rect1.h, rect2.y + rect2.h);
		if (yB <= yT)
		{
			result.Init(0, 0, -1, -1);
			return result;
		}
		else
		{
			result.Init(xL, yT, xR - xL, yB - yT);
			return result;
		}
	}
}

bool SMath::PointInRect(float px, float py, float pr, float x, float y, float w, float h)
{
	float nx = x - pr;
	float ny = y - pr;
	float nw = w + pr*2;
	float nh = h + pr*2;

#if SHOW_RECT_COLLISION
	G()->SetColor(0xffffff00);
	G()->FillRect(px, py, 5, 5, true);

	G()->SetColor(0xffff0000);
	G()->FillRect(nx, ny, nw, nh, true);
#endif

	return CHECK_POINT_IN_RECT(px, py, nx, ny, nw, nh);
}

bool SMath::PointInRect(float px, float py, float x, float y, float w, float h)
{
#if SHOW_RECT_COLLISION
	G()->SetColor(0xffffff00);
	G()->FillRect(px, py, 5, 5, true);

	G()->SetColor(0xffff0000);
	G()->FillRect(nx, ny, nw, nh, true);
#endif

	return CHECK_POINT_IN_RECT(px, py, x, y, w, h);
}

/*bool SMath::PointInRect(float px, float py, float x, float y, float w, float h)
{
	return CHECK_POINT_IN_RECT(px, py, x, y, w, h);
}*/

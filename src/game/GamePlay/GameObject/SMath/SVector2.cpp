#include "pch.h"
#include "../../../GameCore/CGame.h"
#include "SVector2.h"

SVector2::SVector2()
{
	x = 0;
	y = 0;
}

SVector2::~SVector2()
{

}

void SVector2::Init(float xx, float yy)
{
	x = xx;
	y = yy;
}

float SVector2::X()
{
	return x;
}

float SVector2::Y()
{
	return y;
}

void SVector2::Normalized()
{
	float a = CMath::SQRT(x*x + y*y);
	if (a == 0)
	{
		x = 0;
		y = 0;
	}
	else
	{
		x = x / SMath::Absolute(a);
		y = y / SMath::Absolute(a);
	}
}

/*
SVector2 & SVector2::operator=(const SVector2& v)
{
	x = v.x;
	y = v.y;
	return *this;
}

SVector2 & SVector2::operator+(const SVector2& v)
{
	x + v.x;
	y + v.y;
	return *this;
}

SVector2 & SVector2::operator+=(const SVector2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

SVector2 & SVector2::operator-(const SVector2& v)
{
	x - v.x;
	y - v.y;
	return *this;
}

SVector2 & SVector2::operator*(const float f)
{
	x * f;
	y * f;
	return *this;
}

SVector2 SVector2::operator*(const SVector2& v)
{
	SVector2 result;
	result.x = x * v.x;
	result.y = y * v.y;
	return result;
}
*/

SVector2 SVector2::operator=(const SVector2 v)
{
	SVector2 result;
	x = v.x;
	y = v.y;
	return result;
}

SVector2 SVector2::operator+(const SVector2 v)
{
	SVector2 result;
	result.x = x + v.x;
	result.y = y + v.y;
	return result;
}

SVector2 SVector2::operator+=(const SVector2 v)
{
	SVector2 result;
	x += v.x;
	y += v.y;
	result.x = x;
	result.y = y;
	return result;
}

SVector2 SVector2::operator-(const SVector2 v)
{
	SVector2 result;
	result.x = x - v.x;
	result.y = y - v.y;
	return result;
}

SVector2 SVector2::operator*(const float f)
{
	SVector2 result;
	result.x = x * f;
	result.y = y * f;
	return result;
}

SVector2 SVector2::operator/(const float f)
{
	SVector2 result;
	result.x = x / f;
	result.y = y / f;
	return result;
}

SVector2 SVector2::operator*(const SVector2 v)
{
	SVector2 result;
	result.x = x * v.x;
	result.y = y * v.y;
	return result;
}

bool SVector2::operator==(const SVector2 v)
{
	return (x == v.x && y == v.y);
}

bool SVector2::operator!=(const SVector2 v)
{
	return !(x == v.x && y == v.y);
}

SVector2 SVector2::CreateVector(float x, float y)
{
	SVector2 pos;
	pos.Init(x, y);
	return pos;
}

float SVector2::Dot(SVector2 start, SVector2 end)
{
	return start.x * end.x + start.y * end.y;
}

float SVector2::Magnitude(SVector2 v)
{
	return CMath::SQRT(v.x*v.x + v.y*v.y);
}

SVector2 SVector2::Lerp(SVector2 start, SVector2 end, float percent)
{
	return (start + (end - start)*percent);
}

SVector2 SVector2::SLerp(SVector2 start, SVector2 end, float percent)
{
	// Dot product - the cosine of the angle between 2 vectors.
	float dot = SVector2::Dot(start, end);
	// Clamp it to be in the range of Acos()
	// This may be unnecessary, but floating point
	// precision can be a fickle mistress.
	//Mathf.Clamp(dot, -1.0f, 1.0f);
	dot = SMath::Clamp(dot, -1.0f, 1.0f);
	// Acos(dot) returns the angle between start and end,
	// And multiplying that by percent returns the angle between
	// start and the final result.
	//float theta = Mathf.Acos(dot)*percent;
	float theta = CMath::ARCCOS(dot)*percent;
	SVector2 RelativeVec = end - start*dot;
	RelativeVec.Normalized();     // Orthonormal basis
	// The final result.
	//return ((start*Mathf.Cos(theta)) + (RelativeVec*Mathf.Sin(theta)));
	return ((start*CMath::COS(theta)) + (RelativeVec*CMath::SIN(theta)));
}




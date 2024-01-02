#pragma once
#include <math.h>
#define PI 3.141592

#define GROUNDCOLOR						RGB(0, 0, 0)
#define WALLCOLOR						RGB(0, 12, 123)
#define FLYLCOLOR						RGB(51, 102, 102)

#define STONEGREY_LOOPENTER				RGB(127, 127, 127) 
#define STONEORANGE_LOOPHALF			RGB(255, 127, 0)
#define STONERED_LOOPENTER				RGB(255, 0, 0)

#define GROUNDYELLO_LOOPCOURSE_RIGHT	RGB(255, 255, 0)
#define GROUNDBLUE_LOOPCOURSE_LEFT		RGB(0, 0, 255)


struct Vector2
{
	static Vector2 Up;
	static Vector2 Right;

	static Vector2 One;
	static Vector2 Zero;

	float x;
	float y;

	Vector2()
		: x(0.0f)
		, y(0.0f)
	{
	}

	Vector2(float x, float y)
		: x(x)
		, y(y)
	{
	}

	Vector2(int x, int y)
		: x(static_cast<float>(x))
		, y(static_cast<float>(y))
	{
	}



	Vector2 operator-()
	{
		return Vector2(-x, -y);
	}




	Vector2 operator+(const Vector2& other)
	{
		Vector2 temp;
		temp.x = x + other.x;
		temp.y = y + other.y;

		return temp;
	}

	Vector2 operator-(const Vector2& other)
	{
		Vector2 temp;
		temp.x = x - other.x;
		temp.y = y - other.y;

		return temp;
	}



	Vector2 operator*(const Vector2& other)
	{
		Vector2 temp;
		temp.x = x * other.x;
		temp.y = y * other.y;

		return temp;
	}

	
	Vector2 operator*(const float ratio)
	{
		Vector2 temp;
		temp.x = x * ratio;
		temp.y = y * ratio;

		return temp;
	}


	Vector2 operator/(const float ratio)
	{
		Vector2 temp;
		temp.x = x / ratio;
		temp.y = y / ratio;

		return temp;
	}



	void operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;
	}

	void operator-=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
	}


	void operator*=(const Vector2& other)
	{
		x *= other.x;
		y *= other.y;
	}

	void operator*=(const float& value)
	{
		x *= value;
		y *= value;
	}


	bool operator==(const Vector2& other)
	{
		return (x == other.x && y == other.y);
	}

	void operator-=(const float& value)
	{
		x -= value;
		y -= value;
	}

	void operator+=(const float& value)
	{
		x += value;
		y += value;
	}


	Vector2(const Vector2& other)
		: x(other.x)
		, y(other.y)
	{
	}

	void Clear()
	{
		x = 0.0f;
		y = 0.0f;
	}

	float Length()
	{
		return sqrtf(x * x + y * y);
	}

	Vector2& Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;

		return *this;
	}



	static Vector2 RSonicWalkLTC;
	static Vector2 RSonicWalksize;
	static Vector2 RSonicWalkSpace;
	static Vector2 LSonicWalkLTC;
	static Vector2 LSonicWalksize;
	static Vector2 LSonicWalkSpace;

	static Vector2 RSonicStandLTC;
	static Vector2 RSonicStandsize;
	static Vector2 RSonicStandSpace;
	static Vector2 LSonicStandLTC;
	static Vector2 LSonicStandsize;
	static Vector2 LSonicStandSpace;

	static Vector2 RSonicSitLTC;
	static Vector2 RSonicSitsize;
	static Vector2 RSonicSitSpace;
	static Vector2 LSonicSitLTC;
	static Vector2 LSonicSitsize;
	static Vector2 LSonicSitSpace;

	static Vector2 RSonicLookUpLTC;
	static Vector2 RSonicLookUpsize;
	static Vector2 RSonicLookUpSpace;
	static Vector2 LSonicLookUpLTC;
	static Vector2 LSonicLookUpsize;
	static Vector2 LSonicLookUpSpace;

	static Vector2 RTailsWalkLTC;
	static Vector2 RTailsWalksize;
	static Vector2 RTailsWalkSpace;
	static Vector2 LTailsWalkLTC;
	static Vector2 LTailsWalksize;
	static Vector2 LTailsWalkSpace;

	static Vector2 RTailsStandLTC;
	static Vector2 RTailsStandsize;
	static Vector2 RTailsStandSpace;
	static Vector2 LTailsStandLTC;
	static Vector2 LTailsStandsize;
	static Vector2 LTailsStandSpace;

	static Vector2 RTailsSitLTC;
	static Vector2 RTailsSitsize;
	static Vector2 RTailsSitSpace;
	static Vector2 LTailsSitLTC;
	static Vector2 LTailsSitsize;
	static Vector2 LTailsSitSpace;

	static Vector2 RTailsLookUpLTC;
	static Vector2 RTailsLookUpsize;
	static Vector2 RTailsLookUpSpace;
	static Vector2 LTailsLookUpLTC;
	static Vector2 LTailsLookUpsize;
	static Vector2 LTailsLookUpSpace;

	static Vector2 RmonsterLTC;
	static Vector2 Rmonstersize;
	static Vector2 RmonsterSpace;
	static Vector2 LmonsterLTC;
	static Vector2 Lmonstersize;
	static Vector2 LmonsterSpace;

	static Vector2 Rmonster1LTC;
	static Vector2 Lmonster1LTC;

	static Vector2 rRobotAtackLTC;
	static Vector2 rRobotAtacksize;
	static Vector2 rRobotAtackSpace;
	static Vector2 lRobotAtackLTC;
	static Vector2 lRobotAtacksize;
	static Vector2 lRobotAtackSpace;
};



namespace jk::math
{
	//float x = mDir.x * cosf(PI / 5.0f) - mDir.y * sinf(PI / 5.0f);
	//float y = mDir.x * sinf(PI / 5.0f) + mDir.y * cosf(PI / 5.0f);

	inline static Vector2 Rotate(Vector2 vector, float degree)
	{
		float radian = (float)((degree / 180.0f) * PI);
		//vector.Normalize();

		float x = vector.x * cosf(radian) - vector.y * sinf(radian);
		float y = vector.x * sinf(radian) + vector.y * cosf(radian);
		//atan
		//atan();
		return Vector2(x, y);
	}


	inline static float Dot(Vector2& v1, Vector2& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	inline static float Cross(Vector2& v1, Vector2& v2)
	{
		return v1.x * v2.y - v1.y * v2.x;
	}

}






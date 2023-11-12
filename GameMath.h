#pragma once

struct Vector2
{
	union {
		float X;
		float W;
	};
	union {
		float Y;
		float H;
	};

	Vector2(float x, float y)
	{
		X = x;
		Y = y;
	}
};

struct Vector3
{
	float X;
	float Y;
	float Z;
	Vector3(float x, float y, float z)
	{
		X = x;
		Y = y;
		Z = z;
	}
};
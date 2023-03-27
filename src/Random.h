#pragma once
#include <random>
#include "Math.h"

class Random
{
public:
	static void Init();
	static float GenerateFloat(float start = 0.0f, float end = 1.0f);
	static int GenerateInt(int start, int end);
	static Vector2 GenerateVector2(const Vector2& a, const Vector2& b);
	static Vector3 GenerateVector3(const Vector3& a, const Vector3& b);
private:
	static std::default_random_engine mEngine;
};
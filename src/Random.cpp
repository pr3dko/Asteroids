#include "Random.h"

std::default_random_engine Random::mEngine;

void Random::Init()
{
	std::random_device rd;
	mEngine.seed(rd());
}

float Random::GenerateFloat(float start, float end)
{
	std::uniform_real_distribution<float> u(start, end);
	return u(mEngine);
}

int Random::GenerateInt(int start, int end)
{
	std::uniform_int_distribution<int> u(start, end);
	return u(mEngine);
}

Vector2 Random::GenerateVector2(const Vector2& a, const Vector2& b)
{
	std::uniform_real_distribution<float> uX(a.x, b.x);
	std::uniform_real_distribution<float> uY(a.y, b.y);
	return Vector2(uX(mEngine), uY(mEngine));
}

Vector3 Random::GenerateVector3(const Vector3& a, const Vector3& b)
{
	std::uniform_real_distribution<float> uX(a.x, b.x);
	std::uniform_real_distribution<float> uY(a.y, b.y);
	return Vector3(uX(mEngine), uY(mEngine));
}
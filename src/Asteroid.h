#pragma once
#include "Actor.h"
#include "CircleComponent.h"

class Asteroid : public Actor
{
public:
	Asteroid(class Game* game);
	~Asteroid();

	void SplitInTwo();

	class CircleComponent* GetCircle() { return mCircle; }

private:
	class CircleComponent* mCircle;
};
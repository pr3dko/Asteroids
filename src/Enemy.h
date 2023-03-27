#pragma once
#include "Actor.h"

class Enemy : public Actor
{
public:
	Enemy(class Game* game);
	void UpdateActor(float deltaTime) override;
	~Enemy();

	void SetLaserRotation(float rotation) { mLaserRotation = rotation; }

	class CircleComponent* GetCircle() { return mCircle; }

private:
	class CircleComponent* mCircle;
	float mLaserCooldown;
	float mLaserRotation;
};
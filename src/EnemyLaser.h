#pragma once
#include "Actor.h"

class EnemyLaser : public Actor
{
public:
	EnemyLaser(class Game* game);

	void UpdateActor(float deltaTime) override;

private:
	class CircleComponent* mCircle;
	float mDeathTimer;
};
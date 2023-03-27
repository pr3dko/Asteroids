#pragma once
#include "Actor.h"

class Explosion : public Actor
{
public:
	Explosion(class Game* game);

	void UpdateActor(float deltaTime) override;

private:
	class AnimSpriteComponent* mAnim;
	float mDeathTimer;
};
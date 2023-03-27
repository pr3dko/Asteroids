#pragma once
#include "Actor.h"

class Ship : public Actor
{
public:
	Ship(class Game* game);
	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* state) override;
	class CircleComponent* GetCircle() const { return mCircle; }
	void Reset();

private:
	float mLaserCooldown;
	float mResetTimer;
	class CircleComponent* mCircle;
	//class InputComponent* mInput;
	class PhysicsInputComponent* mInput;
	class AnimSpriteComponent* mAnim;
};
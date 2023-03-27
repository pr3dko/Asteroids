#pragma once
#include "Component.h"
#include "Math.h"

class PhysicsMoveComponent : public Component
{
public:
	PhysicsMoveComponent(class Actor* owner, int updateOrder = 10);
	void Update(float deltaTime) override;

	float GetAngularSpeed() const { return mAngularSpeed; }
	const Vector2& GetVelocity() const { return mVelocity; }
	const Vector2& GetAcceleration() const { return mAcceleration; }

	void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
	void SetAcceleration(Vector2 acceleration) { mAcceleration = acceleration; }
	void SetMaxSpeed(float speed) { mMaxSpeed = speed; }
	void SetVelocity(Vector2 velocity) { mVelocity = velocity; }

private:
	float mAngularSpeed;
	float mMaxSpeed;
	Vector2 mAcceleration;
	Vector2 mVelocity;
};
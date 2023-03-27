#pragma once
#include "PhysicsMoveComponent.h"
#include <cstdint>

class PhysicsInputComponent : public PhysicsMoveComponent
{
public:
	PhysicsInputComponent(class Actor* owner);
	void ProcessInput(const uint8_t* state) override;

	float GetMaxAcceleration() const { return mMaxAcceleration; }
	float GetMaxAngularSpeed() const { return mMaxAngularSpeed; }
	int GetForwardKey() const { return mForwardKey; }
	int GetBackwardKey() const { return mBackwardKey; }
	int GetClockwiseKey() const { return mClockwiseKey; }
	int GetAntiClockwiseKey() const { return mAntiClockwiseKey; }

	void SetMaxAcceleration(float acceleration) { mMaxAcceleration = acceleration; }
	void SetMaxAngularSpeed(float speed) { mMaxAngularSpeed = speed; }
	void SetForwardKey(int key) { mForwardKey = key; }
	void SetBackwardKey(int key) { mBackwardKey = key; }
	void SetClockwiseKey(int key) { mClockwiseKey = key; }
	void SetAntiClockwiseKey(int key) { mAntiClockwiseKey = key; }
	void SetEnabled(bool enabled) { mEnabled = enabled; }

private:
	float mMaxAcceleration;
	float mMaxAngularSpeed;

	int mForwardKey;
	int mBackwardKey;
	int mClockwiseKey;
	int mAntiClockwiseKey;

	bool mEnabled;
};
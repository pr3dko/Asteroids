#include "PhysicsInputComponent.h"
#include "Actor.h"

PhysicsInputComponent::PhysicsInputComponent(Actor* owner) : PhysicsMoveComponent(owner), mMaxAcceleration(0.0f), mMaxAngularSpeed(0.0f), mForwardKey(0), mBackwardKey(0), mClockwiseKey(0), mAntiClockwiseKey(0),
mEnabled(true)
{

}

void PhysicsInputComponent::ProcessInput(const uint8_t* state)
{
	if (mEnabled)
	{
		if (state[mForwardKey]) { SetAcceleration(mMaxAcceleration * mOwner->GetForward()); }
		else { SetAcceleration(Vector2(0.0f, 0.0f)); }

		float angularSpeed = 0.0f;
		if (state[mClockwiseKey]) { angularSpeed -= mMaxAngularSpeed; }
		if (state[mAntiClockwiseKey]) { angularSpeed += mMaxAngularSpeed; }
		SetAngularSpeed(angularSpeed);
	}
}
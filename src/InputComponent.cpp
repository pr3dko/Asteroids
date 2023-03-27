#include "InputComponent.h"
#include "Actor.h"

InputComponent::InputComponent(Actor* owner) : MoveComponent(owner), mMaxForwardSpeed(0.0f), mMaxAngularSpeed(0.0f), mForwardKey(0), mBackwardKey(0), mClockwiseKey(0), mAntiClockwiseKey(0)
{

}

void InputComponent::ProcessInput(const uint8_t* state)
{
	float forwardSpeed = 0.0f;
	if (state[mForwardKey]) { forwardSpeed += mMaxForwardSpeed; }
	if (state[mBackwardKey]) { forwardSpeed -= mMaxForwardSpeed; }
	SetForwardSpeed(forwardSpeed);

	float angularSpeed = 0.0f;
	if (state[mClockwiseKey]) { angularSpeed -= mMaxAngularSpeed; }
	if (state[mAntiClockwiseKey]) { angularSpeed += mMaxAngularSpeed; }
	SetAngularSpeed(angularSpeed);
}
#include "PhysicsMoveComponent.h"
#include "Actor.h"
#include <iostream>

PhysicsMoveComponent::PhysicsMoveComponent(Actor* owner, int updateOrder) : Component(owner, updateOrder), mAngularSpeed(0.0f), mAcceleration(0.0f), mVelocity()
{

}

void PhysicsMoveComponent::Update(float deltaTime)
{
	if (!Math::NearZero(mAngularSpeed))
	{
		float rot = mOwner->GetRotation();
		rot += mAngularSpeed * deltaTime;
		mOwner->SetRotation(rot);
	}

	if (!Math::NearZero(mAcceleration.Length()))
	{
		mVelocity += mAcceleration * deltaTime;
		if (mVelocity.Length() > mMaxSpeed)
		{
			mVelocity.Normalize();
			mVelocity *= mMaxSpeed;
		}
	}
	else
	{
		// Decay the velocity over time 
		mVelocity *= 0.95f;
	}

	if (!Math::NearZero(mVelocity.Length()))
	{
		Vector2 pos = mOwner->GetPosition();
		pos += mVelocity * deltaTime;
		// Screen wrapping
		if (pos.x < 0.0f) { pos.x = 1022.0f; }
		else if (pos.x > 1024.0f) { pos.x = 2.0f; }
		if (pos.y < 0.0f) { pos.y = 766.0f; }
		else if (pos.y > 768.0f) { pos.y = 2.0f; }

		mOwner->SetPosition(pos);
	}

}
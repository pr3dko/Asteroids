#include "CircleComponent.h"
#include "Actor.h"

CircleComponent::CircleComponent(Actor* owner) : Component(owner), mRadius(0.0f)
{

}

float CircleComponent::GetRadius() const
{
	return mOwner->GetScale() * mRadius;
}

const Vector2& CircleComponent::GetCentre() const
{
	return mOwner->GetPosition();
}

bool Intersect(const CircleComponent& a, const CircleComponent &b)
{
	Vector2 diff = a.GetCentre() - b.GetCentre();
	float sumOfRadiiSquared = (a.GetRadius() + b.GetRadius()) * (a.GetRadius() + b.GetRadius());
	return diff.LengthSquared() <= sumOfRadiiSquared;
}
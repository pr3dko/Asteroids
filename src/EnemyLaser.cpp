#include "EnemyLaser.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CircleComponent.h"
#include "Asteroid.h"
#include "Explosion.h"
#include "Ship.h"
#include "Enemy.h"

EnemyLaser::EnemyLaser(Game* game) : Actor(game), mDeathTimer(2.0f)
{
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/laser.png"));

	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(600.0f);
	mc->SetScreenWrap(false);

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(11.0f);
}

void EnemyLaser::UpdateActor(float deltaTime)
{
	mDeathTimer -= deltaTime;
	if (mDeathTimer <= 0.0f)
	{
		SetState(EDead);
	}
	else
	{
		if (Intersect(*mCircle, *(GetGame()->GetShip()->GetCircle())))
		{
			Explosion* explosion = new Explosion(GetGame());
			explosion->SetPosition(GetPosition());
			GetGame()->GetSounds()->PlayChunk(SoundManager::Explosion);
			SetState(EDead);
			GetGame()->Reset();
		}
	}
}
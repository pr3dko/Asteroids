#include "Laser.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CircleComponent.h"
#include "Asteroid.h"
#include "Explosion.h"
#include "Enemy.h"

Laser::Laser(Game* game) : Actor(game), mDeathTimer(2.0f)
{
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/laser.png"));

	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(600.0f);
	mc->SetScreenWrap(false);

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(11.0f);
}

void Laser::UpdateActor(float deltaTime)
{
	mDeathTimer -= deltaTime;
	if (mDeathTimer <= 0.0f)
	{
		SetState(EDead);
	}
	else
	{
		for (auto ast : GetGame()->GetAsteroids())
		{
			if (Intersect(*mCircle, *(ast->GetCircle())))
			{
				Explosion* explosion = new Explosion(GetGame());
				explosion->SetPosition(GetPosition());
				GetGame()->GetSounds()->PlayChunk(SoundManager::Explosion);
				SetState(EDead);

				if (ast->GetScale() > 1.0f)
				{
					ast->SplitInTwo();
				}
				else
				{
					ast->SetState(EDead);
				}
				break;
			}
		}

		if (GetGame()->IsEnemyPresent() && Intersect(*mCircle, *(GetGame()->GetEnemy()->GetCircle())))
		{
			Explosion* explosion = new Explosion(GetGame());
			explosion->SetPosition(GetPosition());
			GetGame()->GetSounds()->PlayChunk(SoundManager::Explosion);
			SetState(EDead);
			GetGame()->GetEnemy()->SetState(EDead);
			GetGame()->SetEnemyPresent(false);
		}
	}
}
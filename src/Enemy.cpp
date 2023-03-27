#include "Enemy.h"
#include "Game.h"
#include "Random.h"
#include "CircleComponent.h"
#include "MoveComponent.h"
#include "AnimSpriteComponent.h"
#include "EnemyLaser.h"
#include "Ship.h"
#include "Explosion.h"

Enemy::Enemy(Game* game) : Actor(game), mLaserCooldown(1.5f), mLaserRotation(0.0f)
{
	game->SetEnemyPresent(true);
	// Initialize position along one of the borders
	Vector2 randPos;
	enum Border { Left = 0, Right, Top, Bottom };
	Border border = static_cast<Border>(Random::GenerateInt(0, 3));
	switch (border)
	{
		case Left:
		{
			randPos.x = 0.0f;
			randPos.y = Random::GenerateFloat(0, 768.0f);
			break;
		}
		case Right:
		{
			randPos.x = 1024.0f;
			randPos.y = Random::GenerateFloat(0, 768.0f);
			break;
		}
		case Top:
		{
			randPos.x = Random::GenerateFloat(0, 1024.0f);
			randPos.y = 0.0f;
			break;
		}
		case Bottom:
		{
			randPos.x = Random::GenerateFloat(0, 1024.0f);
			randPos.y = 768.0f;
			break;
		}
	}
	SetPosition(randPos);

	// Initialise orientation and scale
	SetRotation(Random::GenerateFloat(0.0f, 2 * Math::Pi));
	SetScale(2.0f);

	// Create components
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(16.0f);

	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(200.0f);

	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> textures = {
		game->GetTexture("Assets/enemy.png"),
		game->GetTexture("Assets/enemy2.png")
	};
	asc->SetAnimTextures(textures);
	asc->AddAnim("Default", 0, 1);
	asc->SetAnim("Default");
	asc->SetAnimFPS(6.0f);
}

void Enemy::UpdateActor(float deltaTime)
{
	mLaserCooldown -= deltaTime;
	if (mLaserCooldown <= 0.0f)
	{
		EnemyLaser* laser = new EnemyLaser(GetGame());
		laser->SetPosition(GetPosition());
		laser->SetRotation(mLaserRotation);
		mLaserCooldown = 1.5f;
		GetGame()->GetSounds()->PlayChunk(SoundManager::EnemyShoot);
	}
	if (Intersect(*mCircle, *(GetGame()->GetShip()->GetCircle())))
	{
		Explosion* explosion = new Explosion(GetGame());
		explosion->SetPosition(GetPosition());
		GetGame()->GetSounds()->PlayChunk(SoundManager::Explosion);
		GetGame()->Reset();
	}
}

Enemy::~Enemy()
{
	GetGame()->SetEnemyPresent(false);
}
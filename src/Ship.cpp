#include "Ship.h"
#include "Game.h"
#include "AnimSpriteComponent.h"
#include "InputComponent.h"
#include "PhysicsInputComponent.h"
#include "Laser.h"
#include "CircleComponent.h"
#include "Asteroid.h"
#include "Explosion.h"
#include "Enemy.h"

Ship::Ship(Game* game) : Actor(game), mLaserCooldown(0.0f)
{
	mAnim = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> textures = {
		game->GetTexture("Assets/ship-default.png"),
		game->GetTexture("Assets/ship.png"),
		game->GetTexture("Assets/ship2.png")
	};
	mAnim->SetAnimTextures(textures);
	mAnim->AddAnim("Default", 0, 0);
	mAnim->AddAnim("Thrust", 1, 2);
	mAnim->SetAnim("Default");
	mAnim->SetAnimFPS(6.0f);

	mInput = new PhysicsInputComponent(this);
	mInput->SetMaxSpeed(300.0f);
	mInput->SetMaxAngularSpeed(Math::Pi * 2.0f);
	mInput->SetMaxAcceleration(400.0f);
	mInput->SetForwardKey(SDL_SCANCODE_W);
	mInput->SetBackwardKey(SDL_SCANCODE_S);
	mInput->SetClockwiseKey(SDL_SCANCODE_D); 
	mInput->SetAntiClockwiseKey(SDL_SCANCODE_A);

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(12.0f);
}

void Ship::UpdateActor(float deltaTime)
{
	if (mResetTimer > 0.0f)
	{
		mResetTimer -= deltaTime;
		return;
	}

	mInput->SetEnabled(true);
	mLaserCooldown -= deltaTime;
	mAnim->SetAlphaMod(255);

	if (!Math::NearZero(mInput->GetAcceleration().Length()))
	{
		mAnim->SetAnim("Thrust");
	}
	else
	{
		mAnim->SetAnim("Default");
	}

	for (auto ast : GetGame()->GetAsteroids())
	{
		if (Intersect(*mCircle, *(ast->GetCircle())))
		{
			// If ship collides with asteroid, reset its position and rotation, and disable input until respawn
			Explosion* explosion = new Explosion(GetGame());
			explosion->SetPosition(GetPosition());
			GetGame()->GetSounds()->PlayChunk(SoundManager::Explosion);
			GetGame()->Reset();
			break;
		}
	}
}

void Ship::ActorInput(const uint8_t* state)
{
	if (state[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.0f && mResetTimer <= 0.0f)
	{
		Laser* laser = new Laser(GetGame());
		laser->SetPosition(GetPosition());
		laser->SetRotation(GetRotation());

		mLaserCooldown = 0.5f;
		GetGame()->GetSounds()->PlayChunk(SoundManager::Shoot);
	}
}

void Ship::Reset()
{
	mInput->SetEnabled(false);
	mInput->SetAcceleration(Vector2(0.0f, 0.0f));
	mInput->SetVelocity(Vector2(0.0f, 0.0f));
	mInput->SetAngularSpeed(0.0f);
	SetPosition(Vector2(512.0f, 384.0f));
	SetRotation(0.0f);
	mResetTimer = 2.0f;
	mAnim->SetAnim("Default");
	mAnim->SetAlphaMod(120);
}
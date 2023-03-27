#include "Asteroid.h"
#include "Game.h"
#include "Random.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CircleComponent.h"
#include <iostream>

Asteroid::Asteroid(Game* game) : Actor(game)
{
	// Initialize position along one of the borders
	Vector2 randPos;
	enum Border {Left = 0, Right, Top, Bottom};
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
	SetScale(Random::GenerateFloat(0.7f, 1.3f));

	// Create components
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/asteroid.png"));
	
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(150.0f);

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(20.0f);

	game->AddAsteroid(this);
}

Asteroid::~Asteroid()
{
	GetGame()->RemoveAsteroid(this);
}

void Asteroid::SplitInTwo()
{
	Asteroid* ast1 = new Asteroid(GetGame());
	Asteroid* ast2 = new Asteroid(GetGame());

	ast1->SetScale(1.0f);
	ast1->SetPosition(GetPosition());
	ast1->SetRotation(GetRotation() + Math::Pi / 4.0f);

	ast2->SetScale(1.0f);
	ast2->SetPosition(GetPosition());
	ast2->SetRotation(GetRotation() - Math::Pi / 4.0f);

	SetState(EDead);
}
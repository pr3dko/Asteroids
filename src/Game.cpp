#include "Game.h"
#include <algorithm>
#include "Actor.h"
#include <SDL_image.h>
#include "SpriteComponent.h"
#include "BGSpriteComponent.h"
#include "Asteroid.h"
#include "TileMapComponent.h"
#include "Ship.h"
#include "Random.h"
#include <iostream>
#include <SDL_mixer.h>
#include "Enemy.h"

Game::Game() : mWindow(nullptr), mRenderer(nullptr), mIsRunning(true), mUpdatingActors(false), mEnemyPresent(false), mSounds(std::make_shared<SoundManager>()), mNumAsteroids(5), mLevel(1)
{
}

bool Game::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Failed to initialise SDL. Error: %s\n", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("SDL Game", 100, 100, 1024, 768, 0);
	if (!mWindow)
	{
		SDL_Log("Failed to create window. Error: %s\n", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer. Error: %s\n", SDL_GetError());
		return false;
	}

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		SDL_Log("Failed to initialise SDL_image. Error: %s\n", IMG_GetError());
		return false;
	}

	if (!mSounds->Init())
	{
		return false;
	}

	Random::Init();

	LoadData();

	mTicksCount = SDL_GetTicks();

	return true;
}

void Game::Run()
{
	while (mIsRunning)
	{
		ProcessInput();
		Update();
		Render();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->ProcessInput(state);
	}
	mUpdatingActors = false;
}

void Game::Update()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

	// Update actors
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	// Add pending actors to current actors
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	// Clear dead actors
	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}
	for (auto actor : deadActors)
	{
		delete actor;
	}

	// Respawn all asteroids and potentially spawn enemy
	if (mAsteroids.size() == 0)
	{
		++mLevel;
		SpawnAsteroids();
		RandomSpawnEnemy(0.25f);
	}

	if (mEnemyPresent)
	{
		Vector2 diff = mShip->GetPosition() - mEnemy->GetPosition();
		diff.Normalize();
		float laserRotation = Math::Atan2(-diff.y, diff.x);
		mEnemy->SetLaserRotation(laserRotation);
	}
}

void Game::Render()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);

	// Render sprites
	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}

	SDL_RenderPresent(mRenderer);
}

void Game::LoadData()
{
	// Sounds
	mSounds->LoadChunk("Assets/Sounds/shoot.wav", SoundManager::Shoot);
	mSounds->LoadChunk("Assets/Sounds/explosion.wav", SoundManager::Explosion);
	mSounds->LoadChunk("Assets/Sounds/enemy-shoot.wav", SoundManager::EnemyShoot);

	// Ship
	mShip = new Ship(this);
	mShip->SetPosition(Vector2(512.0f, 384.0f));
	mShip->SetScale(2.0f);

	// Background
	Actor* background = new Actor(this);
	background->SetPosition(Vector2(512.0f, 384.0f));
	// Static background
	BGSpriteComponent* bsc = new BGSpriteComponent(background);
	bsc->SetScreenSize(Vector2(1024.0f, 768.0f));
	std::vector<SDL_Texture*> bgtextures = {
		GetTexture("Assets/Nebula Blue.png"),
		GetTexture("Assets/Nebula Blue.png")
	};
	bsc->SetBGTextures(bgtextures);
	bsc->SetScrollSpeed(-20.0f);
	// Stars
	bsc = new BGSpriteComponent(background);
	bsc->SetScreenSize(Vector2(1024.0f, 768.0f));
	bgtextures = {
		GetTexture("Assets/Stars.png"),
		GetTexture("Assets/Stars.png")
	};
	bsc->SetBGTextures(bgtextures);
	bsc->SetScrollSpeed(-10.0f);

	// Asteroids
	SpawnAsteroids();
}

void Game::UnloadData()
{
	// Delete actors
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	// Delete textures
	for (auto i : mTextures)
	{
		SDL_DestroyTexture(i.second);
	}
	mTextures.clear();
}

void Game::Shutdown()
{
	UnloadData();
	IMG_Quit();
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::AddActor(Actor* actor)
{
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		// 'swap and pop' to avoid copies that would be created when using erase()
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::AddSprite(SpriteComponent* component)
{
	int drawOrder = component->GetDrawOrder();
	auto iter = mSprites.begin();

	for (; iter != mSprites.end(); ++iter)
	{
		if (drawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}
	mSprites.insert(iter, component);
}

void Game::RemoveSprite(SpriteComponent* component)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), component);
	mSprites.erase(iter);
}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
	SDL_Texture* tex = nullptr;
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		SDL_Surface* surface = IMG_Load(fileName.c_str());
		if (!surface)
		{
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}

		tex = SDL_CreateTextureFromSurface(mRenderer, surface);
		if (!tex)
		{
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}
		SDL_FreeSurface(surface);

		mTextures.emplace(fileName.c_str(), tex);
	}

	return tex;
}

void Game::AddAsteroid(Asteroid* asteroid)
{
	mAsteroids.emplace_back(asteroid);
}

void Game::RemoveAsteroid(Asteroid* asteroid)
{
	auto iter = std::find(mAsteroids.begin(), mAsteroids.end(), asteroid);
	if (iter != mAsteroids.end())
	{
		mAsteroids.erase(iter);
	}
}

void Game::SpawnAsteroids()
{
	for (int i = 0; i < (mNumAsteroids - 2) * mLevel; ++i)
	{
		new Asteroid(this);
	}
}

void Game::ClearAsteroids()
{
	for (auto ast : mAsteroids)
	{
		ast->SetState(Actor::EDead);
	}
}

void Game::RandomSpawnEnemy(float prob)
{
	if (Random::GenerateFloat(0.0f, 1.0f) < prob)
	{
		mEnemy = new Enemy(this);
		mEnemyPresent = true;
	}
}

void Game::Reset()
{
	SetLevel(1);
	mShip->Reset();
	if (mEnemyPresent)
	{
		mEnemy->SetState(Actor::EDead);
	}
	ClearAsteroids();
	SpawnAsteroids();
}
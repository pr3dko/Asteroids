#pragma once
#include <SDL.h>
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>
#include "SoundManager.h"

class Game
{
public:
	Game();
	bool Init();
	void Run();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);
	void AddSprite(class SpriteComponent* component);
	void RemoveSprite(class SpriteComponent* component);

	SDL_Texture* GetTexture(const std::string& fileName);

	std::shared_ptr<SoundManager> GetSounds() { return mSounds; }

	// Game specific
	void AddAsteroid(class Asteroid* asteroid);
	void RemoveAsteroid(class Asteroid* asteroid);
	void ClearAsteroids();
	void SpawnAsteroids();
	void RandomSpawnEnemy(float prob);
	void SetLevel(int level) { mLevel = level; }
	std::vector<class Asteroid*>& GetAsteroids() { return mAsteroids; }
	class Ship* GetShip() const { return mShip; }
	void SetEnemyPresent(bool present) { mEnemyPresent = present;}
	class Enemy* GetEnemy() const { return mEnemy;}
	bool IsEnemyPresent() const { return mEnemyPresent; }
	void Reset();

private:
	void ProcessInput();
	void Update();
	void Render();
	void LoadData();
	void UnloadData();

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	bool mIsRunning;
	bool mUpdatingActors;
	bool mEnemyPresent;

	std::vector<class Actor*> mActors;
	std::vector<class Actor*> mPendingActors;
	std::vector<class SpriteComponent*> mSprites;

	std::unordered_map<std::string, SDL_Texture*> mTextures;

	std::shared_ptr<SoundManager> mSounds;

	//Game specific data
	class Ship* mShip;
	class Enemy* mEnemy;
	std::vector<class Asteroid*> mAsteroids;
	int mNumAsteroids;
	int mLevel;
};
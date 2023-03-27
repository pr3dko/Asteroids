#include "SoundManager.h"
#include <SDL.h>

bool SoundManager::Init()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0)
	{
		SDL_Log("Failed to initialise SDL_mixer. Error: %s\n", Mix_GetError());
		return false;
	}

	return true;
}

Mix_Chunk* SoundManager::LoadChunk(const std::string& filename, ID id)
{
	Mix_Chunk* chunk = Mix_LoadWAV(filename.c_str());
	if (!chunk)
	{
		SDL_Log("Failed to load chunk at %s. Error: %s\n", filename.c_str(), Mix_GetError());
		return nullptr;
	}

	mChunks[id] = chunk;
	return mChunks[id];
}

Mix_Music* SoundManager::LoadMusic(const std::string& filename, ID id)
{
	Mix_Music* music = Mix_LoadMUS(filename.c_str());
	if (!music)
	{
		SDL_Log("Failed to load music at %s. Error: %s\n", filename.c_str(), Mix_GetError());
		return nullptr;
	}

	mMusic[id] = music;
	return mMusic[id];
}

void SoundManager::PlayChunk(ID id)
{
	if (mChunks.find(id) != mChunks.end())
	{
		Mix_PlayChannel(-1, mChunks[id], 0);
	}
	else
	{
		SDL_Log("Error: could not play sound\n");
	}
}

void SoundManager::PlayMusic(ID id)
{
	if (Mix_PlayingMusic())
	{
		Mix_HaltMusic();
	}

	Mix_PlayMusic(mMusic[id], -1);
}

void SoundManager::StopMusic()
{
	Mix_HaltMusic();
}

SoundManager::~SoundManager()
{
	for (auto iter = mChunks.begin(); iter != mChunks.end(); ++iter)
	{
		Mix_FreeChunk(iter->second);
		iter->second = nullptr;
	}
	for (auto iter = mMusic.begin(); iter != mMusic.end(); ++iter)
	{
		Mix_FreeMusic(iter->second);
		iter->second = nullptr;
	}

	Mix_Quit();
}
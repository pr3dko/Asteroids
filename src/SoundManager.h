#pragma once
#include <string>
#include <SDL_mixer.h>
#include <map>

class SoundManager
{
public:
	enum ID {Shoot, EnemyShoot, Explosion, EnemyAppears};
	bool Init();
	Mix_Chunk* LoadChunk(const std::string& filename, ID id);
	Mix_Music* LoadMusic(const std::string& filename, ID id);
	void PlayChunk(ID id);
	void PlayMusic(ID id);
	void StopMusic();
	~SoundManager();

private:
	std::map<ID, Mix_Chunk*> mChunks;
	std::map<ID, Mix_Music*> mMusic;
};
#include "Explosion.h"
#include "AnimSpriteComponent.h"
#include "Game.h"

Explosion::Explosion(Game* game) : Actor(game), mDeathTimer(1.0f)
{
	mAnim = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> textures;
	// Load animation frames
	for (int i = 1; i <= 71; ++i)
	{
		std::string filename = "Assets/Explosion/frame (" + std::to_string(i) + ").png";
		textures.emplace_back(game->GetTexture(filename));
	}
	mAnim->SetAnimTextures(textures);
	mAnim->AddAnim("Default", 0, 70);
	mAnim->SetAnim("Default", false);
	mAnim->SetAnimFPS(70.0f);
}

void Explosion::UpdateActor(float deltaTime)
{
	mDeathTimer -= deltaTime;
	if (mDeathTimer <= 0.0f)
	{
		SetState(EDead);
	}
}
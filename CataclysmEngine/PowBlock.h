#pragma once

#ifndef _POW_BLOCK_H
#define _POW_BLOCK_H



#include <SDL.h>
#include <string>//
#include <iostream>//
#include "LevelMap.h"//
#include "Commons.h"
#include "Texture2D.h"//

class LevelMap;
class Texture2D;

class PowBlock
{
public:
	PowBlock(SDL_Renderer* renderer, LevelMap* map);
	~PowBlock();

	void Render();
	Rect2D GetCollisionBox();
	void TakeAHit();
	bool IsAvailable() { return mNumberOfHitsLeft > 0; };

private:
	SDL_Renderer * mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	LevelMap* mLevelMap;

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	int mNumberOfHitsLeft;
};

#endif // !_POW_BLOCK_H
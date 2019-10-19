#include "PowBlock.h"
#include <string>
#include "Texture2D.h"
#include <iostream>
#include "Constants.h"
#include "LevelMap.h"

using namespace std;

PowBlock::PowBlock(SDL_Renderer* renderer, LevelMap* map)
{
	string imagePath = "Images/PowBlock.png";
	mTexture = new Texture2D(renderer);

	if (!mTexture->LoadFromFile(imagePath.c_str()))
	{
		cout << "Failed to load PowBlock texture: " << imagePath << endl;
		return;
	}

	mLevelMap = map;
	mSingleSpriteWidth = mTexture->GetWidth() / 3; //3 Sprites on this spritesheet in 1 row
	mSingleSpriteHeight = mTexture->GetHeight();
	mNumberOfHitsLeft = 3;
	mPosition = Vector2D((SCREEN_WIDTH * 0.5f) - mSingleSpriteWidth * 0.5f, 260);

}

PowBlock::~PowBlock()
{
	mRenderer = NULL;
	delete mTexture;
	mTexture = NULL;
	mLevelMap = NULL;
}

void PowBlock::TakeAHit()
{
	mNumberOfHitsLeft--;          //-= 1;

	if (mNumberOfHitsLeft <= 0)
	{
		mNumberOfHitsLeft = 0;
		mLevelMap->ChangeTileAt(8, 7, 0);
		mLevelMap->ChangeTileAt(8, 8, 0);
	}
}



void PowBlock::Render()
{
	if (mNumberOfHitsLeft > 0)
	{
		//Get the portion of the spritesheet you want to draw.
		int left = mSingleSpriteWidth * (mNumberOfHitsLeft - 1);

		//								{XPos, YPos, WidthOfSingleSprite, HeightOfSingleSprite}
		SDL_Rect portionOfSpritesheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };

		//Determins where you want it drawn.
		SDL_Rect destRect = { (int)(mPosition.x), (int)(mPosition.y), mSingleSpriteWidth, mSingleSpriteHeight };

		//Then Draw it
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	}
}

Rect2D PowBlock::GetCollisionBox()
{
	return Rect2D(mPosition.x, mPosition.y, mSingleSpriteWidth, mTexture->GetHeight());     // mTexture->GetWidth(), mTexture->GetHeight());
}



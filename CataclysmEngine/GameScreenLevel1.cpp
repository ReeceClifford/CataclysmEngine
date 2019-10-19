#include "GameScreenLevel1.h"
#include <iostream>
#include "Texture2D.h"
#include "Collisions.h"
#include "PowBlock.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	myCharacterMario->Update(deltaTime, e);
	myCharacterLuigi->Update(deltaTime, e);

	if (Collisions::Instance()->Circle(myCharacterMario, myCharacterLuigi))
	{

	}
	
	if ((Collisions::Instance()->Box(myCharacterMario->GetCollisionBox(), myCharacterLuigi->GetCollisionBox())))
	{

	}
	
	UpdatePowBlock();
	//UpdateEnimies(deltaTime, e)

	//Do When Screenshake is needed
	if (mScreenshake)
	{
		mScreenshakeTime -= deltaTime;
		mWobble++;
		mBackgroundYPos = sin(mWobble);
		mBackgroundYPos *= 3.0f;

		//End the shake after the duration
		if (mScreenshakeTime <= 0.0f)
		{
			mScreenshake = false;
			mBackgroundYPos = 0.0f;
		}
	}
	
}

void GameScreenLevel1::Render()
{
	/*for (unsigned int i = 0; i < mEnemies.size(); i++)
	{
		mEnemies[i]->Render();
	}*/
	//Draw the background
	mBackgroundTexture->Render(Vector2D(0, mBackgroundYPos), SDL_FLIP_NONE);
	myCharacterMario->Render();
	myCharacterLuigi->Render();
	mPowBlock->Render();
}

bool GameScreenLevel1::SetUpLevel()
{
	//Load the background texture
	mBackgroundTexture = new Texture2D(mRenderer);
	if (!mBackgroundTexture->LoadFromFile("Images/BackgroundMB.png"))
	{
		cout << "Failed to load background texture";
			return false;
	}

	//Set up level map
	SetLevelMap(); 

	//Set up PowBlock
	mPowBlock = new PowBlock(mRenderer, mLevelMap);

	//Set up Screenshake
	mScreenshake = false;
	mBackgroundYPos = 0.0f;

	//Set up the Player Character 
	myCharacterMario = new CharacterMario(mRenderer, "Images/Mario.png", Vector2D(0, 0), mLevelMap );
	myCharacterLuigi = new CharacterLuigi(mRenderer, "Images/Luigi.png", Vector2D(10, 10), mLevelMap);

	return true;
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = {	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
										{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	if (mLevelMap != NULL)
	{
		delete mLevelMap;
	}

	mLevelMap = new LevelMap(map);

}

void GameScreenLevel1::UpdatePowBlock()
{
	if ((Collisions::Instance()->Box(myCharacterMario->GetCollisionBox(), mPowBlock->GetCollisionBox())))
	{
		if (mPowBlock->IsAvailable())
		{
			if (myCharacterMario->IsJumping())
			{
				DoScreenshake();
				mPowBlock->TakeAHit();
				myCharacterMario->CancelJump();
			}
		}
	}

	if ((Collisions::Instance()->Box(myCharacterLuigi->GetCollisionBox(), mPowBlock->GetCollisionBox())))
	{
		if (mPowBlock->IsAvailable())
		{
			if (myCharacterLuigi->IsJumping())
			{
				DoScreenshake();
				mPowBlock->TakeAHit();
				myCharacterLuigi->CancelJump();
			}
		}
	}
}

void GameScreenLevel1::DoScreenshake()
{
	mScreenshake = true;
	mScreenshakeTime = SCREENSHAKE_DURATION;
	mWobble = 0.0f;
}

GameScreenLevel1::~GameScreenLevel1()
{
	mBackgroundTexture = NULL;
	myCharacterMario = NULL;
	myCharacterLuigi = NULL;
	mLevelMap = NULL;
	delete mPowBlock;
	mPowBlock = NULL;
	//mEnemies.clear();
}


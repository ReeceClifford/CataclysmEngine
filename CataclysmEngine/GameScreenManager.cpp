#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenManager.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	mRenderer = renderer;
	mCurrentScreen = NULL;
	//Ensure first screen is set up
	ChangeScreen(startScreen);
	
}

void GameScreenManager::ChangeScreen(SCREENS newScreen)
{
	//Clear up the old screen
	if (mCurrentScreen != NULL)
	{
		delete mCurrentScreen;

	}
	GameScreenLevel1* tempScreen;

	switch (newScreen)
	{
	case SCREEN_INTRO:

		break;

	case SCREEN_LEVEL1:
		tempScreen = new GameScreenLevel1(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreen;
		tempScreen = NULL;
		break;
	}

	
}

void GameScreenManager::Render()
{
	mCurrentScreen->Render();
}
void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	mCurrentScreen->Update(deltaTime, e);
}


GameScreenManager::~GameScreenManager() 
{
	mRenderer = NULL;
	delete mCurrentScreen;
	mCurrentScreen = NULL;
}
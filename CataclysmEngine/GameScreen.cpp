#include "GameScreen.h"

GameScreen::GameScreen(SDL_Renderer* renderer)
{
	mRenderer = renderer;
}


void GameScreen::Render()
{

}

void GameScreen::Update(float deltaTime, SDL_Event e)
{

}

GameScreen::~GameScreen()
{
	mRenderer = NULL;
}
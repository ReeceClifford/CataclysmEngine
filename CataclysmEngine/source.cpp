#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Constants.h"
#include <iostream>
#include "Commons.h"
#include "Texture2D.h"
#include "GameScreenManager.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
//Texture2D* testImage;
GameScreenManager* gameScreenManager;
Uint32 gOldTime;

using namespace std;

bool InitSDL();
void CloseSDL();
bool Update();
void Render();

int main(int argc, char* args[])
{
	//Check if SDL was set up correctly 
	if (InitSDL())
	{
		gameScreenManager = new GameScreenManager(gRenderer, SCREEN_LEVEL1);
		//gameScreenManager = new GameScreenManager(gRenderer, SCREEN_INTRO); Addtional Work?
		gOldTime = SDL_GetTicks();
		bool quit = false;
		while (!quit)
		{
			Render();
			quit = Update();

		}
	}
	//Close Window and free resources.
	CloseSDL();
	return 0;
}

bool Update()
{
	Uint32 newTime = SDL_GetTicks();

	// Event Handler 
	SDL_Event e;

	// Get the Events
	SDL_PollEvent(&e);

	//Handle any events.
	switch (e.type)
	{
	case SDL_QUIT:
		return true;
		break;

	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_x:
			// gameScreenManager->ChangeScreen(SCREEN_LEVEL1); Addtional Work?
			break;
		}
	case SDL_MOUSEBUTTONDOWN:
		switch (e.button.button)
		{
		case SDL_BUTTON_RIGHT:
			return true;
			break;
		}

	}
	gameScreenManager->Update((float)(newTime - gOldTime) / 1000.0f, e);
	gOldTime = newTime;
	return false;
}

bool InitSDL()
{
	//Setup SDL.
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		gWindow = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
		if (gRenderer != NULL)
		{
			//IntialisePNG
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
				return false;
			}

			//testImage = new Texture2D(gRenderer);
			//testImage->LoadFromFile("Images/test.bmp");
			
		}
		else
		{
			cout << "Renderer could not initialise. Error: " << SDL_GetError();
			return false;
		}
		//Did Window get Created
		if (gWindow == NULL)
		{
			//Not created
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}
		return true;
	}

}
void Render()
{
	//Clear the screen.
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(gRenderer);

	gameScreenManager->Render();

	//testImage->Render(Vector2D(), SDL_FLIP_NONE);

	//Update the screen
	SDL_RenderPresent(gRenderer);
}


//SDL_Texture* LoadTextureFromFile(string path)
//{
//	Remove the memory used for a previous texture
//	FreeTexture();
//
//	SDL_Texture* pTexture = NULL;
//
//	Load the Image
//	SDL_Surface* pSurface = IMG_Load(path.c_str());
//	if (pSurface != NULL)
//	{
//		pTexture = SDL_CreateTextureFromSurface(gRenderer, pSurface);
//		if (pTexture == NULL)
//		{
//			cout << "Unable to create texture from surface. Error: " << SDL_GetError() << endl;
//		}
//		Remove the loaded surface now that we have the texture.
//		SDL_FreeSurface(pSurface);
//	}
//	else
//	{
//		cout << "Unable to create texture from Surface. Error: " << IMG_GetError() << endl;
//	}
//
//	return the texture
//	return pTexture;
//
//}

void CloseSDL()
{
	// Release the window.
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;
	IMG_Quit();
	SDL_Quit();
	//delete testImage;
	delete gameScreenManager;
	gameScreenManager = NULL;
}
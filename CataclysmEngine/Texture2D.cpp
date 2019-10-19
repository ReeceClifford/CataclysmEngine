#include <SDL_image.h>
#include <iostream>
#include "Texture2D.h"
#include "Constants.h"


using namespace std;

Texture2D::Texture2D(SDL_Renderer* renderer)
{
	mRenderer = renderer;
}



bool Texture2D::LoadFromFile(string path) 
{
	//Remove the memory used for a previous texture
	Free();
	//Load the Image
	SDL_Surface* pSurface = IMG_Load(path.c_str());
	if (pSurface != NULL)
	{
		mTexture = SDL_CreateTextureFromSurface(mRenderer, pSurface);
		if (mTexture == NULL)
		{
			cout << "Unable to create texture from surface. Error: " << SDL_GetError() << endl;
		}
		//Remove the loaded surface now that we have the texture.
		SDL_FreeSurface(pSurface);

		mWidth = pSurface->w;
		mHeight = pSurface->h;

	}
	else
	{
		cout << "Unable to create texture from Surface. Error: " << IMG_GetError() << endl;
	}

	//return the texture
	return mTexture != NULL;
}

void Texture2D::Free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
	}
}

void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle) 
{
	//Set where to render the texture
	SDL_Rect renderLocation = { newPosition.x, newPosition.y, mWidth, mHeight };

	//Render to screen
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, 0, NULL, flip);
}

void Texture2D::Render(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip, double angle)
{
	//Render to screen
	SDL_RenderCopyEx(mRenderer, mTexture, &srcRect, &destRect, angle, NULL, flip);
}

Texture2D::~Texture2D()
{
	Free();
}
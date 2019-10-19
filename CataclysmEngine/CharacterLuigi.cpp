#include "CharacterLuigi.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map)
{

}

void CharacterLuigi::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
		//Deal with keyboard Input.
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			mMovingLeft = false;
			break;
		case SDLK_d:
			mMovingRight = false;
			break;
		default:
			break;
		}
		break;
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			Jump();
			break;
		case SDLK_s:
			break;
		case SDLK_a:
			mMovingRight = false;
			mMovingLeft = true;
			break;
		case SDLK_d:
			mMovingLeft = false;
			mMovingRight = true;
			break;

		default:
			break;
		}
		break;
	}

	Character::Update(deltaTime, e);
}

CharacterLuigi::~CharacterLuigi()
{

}

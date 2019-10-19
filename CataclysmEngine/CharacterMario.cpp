#include "CharacterMario.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map) : Character (renderer,imagePath,startPosition,map)
{

}

void CharacterMario::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
		//Deal with keyboard Input.
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			mMovingLeft = false;
			break;
		case SDLK_RIGHT:
			mMovingRight = false;
			break;
		default:
			break;
		}
		break;
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			Jump();
			break;
		case SDLK_DOWN:
			break;
		case SDLK_LEFT:
			mMovingRight = false;
			mMovingLeft = true;
			break;
		case SDLK_RIGHT:
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

CharacterMario::~CharacterMario()
{

}

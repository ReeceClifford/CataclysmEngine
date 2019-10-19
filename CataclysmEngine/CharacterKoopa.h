#pragma once
#include "Character.h"
#include "Texture2D.h"
class CharacterKoopa  : public Character
{
public:
	CharacterKoopa(SDL_Renderer* renderer, string imagePath, LevelMap* map, Vector2D startPosition, FACING startFacting, float movementSpeed);;
	~CharacterKoopa();

	virtual void Update(float deltaTime, SDL_Event e);
	virtual void Render();

	void TakeDamage();
	void Jump();

private:
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	float mMovementSpeed;

	bool mInjured;
	float mInjuredTime;

	void FlipRightWayUp();
};


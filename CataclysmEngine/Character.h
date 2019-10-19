#pragma once
#ifndef _CHARACTER
#define _CHARACTER

#include <SDL.h>
#include <iostream>
#include <string>
#include "Commons.h"
#include "LevelMap.h"
using namespace std;

class Texture2D;

class Character
{
protected:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	FACING mFacingDirection;

	bool mMovingLeft;
	bool mMovingRight;

	bool mCanJump;
	float mJumpForce;

	float mCollisionRadius;
	
	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	virtual void AddGravity(float deltaTime);
	virtual void Jump();

public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition(); 

	float GetCollisionRadius();
	
	Rect2D GetCollisionBox();
	bool mJumping;
	bool IsJumping() { return mJumping; }
	void CancelJump() { mJumping = false; }
	
private:
	LevelMap * mCurrentLevelMap;
};

#endif //_CHARACTER

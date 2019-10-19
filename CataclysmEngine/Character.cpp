#include "Character.h"
#include "Texture2D.h"
#include "Constants.h"
#include <string>
using namespace std;

Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition, LevelMap* map)
{
	mRenderer = renderer;
	mTexture = new Texture2D(renderer);
	mTexture->LoadFromFile(imagePath);
	mPosition = startPosition;
	mFacingDirection = FACING_RIGHT;
	mMovingLeft = false;
	mMovingRight = false;
	mCollisionRadius = 15.0f;
	mCurrentLevelMap = map;
}

void Character::Render()
{
	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(mPosition, SDL_FLIP_NONE, 0.0);
	}
	else
	{
		mTexture->Render(mPosition, SDL_FLIP_HORIZONTAL, 0.0);
	}
}

void Character::Update(float deltaTime, SDL_Event e)
{
	//Deal with Jumping first
	if (mJumping)
	{
		//Adjust the position.
		mPosition.y -= mJumpForce * deltaTime;

		//Reduce the Jump Force
		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		//Has the Jump force reduced to zero>
		if (mJumpForce <= 0.0f)
			mJumping = false;
	}
	if (mMovingLeft)
	{
		MoveLeft(deltaTime);
	}
	else if (mMovingRight) 
	{
		MoveRight(deltaTime);
	}

	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_x:
			exit(0);
			break;
		}
	}		
	
	int centralXPosition = (int)(mPosition.x + (mTexture->GetWidth()*0.5f)) / TILE_WIDTH;
	int footPosition = (int)(mPosition.y + mTexture->GetHeight()) / TILE_HEIGHT;

	if (mCurrentLevelMap->GetTileAt(footPosition, centralXPosition) == 0)
	{
		AddGravity(deltaTime);
	}
	else
	{
		//Collided with ground so we can jump again
		mCanJump = true;
	}
	
}

void Character::SetPosition(Vector2D newPosition)
{
	mPosition = newPosition; 
}

Vector2D Character::GetPosition()
{
	return mPosition;
}

void Character::MoveLeft(float deltaTime)
{
	mFacingDirection = FACING_LEFT;
	mPosition.x -= (MovementSpeed * deltaTime);
}

void Character::MoveRight(float deltaTime)
{
	mFacingDirection = FACING_RIGHT;
	mPosition.x += (MovementSpeed * deltaTime);
}

void Character::AddGravity(float deltaTime)
{	
	mPosition.y += GRAVITY * deltaTime;
	mCanJump = false;

	//if(mPosition.y + mTexture->GetHeight() <= SCREEN_HEIGHT)
	//	mPosition.y += (MovementSpeed * deltaTime);
	//else
	//{
	//	//Collided with ground so can jump
	//	mCanJump = true;
	//}
}

void Character::Jump()
{
	if (!mJumping && mCanJump)
	{
		mJumpForce = INITIAL_JUMP_FORCE;
		mJumping = true;
		mCanJump = false;
	}
}

float Character::GetCollisionRadius() 
{
	return mCollisionRadius;
}

Rect2D Character::GetCollisionBox()
{
	return Rect2D(mPosition.x, mPosition.y, mTexture->GetWidth(), mTexture->GetHeight());
}

Character::~Character()
{
	mRenderer = NULL;
}


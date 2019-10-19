#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H
#include <SDL.h>
#include "Commons.h"
#include "GameScreen.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "LevelMap.h"
#include "PowBlock.h"
#include <vector>



class Character;
class Texture2D;
class PowBlock;
class CharacterKoopa;

class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();
	// Create a pointer to gamescreen manager, so gamescreen level 1 can access the gamescreen manager when it needs to be changed addtional work Tutorial 6
	void Render();
	void Update(float deltaTime, SDL_Event e);
	void UpdatePowBlock();
	//void UpdateEnimies(float deltaTime, SDL_Event e);
	//void CreateKoopa(Vector2D position, FACING direction, float speed);

private:
	Texture2D * mBackgroundTexture;
	Character* myCharacterMario;
	Character* myCharacterLuigi;
	bool SetUpLevel();

	void SetLevelMap();
	LevelMap * mLevelMap;

	PowBlock * mPowBlock;

	vector<CharacterKoopa*> mEnemies;

	//Screenshake Values
	bool mScreenshake;
	float mScreenshakeTime;
	float mWobble;
	float mBackgroundYPos;
	void DoScreenshake();
};
#endif //_GAMESCREENLEVEL1_H
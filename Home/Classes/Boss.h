#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Boss
{
public:
	Boss(Vec2 pos, float bL, float bR, float bD);

	void Movement(float dt);

	Sprite* GetSprite();

	Sprite* healthBar;

	void GotHit();

private:
	Sprite* sprite;
	Vec2 speed;
	float boundL;
	float boundR;
	float boundD;

	float timerTomove;
	int timeToMove;
};
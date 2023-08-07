#pragma once
#include "cocos2d.h"

using namespace cocos2d;
#define BULLETSNUM 10

class Boss
{
public:

	class ThrustBullets
	{
	public:

		ThrustBullets();

		void Movement(float dt);

		Sprite* bSprite[BULLETSNUM];

		Vec2 bSpeed[BULLETSNUM];

		float timer;
	};

	Boss(Vec2 pos, float bL, float bR, float bD);

	void Movement(float dt);

	Sprite* GetSprite();

	Sprite* healthBar;

	void GotHit();

	void Shoot();

	ThrustBullets bullets;

private:
	Sprite* sprite;
	Vec2 speed;
	float boundL;
	float boundR;
	float originY;

	float timerShot;
};
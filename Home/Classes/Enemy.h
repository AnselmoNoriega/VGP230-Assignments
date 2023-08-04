#pragma once
#include "cocos2d.h"

using namespace cocos2d;
#define BULLETCOUNT 5

class Enemy
{
public:

	class Blasts
	{
	public:

		Blasts();

		Sprite* GetSprite();

		void LaunchBullet(Vec2 pos);
		void Movement(float dt);

	private:
		float speed;
		Sprite* sprite;
		Vec2 launchingPos;
	};

	Enemy(Vec2 pos);

	Sprite* GetSprite();

	void Move(float dt, float boundL, float boundR);
	void BulletMovement(float dt, float lowerBound);

	void FireBullet();

	Blasts lasers[BULLETCOUNT];

private:
	Sprite* sprite;
	Vec2 speed;
	float startPosY;
	float shootTimer;
};
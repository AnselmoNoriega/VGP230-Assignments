#pragma once
#include "cocos2d.h"

using namespace cocos2d;
#define BULLETCOUNT 5

class Enemy
{
	class Bullets
	{
	public:

		Bullets();

		Sprite* GetSprite();

		void LaunchBullet(Vec2 pos);
		void Movement(float dt);

	private:
		float speed;
		Sprite* sprite;
		Sprite* launchingPos;
	};

	Enemy(Vec2 pos);

	Sprite* GetSprite();
	Vec2 GetPos();

	void SetPosition(Vec2 pos);
	void SetLeft(bool condition);
	void SetRight(bool condition);
	void Move(float dt, float boundL, float boundR);
	void BulletMovement(float dt, float topBound);

	Bullets lasers[BULLETCOUNT];
};
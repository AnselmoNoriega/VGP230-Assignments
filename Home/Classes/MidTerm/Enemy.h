#pragma once
#include "cocos2d.h"

using namespace cocos2d;
#define BULLETCOUNT 2

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
		Sprite* bSprite;
		Vec2 launchingPos;
	};

	Enemy(Vec2 pos, Vec2 speed);

	Sprite* GetSprite();

	void Move(float dt, float boundL, float boundR);

	void FireBullet();

	void DrawCollisionBox();

	Blasts lasers[BULLETCOUNT];

	DrawNode* debug = DrawNode::create(5);

private:
	Sprite* sprite;
	Vec2 mSpeed;
	float startPosY;
	float shootTimer;
	float timeToShoot;
	int bulletIndex;
	int speeder;
	int pathMultiplier;

	float dx;
	float dy;
	float bx;
	float by;
	Color4F color;
	Color4F bulletColor;
	bool isColliderOn;
};
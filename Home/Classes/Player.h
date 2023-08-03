#pragma once
#include "cocos2d.h"

#define MAXBULLETS 5
using namespace cocos2d;

class Player
{
public:

	class Bullets
	{
	public:

		Bullets();

		std::pair <cocos2d::Sprite*, cocos2d::Sprite*> GetSprite();

		void LaunchBullet(Vec2 pos);
		void Movement(float dt, float topBound);

	private:
		float speed;
		std::pair < cocos2d::Sprite*, cocos2d::Sprite*> sprite;
		std::pair < cocos2d::Vec2, cocos2d::Vec2> launchingPos;
	};

	Player(Vec2 pos);

	Sprite* GetSprite();
	Vec2 GetPos();

	void SetPosition(Vec2 pos);
	void SetLeft(bool condition);
	void SetRight(bool condition);
	void Move(float dt, float boundL, float boundR);
	void BulletMovement(float dt, float topBound);

	Bullets lasers[MAXBULLETS];

private:
	Sprite* sprite;
	float speed;
	bool _right;
	bool _left;
};

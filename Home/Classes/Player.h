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

		std::pair <Sprite*, Sprite*> GetSprite();

		void LaunchBullet(Vec2 pos);
		void Movement(float dt, float topBound);

	private:
		float speed;
		std::pair < Sprite*, Sprite*> sprite;
		std::pair < Vec2, Vec2> launchingPos;
	};

	Player(Vec2 pos);

	Sprite* GetSprite();
	Vec2 GetPos();

	void SetPosition(Vec2 pos);
	void SetLeft(bool condition);
	void SetRight(bool condition);
	void Move(float dt, float boundL, float boundR);
	void BulletMovement(float dt, float topBound);

	void PlayerGotHit();

	void DrawCollisionBox();

	Bullets lasers[MAXBULLETS];

	DrawNode* debug = DrawNode::create(5);
	Sprite* health;

private:
	Sprite* sprite;
	float speed;
	bool _right;
	bool _left;

	float dx;
	float dy;
	float bx;
	float by;
	Color4F color;
	Color4F bulletColor;
};

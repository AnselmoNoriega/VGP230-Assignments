#include "Boss.h"

Boss::Boss(Vec2 pos, float bL, float bR, float bD)
{
	sprite = Sprite::create("carrier_01.png");
	sprite->setPosition(pos);
	sprite->setScale(5);

	healthBar = Sprite::create("bar_red.png");
	healthBar->setScaleX(healthBar->getScaleX() + 3);

	boundL = bL;
	boundR = bR;
	boundD = bD;

	timerTomove = 0;
	timeToMove = 7;
}

void Boss::Movement(float dt)
{
	timerTomove += dt;

	if (timeToMove >= timeToMove)
	{
		
		timerTomove = 0.0f;
	}
}

Sprite* Boss::GetSprite()
{
	return sprite;
}

void Boss::GotHit()
{
	healthBar->setScaleX(healthBar->getScaleX() - 0.1f);
}



#include "Boss.h"

Boss::Boss(Vec2 pos, float bL, float bR, float bD)
{
	sprite = Sprite::create("carrier_01.png");
	sprite->setPosition(pos);
	sprite->setScale(5);

	healthBar = Sprite::create("bar_red.png");
	healthBar->setScaleX(healthBar->getScaleX() + 3);

	boundL = bL + sprite->getContentSize().width * 4;
	boundR = bR - sprite->getContentSize().width * 4;

	originY = pos.y;

	speed = { 700, 300 };

	timerShot = 3;
}

void Boss::Movement(float dt)
{
	sprite->setPositionX(sprite->getPositionX() + speed.x * dt);
	sprite->setPositionY(sprite->getPositionY() + speed.y * dt);

	if (sprite->getPositionX() >= boundR || sprite->getPositionX() <= boundL)
	{
 		speed.x *= -1;
	}

	if (sprite->getPositionY() >= originY + 200 || sprite->getPositionY() <= originY - 350)
	{
		speed.y *= -1;
	}

	timerShot -= dt;
	Shoot();
	bullets.Movement(dt);
}

Sprite* Boss::GetSprite()
{
	return sprite;
}

void Boss::GotHit()
{
	healthBar->setScaleX(healthBar->getScaleX() - 0.1f);
}

void Boss::Shoot()
{
	if (timerShot <= 0)
	{
		for (int i = 0; i < BULLETSNUM; ++i)
		{
			bullets.bSprite[i]->setPosition(sprite->getPosition());
			bullets.bSprite[i]->setVisible(true);
		}

		timerShot = 3;
	}
}

Boss::ThrustBullets::ThrustBullets()
{
	int degree = 195;

	for (int i = 0; i < BULLETSNUM; ++i)
	{
		bSprite[i] = Sprite::create("bullet2.png");
		bSprite[i]->setScale(5);
		bSprite[i]->setVisible(false);

		bSpeed[i] = {(float)cos(degree) * 1000, (float)sin(degree) * 1000};
		degree += 30;
	}

	timer = 3;
}

void Boss::ThrustBullets::Movement(float dt)
{
	if (bSprite[0]->isVisible())
	{
		for (int i = 0; i < BULLETSNUM; ++i)
		{
			bSprite[i]->setPosition({ bSprite[i]->getPositionX() + bSpeed[i].x * dt, bSprite[i]->getPositionY() + bSpeed[i].y * dt});
		}

		timer -= dt;
	}

	if (timer <= 0)
	{
		for (int i = 0; i < BULLETSNUM; ++i)
		{
			bSprite[i]->setVisible(false);
		}

		timer = 3;
	}
}

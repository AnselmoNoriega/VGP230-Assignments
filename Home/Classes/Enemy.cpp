#include "Enemy.h"

Enemy::Enemy(Vec2 pos)
{
	sprite = Sprite::create("interceptor.png");
	sprite->setPosition(pos);
	speed = { 700, 100 };
	startPosY = sprite->getPositionY();
	shootTimer = 0;
	speeder = 100;
	pathMultiplier = 5000;
	timeToShoot = 5;
	bulletIndex = 0;
}

Sprite* Enemy::GetSprite()
{
	return sprite;
}

void Enemy::Move(float dt, float boundL, float boundR)
{
	if (sprite->getPositionX() >= boundR || sprite->getPositionX() <= boundL)
	{
		speed.x *= (-1);
	}
	sprite->setPositionX(sprite->getPositionX() + speed.x * dt);
	sprite->setPositionY(startPosY + sin(sprite->getPositionX() / speeder) * pathMultiplier * dt);

	shootTimer += dt;
	FireBullet();

	for (int i = 0; i < BULLETCOUNT; i++)
	{
		if (lasers[i].GetSprite()->isVisible())
		{
			lasers[i].Movement(dt);
		}
	}
}

void Enemy::FireBullet()
{
	if (bulletIndex >= BULLETCOUNT)
	{
		bulletIndex = 0;
	}

	if (shootTimer >= timeToShoot)
	{
		lasers[bulletIndex].LaunchBullet(sprite->getPosition());
		sprite->setVisible(true);
		++bulletIndex;
		shootTimer = 0;
	}
}

Enemy::Blasts::Blasts()
{
	speed = -1000;
	bSprite = Sprite::create("bullet2.png");
	launchingPos = { 0 , -bSprite->getContentSize().height / 2 };
	bSprite->setVisible(false);
}

Sprite* Enemy::Blasts::GetSprite()
{
	return bSprite;
}

void Enemy::Blasts::LaunchBullet(Vec2 pos)
{
	bSprite->setPosition(pos + launchingPos);
}

void Enemy::Blasts::Movement(float dt)
{
	bSprite->setPosition(bSprite->getPositionX(), bSprite->getPositionY() + speed * dt);

	if (bSprite->getPositionY() <= 0)
	{
		bSprite->setVisible(false);
	}
}

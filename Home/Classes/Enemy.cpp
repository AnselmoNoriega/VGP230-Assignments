#include "Enemy.h"

Enemy::Enemy(Vec2 pos)
{
	sprite = Sprite::create("interceptor.png");
	sprite->setPosition(pos);
	speed = { 700, 100 };
	startPosY = sprite->getPositionY();
	shootTimer = 0;
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
	sprite->setPositionY(startPosY + sin(sprite->getPositionX() / 100) * 5000 * dt);
}

void Enemy::BulletMovement(float dt, float lowerBound)
{

}

void Enemy::FireBullet()
{

}

Enemy::Blasts::Blasts()
{
	speed = -1000;
	sprite = Sprite::create("bullet2.png");
	launchingPos = { 0 , -sprite->getContentSize().height / 2 };
	sprite->setVisible(false);
}

Sprite* Enemy::Blasts::GetSprite()
{
	return nullptr;
}

void Enemy::Blasts::LaunchBullet(Vec2 pos)
{

}

void Enemy::Blasts::Movement(float dt)
{

}

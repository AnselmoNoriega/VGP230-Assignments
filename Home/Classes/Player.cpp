#pragma once
#include "Player.h"

Player::Player(Vec2 pos)
{
	sprite = Sprite::create("fighter.png");
	sprite->setPosition(pos);
	speed = 500;
	_left = false;
	_right = false;
}

Sprite* Player::GetSprite()
{
	return sprite;
}

Vec2 Player::GetPos()
{
	return sprite->getPosition();
}

void Player::SetPosition(Vec2 pos)
{
	sprite->setPosition(pos);
}

void Player::SetLeft(bool condition)
{
	_left = condition;
}

void Player::SetRight(bool condition)
{
	_right = condition;
}

void Player::Move(float dt, float boundL, float boundR)
{
	if (_right && sprite->getPosition().x < boundR - sprite->getContentSize().width / 2)
	{
		sprite->setPosition(sprite->getPosition().x + speed * dt, sprite->getPosition().y);
	}
	else if (_left && sprite->getPosition().x > boundL + sprite->getContentSize().width / 2)
	{
		sprite->setPosition(sprite->getPosition().x - speed * dt, sprite->getPosition().y);
	}
}

void Player::BulletMovement(float dt, float topBound)
{
	for (auto bullet : lasers)
	{
		if (bullet.GetSprite().first->isVisible())
		{
			bullet.Movement(dt, topBound);
		}
	}
}

Player::Bullets::Bullets()
{
	sprite.first = Sprite::create("bullet1.png");
	sprite.second = Sprite::create("bullet1.png");
	launchingPos.first = { 18, 22 };
	launchingPos.second = { -18, 22 };
	sprite.first->setVisible(false);
	sprite.second->setVisible(false);
	speed = 800.0f;
}

std::pair < cocos2d::Sprite*, cocos2d::Sprite*> Player::Bullets::GetSprite()
{
	return sprite;
}

void Player::Bullets::LaunchBullet(Vec2 pos)
{
	if (!sprite.first->isVisible())
	{
		sprite.first->setPosition(pos + launchingPos.first);
		sprite.second->setPosition(pos + launchingPos.second);
		sprite.first->setVisible(true);
		sprite.second->setVisible(true);
	}
}

void Player::Bullets::Movement(float dt, float topBound)
{
	if (sprite.first->getPositionY() >= topBound)
	{
		sprite.first->setVisible(false);
		sprite.second->setVisible(false);
	}

	if (sprite.first->isVisible())
	{
		sprite.first->setPosition({ sprite.first->getPosition().x, sprite.first->getPosition().y + speed * dt });
		sprite.second->setPosition({ sprite.second->getPosition().x, sprite.second->getPosition().y + speed * dt });
	}
}

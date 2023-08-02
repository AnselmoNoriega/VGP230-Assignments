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

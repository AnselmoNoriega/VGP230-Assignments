#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Player
{
public:
	Player(Vec2 pos);

	Sprite* GetSprite();

	void SetPosition(Vec2 pos);
	void SetLeft(bool condition);
	void SetRight(bool condition);
	void Move(float dt, float boundL, float boundR);

private:
	Sprite* sprite;
	float speed;
	bool _right;
	bool _left;
};

class Bulleto
{
public:

	Bulleto(std::string SpritePath, cocos2d::Vec2 LaunchingPos)
	{
		sprite.first = Sprite::create(SpritePath);
		sprite.second = Sprite::create(SpritePath);
		launchingPos.first = LaunchingPos;
		launchingPos.second = { LaunchingPos.x - 36, LaunchingPos.y };
	}

	cocos2d::Vec2 bulletSpeed;
	std::pair < cocos2d::Sprite*, cocos2d::Sprite*> sprite;
	std::pair < cocos2d::Vec2, cocos2d::Vec2> launchingPos;
};
#pragma once
#include "cocos2d.h"

#define MAXBULLETS 5
using namespace cocos2d;

class Bullet;

class Assignment2 : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void update(float dt);

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(Assignment2)

private:

	cocos2d::Vec2 _origin;
	cocos2d::Size _screenPos;

	cocos2d::Sprite* _character;
	cocos2d::Vec2 _speed;
	Bullet* _bullets[MAXBULLETS];
	bool _isKeyAPressed;
	bool _isKeyDPressed;
	bool _isKeyWPressed;
	bool _isKeySPressed;

	cocos2d::EventListenerKeyboard* _keyboardListener;

	void CreateCharacter(std::string filePath, cocos2d::Vec2 pos, cocos2d::Vec2 speed);
	void KeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void KeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void CharacterMovement(float dt);
	void InstantiateBulletPool();
	void EnableKeyboard();
};



class Bullet 
{
public:

	Bullet(std::string SpritePath, cocos2d::Vec2 LaunchingPos)
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
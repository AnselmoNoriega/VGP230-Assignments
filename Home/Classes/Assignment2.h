#pragma once
#include "cocos2d.h"

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

	cocos2d::EventListenerKeyboard* _keyboardListener;

	void CreateCharacter(std::string filePath, cocos2d::Vec2 pos, cocos2d::Vec2 speed);
	void KeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void EnableKeyboard();
};


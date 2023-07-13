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

	cocos2d::Sprite* character;
	cocos2d::Vec2 origin;
	cocos2d::Vec2 speed;
};


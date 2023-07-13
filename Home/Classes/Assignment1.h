#pragma once
#include "cocos2d.h"

class Assignment1 : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void update(float dt);

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(Assignment1)

private:

	cocos2d::Sprite* character;
	cocos2d::Vec2 origin;
	cocos2d::Vec2 speed;
	cocos2d::Vec2 frameSize;
	cocos2d::Vec2 frameEndSize;
};

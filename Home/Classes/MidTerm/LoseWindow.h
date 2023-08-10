#pragma once
#include "cocos2d.h"
#include "MidTerm.h"

class LoseWindow : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void update(float dt);

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(LoseWindow)

private:

	void InitKeyboardListener();

	cocos2d::Sprite* background;
	cocos2d::Vec2 _origin;
	cocos2d::Size _screenPos;
};


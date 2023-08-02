#pragma once
#include "cocos2d.h"
#include <math.h>

class MidTerm : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void update(float dt);

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

private:

	EventListenerKeyboard keyboardListener;
	void InitKeyboardListener();

	
};

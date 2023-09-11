#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class VictoryScene : public Scene
{
public:
	static Scene* createScene();

	virtual bool init();
	virtual void update(float dt);

	// a selector callback
	void menuCloseCallback(Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(VictoryScene)

private:
	Sprite* background;
};


#pragma once
#include "cocos2d.h"
#define MAX 3

class MainF : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void update(float dt);

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(MainF)

private:
	cocos2d::Vec2 origin;
	cocos2d::Vec2 screenSize;

	void SetPhysicsMap(cocos2d::TMXTiledMap* map);
};

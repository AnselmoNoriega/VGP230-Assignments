#pragma once
#include "cocos2d.h"
#include "mainF.h"

using namespace cocos2d;

class MainMenu : public cocos2d::Scene
{
public:
	static Scene* createScene();

	virtual bool init();
	virtual void update(float dt);

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(MainMenu)

private:

	void InitBackground();
	void UpdateBackground(float dt);
	void Load();

	Vec2 midlePos;
	Vec2 screenSize;
	Vec2 endScreen;

	Menu* menuController;
	Vector<Sprite*> background[6];
};
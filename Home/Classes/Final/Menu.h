#pragma once
#include "cocos2d.h"
#include "mainF.h"
#include "AudioEngine.h"
#pragma warning(push)
#pragma warning(disable: 4996)
#include "json/document.h"
#include "json/prettywriter.h"
#include "json/stringbuffer.h"
#pragma warning(pop)

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

	bool musicOn = true;
};
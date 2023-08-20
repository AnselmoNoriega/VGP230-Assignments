#include "LW.h"
#include "MazeScene2.h"

USING_NS_CC;

cocos2d::Scene* LW::createScene()
{
	return LW::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool LW::init()
{
	_origin = Director::getInstance()->getVisibleOrigin();
	_screenPos = Director::getInstance()->getVisibleSize();
	auto centerOfScreen = Vec2(_screenPos.width / 2, _screenPos.height / 2);

	background = Sprite::create("deathScreen.png");
	this->addChild(background, 0);
	background->setPosition(centerOfScreen);

	this->scheduleUpdate();
	InitKeyboardListener();

	return true;
}

void LW::update(float dt)
{

}

void LW::menuCloseCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->end();
}

void LW::InitKeyboardListener()
{
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_SPACE:
			Director::getInstance()->replaceScene(MazeScene2::create());
			break;
		default: break;
		};
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

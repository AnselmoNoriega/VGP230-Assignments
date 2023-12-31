#include "LoseWindow.h"

USING_NS_CC;

cocos2d::Scene* LoseWindow::createScene()
{
	return LoseWindow::create();;
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool LoseWindow::init()
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

void LoseWindow::update(float dt)
{

}

void LoseWindow::menuCloseCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->end();
}

void LoseWindow::InitKeyboardListener()
{
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_ENTER:
			Director::getInstance()->replaceScene(MidTerm::create());
			break;
		default: break;
		};
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

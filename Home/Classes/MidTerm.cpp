#include "MidTerm.h"

USING_NS_CC;

Scene* MidTerm::createScene()
{
	return MidTerm::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MidTerm::init()
{

	this->scheduleUpdate();

	InitKeyboardListener();

	return true;
}

void MidTerm::update(float dt)
{

}


void MidTerm::menuCloseCallback(Ref* pSender)
{
	_eventDispatcher->removeEventListener(keyboardListener);
	Director::getInstance()->end();
}

void MidTerm::InitKeyboardListener()
{
	keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_W:
			break;
		case EventKeyboard::KeyCode::KEY_A:
			break;
		case EventKeyboard::KeyCode::KEY_S:
			break;
		case EventKeyboard::KeyCode::KEY_D:
			break;
		};
	};

	keyboardListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_W:
			break;
		case EventKeyboard::KeyCode::KEY_A:
			break;
		case EventKeyboard::KeyCode::KEY_S:
			break;
		case EventKeyboard::KeyCode::KEY_D:
			break;
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

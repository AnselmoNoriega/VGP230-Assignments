#include "VictoryScreen.h"
#include "Menu.h"
#include "AudioEngine.h"

Scene* VictoryScene::createScene()
{
	return VictoryScene::create();
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool VictoryScene::init()
{
	background = Sprite::create("Background/WinScreen.png");
	background->setScale(0.4f);
	background->setPosition(_defaultCamera->getPosition());
	addChild(background);

	AudioEngine::stopAll();
	AudioEngine::play2d("sounds/snd_music_victorytheme.ogg", true, 1.0f, nullptr);

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
		{
			switch (keyCode)
			{
			case EventKeyboard::KeyCode::KEY_M:
				AudioEngine::stopAll();
				Director::getInstance()->replaceScene(MainMenu::createScene());
				break;
			};
		};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	scheduleUpdate();
	return true;
}

void VictoryScene::update(float dt)
{

}

void VictoryScene::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}
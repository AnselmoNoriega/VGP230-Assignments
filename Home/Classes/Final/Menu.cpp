#include "Menu.h"

std::string mapName;

Scene* MainMenu::createScene()
{
	return MainMenu::create();
}

bool MainMenu::init()
{
	endScreen = Director::getInstance()->getVisibleOrigin() + Director::getInstance()->getVisibleSize();
	screenSize = Director::getInstance()->getVisibleSize();

	midlePos = Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2);

	InitBackground();

	mapName = mapNames[levelsUnlucked];

	auto newGame = MenuItemLabel::create(cocos2d::Label::createWithTTF("New Game", "fonts/Marker Felt.ttf", 24), [this](cocos2d::Ref* sender)
		{
			Director::getInstance()->replaceScene(MainF::createScene());
		});

	auto loadButton = MenuItemLabel::create(cocos2d::Label::createWithTTF("Load", "fonts/Marker Felt.ttf", 24), [this](cocos2d::Ref* sender)
		{
			//load();
		});

	auto quitButton = MenuItemLabel::create(cocos2d::Label::createWithTTF("Quit", "fonts/Marker Felt.ttf", 24), [this](cocos2d::Ref* sender)
		{
			Director::getInstance()->end();
		});

	menuController = Menu::create(newGame, loadButton, quitButton, nullptr);
	menuController->alignItemsVerticallyWithPadding(20);

	addChild(menuController, 0);

	scheduleUpdate();

	return true;
}

void MainMenu::update(float dt)
{
	UpdateBackground(dt);
}

void MainMenu::menuCloseCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->end();
}

void MainMenu::InitBackground()
{
	std::string names[6] = { "trees.png", "mountains.png", "far-mountains.png", "near-clouds.png", "far-clouds.png", "sky.png" };
	bool isFlipped = false;

	for (int i = 5; i >= 0; --i)
	{
		for (int j = -1; j < 2; ++j)
		{
			background[i].pushBack(Sprite::create("Background/" + names[i]));
			background[i].back()->setPosition(midlePos + Vec2(background[i].back()->getContentSize().width * j * (screenSize.x/ background[i].back()->getContentSize().width), 0.0f));
			addChild(background[i].back());
			background[i].back()->setScale(screenSize.x / background[i].back()->getContentSize().width);
			background[i].back()->setFlippedX(isFlipped);
			isFlipped = !isFlipped;
		}
	}
}

void MainMenu::UpdateBackground(float dt)
{
	int speed = 10;
	float halfBackground;

	for (int i = 5; i >= 0; --i)
	{
		halfBackground = (background[i].back()->getContentSize().width * (screenSize.x / background[i].back()->getContentSize().width)) / 2;

		for (int j = 0; j < 3; ++j)
		{
			if (endScreen.x < background[i].at(j)->getPositionX() - halfBackground)
			{
				background[i].at(j)->setPositionX(midlePos.x - halfBackground * 2);
			}
			background[i].at(j)->setPositionX(background[i].at(j)->getPositionX() + speed * dt);
		}
		speed *= 2;
	}
}
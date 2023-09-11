#include "Menu.h"
#include "AudioEngine.h"
#pragma warning(push)
#pragma warning(disable: 4996)
#include "json/document.h"
#include "json/prettywriter.h"
#include "json/stringbuffer.h"
#pragma warning(pop)

std::string mapName;
std::string mapNames[3] = { "TestLevel.tmx", "FirstLevel.tmx", "LastLevel.tmx" };
int levelsUnlucked = 0;

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

	auto newGame = MenuItemLabel::create(cocos2d::Label::createWithTTF("New Game", "fonts/Marker Felt.ttf", 24), [this](cocos2d::Ref* sender)
		{
			mapName = mapNames[levelsUnlucked];
			Director::getInstance()->replaceScene(MainF::createScene());
		});

	auto loadButton = MenuItemLabel::create(cocos2d::Label::createWithTTF("Load", "fonts/Marker Felt.ttf", 24), [this](cocos2d::Ref* sender)
		{
			Load();
			mapName = mapNames[levelsUnlucked];
			Director::getInstance()->replaceScene(MainF::createScene());
		});

	auto quitButton = MenuItemLabel::create(cocos2d::Label::createWithTTF("Quit", "fonts/Marker Felt.ttf", 24), [this](cocos2d::Ref* sender)
		{
			Director::getInstance()->end();
		});

	menuController = Menu::create(newGame, loadButton, quitButton, nullptr);
	menuController->alignItemsVerticallyWithPadding(20);

	addChild(menuController, 0);

	AudioEngine::play2d("sounds/ockaie_temple.ogg", true, 1.0f, nullptr);

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

void MainMenu::Load()
{
	std::string jsonString = cocos2d::FileUtils::getInstance()->getStringFromFile("Save.json");

	if (jsonString != "")
	{
		rapidjson::Document document;
		document.Parse(jsonString.c_str());

		if (document.HasParseError())
		{
			std::stringstream ss;
			ss << "Error parsing JSON: ErrorCode " << document.GetParseError();
			std::string s = ss.str();
			return;
		}

		if (document.HasMember("levelsUnlucked") && document["levelsUnlucked"].IsInt())
		{
			levelsUnlucked = document["levelsUnlucked"].GetFloat();
		}
	}
}

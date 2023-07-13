#include "Assignment1.h"

USING_NS_CC;

Scene* Assignment1::createScene()
{
	return Assignment1::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Assignment1::init()
{
	origin = Director::getInstance()->getVisibleOrigin();

	character = Sprite::create("dvdLogo.png");
	character->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2));
	this->addChild(character, 0);
	speed = { -300, 300 };
	this->scheduleUpdate();

	return true;
}

void Assignment1::update(float dt)
{
	frameSize.x = Director::getInstance()->getVisibleOrigin().x + (character->getContentSize().width / 2);
	frameSize.y = Director::getInstance()->getVisibleOrigin().y + (character->getContentSize().height / 3);
	frameEndSize.x = Director::getInstance()->getVisibleSize().width - (character->getContentSize().width / 2);
	frameEndSize.y = Director::getInstance()->getVisibleSize().height + (character->getContentSize().height / 3);

	if (frameSize.x >= character->getPositionX() || frameEndSize.x <= character->getPositionX())
	{
		speed.x *= (-1);
	}

	if (frameSize.y >= character->getPositionY() || frameEndSize.y <= character->getPositionY())
	{
		speed.y *= (-1);
	}

	character->setPosition(character->getPositionX() + speed.x * dt, character->getPositionY() + speed.y * dt);

}


void Assignment1::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

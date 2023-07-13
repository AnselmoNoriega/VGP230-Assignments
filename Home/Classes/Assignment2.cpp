#include "Assignment2.h"

USING_NS_CC;

Scene* Assignment2::createScene()
{
	return Assignment2::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool Assignment2::init()
{
	origin = Director::getInstance()->getVisibleOrigin();

	character = Sprite::create("dvdLogo.png");
	character->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2));
	this->addChild(character, 0);

	this->scheduleUpdate();

	return true;
}

void Assignment2::update(float dt)
{

}


void Assignment2::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}
#include "mainF.h"

USING_NS_CC;

Scene* MainF::createScene()
{
	return MainF::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainF::init()
{
	origin = Director::getInstance()->getVisibleOrigin();
	screenSize = Director::getInstance()->getVisibleSize();

	Vec2 midlePos = Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2);

	this->scheduleUpdate();

	return true;
}

void MainF::update(float dt)
{

}


void MainF::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

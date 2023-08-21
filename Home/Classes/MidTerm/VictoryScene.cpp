#include "VictoryScene.h"

USING_NS_CC;

cocos2d::Scene* VictoryScene::createScene()
{
	return VictoryScene::create();;
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool VictoryScene::init()
{
	_origin = Director::getInstance()->getVisibleOrigin();
	_screenPos = Director::getInstance()->getVisibleSize();
	auto centerOfScreen = Vec2(_screenPos.width / 2, _screenPos.height / 2);

	background = Sprite::create("victory.jpg");
	this->addChild(background, 0);
	background->setPosition(centerOfScreen);

	this->scheduleUpdate();

	return true;
}

void VictoryScene::update(float dt)
{

}

void VictoryScene::menuCloseCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->end();
}

/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	origin = Director::getInstance()->getVisibleOrigin();

	character = Sprite::create("dvdLogo.png");
	character->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height/2));
	this->addChild(character, 0);
	speed = { -300, 300 };
	this->scheduleUpdate();

	return true;
}

void HelloWorld::update(float dt)
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


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

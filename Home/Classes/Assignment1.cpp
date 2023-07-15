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
	ScreenSize = Director::getInstance()->getVisibleSize();

	Vec2 midlePos = Vec2(Director::getInstance()->getVisibleSize().width / 2, 
		                 Director::getInstance()->getVisibleSize().height / 2);

	CreateCharacters(0, "dvdLogo.png", midlePos, { -300, 300 });
	CreateCharacters(1, "carrot.png", midlePos, { 200, 250 });
	CreateCharacters(2, "carrier.png", midlePos, { -100, 50 });

	this->scheduleUpdate();

	return true;
}

void Assignment1::update(float dt)
{
	CharacterMovemnt(0, dt);
	CharacterMovemnt(1, dt);
	CharacterMovemnt(2, dt);
}


void Assignment1::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

void Assignment1::CreateCharacters(int characterIndex, std::string fileName, Vec2 pos, Vec2 speed)
{
	character[characterIndex] = Sprite::create(fileName);
	character[characterIndex]->setPosition(pos);
	this->addChild(character[characterIndex], 0);
	mSpeed[characterIndex] = speed;
}

void Assignment1::CharacterMovemnt(int characterIndex, float deltaTime)
{
	frameSize[characterIndex].x = origin.x + (character[characterIndex]->getContentSize().width / 2);
	frameSize[characterIndex].y = origin.y + (character[characterIndex]->getContentSize().height / 2);
	frameEndSize[characterIndex].x = ScreenSize.width - (character[characterIndex]->getContentSize().width / 2);
	frameEndSize[characterIndex].y = ScreenSize.height - (character[characterIndex]->getContentSize().height / 2);

	if (FrameSizeX(characterIndex))
	{
		mSpeed[characterIndex].x *= (-1);
	}

	if (FrameSizeY(characterIndex))
	{
		mSpeed[characterIndex].y *= (-1);
	}

	character[characterIndex]->setPosition(character[characterIndex]->getPositionX() + mSpeed[characterIndex].x * deltaTime, 
		                                   character[characterIndex]->getPositionY() + mSpeed[characterIndex].y * deltaTime);
}

bool Assignment1::FrameSizeX(int characterIndex)
{
	return frameSize[characterIndex].x >= character[characterIndex]->getPositionX() || 
		   frameEndSize[characterIndex].x <= character[characterIndex]->getPositionX();
}

bool Assignment1::FrameSizeY(int characterIndex)
{
	return frameSize[characterIndex].y >= character[characterIndex]->getPositionY() || 
		   frameEndSize[characterIndex].y <= character[characterIndex]->getPositionY();
}

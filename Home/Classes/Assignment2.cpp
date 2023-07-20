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
	//----------------------Game init-----------------------

	_origin = Director::getInstance()->getVisibleOrigin();
	_screenPos = Director::getInstance()->getVisibleSize();

	EnableKeyboard();

	//----------------------Objects init-----------------------

	auto centerOfScreen = Vec2(_screenPos.width / 2, _screenPos.height / 2);
	CreateCharacter("fighter.png", centerOfScreen, Vec2(200, 200));

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

void Assignment2::CreateCharacter(std::string filePath, cocos2d::Vec2 pos, cocos2d::Vec2 speed)
{
	_character = Sprite::create(filePath);
	_character->setPosition(pos);
	_speed = speed;
	this->addChild(_character, 0);

	InstantiateBulletPool();
}

void Assignment2::InstantiateBulletPool()
{
	for (size_t i = 0; i < MAXBULLETS; i++)
	{
		_bullets[i] = new Bullet("bullet1.png", Vec2(18, 20));

		_bullets[i]->sprite.first->setPosition(_bullets[i]->launchingPos.first);
		_bullets[i]->sprite.second->setPosition(_bullets[i]->launchingPos.second);


		this->addChild(_bullets[i], 0);
	}
}

void Assignment2::KeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_A:
		_character->setPosition(_character->getPositionX() + (_speed.x * (-1)), _character->getPositionY());
		_character->setRotation(-90);
		break;

	case EventKeyboard::KeyCode::KEY_D:
		_character->setPosition(_character->getPositionX() + _speed.x, _character->getPositionY());
		_character->setRotation(90);
		break;

	case EventKeyboard::KeyCode::KEY_W:
		_character->setPosition(_character->getPositionX(), _character->getPositionY() + _speed.y);
		_character->setRotation(0);
		break;

	case EventKeyboard::KeyCode::KEY_S:
		_character->setPosition(_character->getPositionX(), _character->getPositionY() + (_speed.y * (-1)));
		_character->setRotation(180);
		break;

	case EventKeyboard::KeyCode::KEY_SPACE:
		_character->setPosition(_character->getPositionX(), _character->getPositionY() + (_speed.y * (-1)));
		_character->setRotation(180);
		break;
	}
}


void Assignment2::EnableKeyboard()
{
	_keyboardListener = EventListenerKeyboard::create();
	_keyboardListener->onKeyPressed = CC_CALLBACK_2(Assignment2::KeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboardListener, this);
}


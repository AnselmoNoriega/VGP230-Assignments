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
	CharacterMovement(dt);
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
		_bullets[i] = new Bullet("bullet1.png", { _character->getPosition().x + 18, _character->getPosition().y + 20 });

		_bullets[i]->sprite.first->setPosition(_bullets[i]->launchingPos.first);
		_bullets[i]->sprite.second->setPosition(_bullets[i]->launchingPos.second);

		this->addChild(_bullets[i]->sprite.first, 0);
		this->addChild(_bullets[i]->sprite.second, 0);

		//disables the objects
	}
}

void Assignment2::CharacterMovement(float dt)
{
	if (_isKeyAPressed)
	{
		_character->setRotation(_character->getRotation() - 20 * dt);
	}
	if (_isKeyDPressed)
	{
		_character->setRotation(_character->getRotation() + 20 * dt);
	}
	if (_isKeyWPressed && !_isKeySPressed)
	{
		
	}
}

void Assignment2::KeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_A:
		_isKeyAPressed = true;
		break;

	case EventKeyboard::KeyCode::KEY_D:
		_isKeyDPressed = true;
		break;

	case EventKeyboard::KeyCode::KEY_W:
		_isKeyWPressed = true;
		break;

	case EventKeyboard::KeyCode::KEY_S:
		_isKeySPressed = true;
		break;

	case EventKeyboard::KeyCode::KEY_SPACE:
		//enables the shot
		break;
	}
}

void Assignment2::KeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_A:
		_isKeyAPressed = false;
		break;

	case EventKeyboard::KeyCode::KEY_D:
		_isKeyDPressed = false;
		break;

	case EventKeyboard::KeyCode::KEY_W:
		_isKeyWPressed = false;
		break;

	case EventKeyboard::KeyCode::KEY_S:
		_isKeySPressed = false;
		break;

	case EventKeyboard::KeyCode::KEY_SPACE:
		//enables the shot
		break;
	}
}

void Assignment2::EnableKeyboard()
{
	_keyboardListener = EventListenerKeyboard::create();
	_keyboardListener->onKeyPressed = CC_CALLBACK_2(Assignment2::KeyPressed, this);
	_keyboardListener->onKeyReleased = CC_CALLBACK_2(Assignment2::KeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboardListener, this);
}


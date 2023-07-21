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
	BulletMovment();
}


void Assignment2::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

//----------------------Creation Methods---------------------------------------------------------------------

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
		_bullets[i] = new Bullet("bullet1.png", { 18, 22 });

		this->addChild(_bullets[i]->sprite.first);
		this->addChild(_bullets[i]->sprite.second);

		_bullets[i]->sprite.first->setVisible(false);
		_bullets[i]->sprite.second->setVisible(false);
	}
}

//----------------------Objects Movements---------------------------------------------------------------------

void Assignment2::CharacterMovement(float dt)
{
	if (_isKeyAPressed)
	{
		_character->setRotation(_character->getRotation() - 40 * dt);
	}
	if (_isKeyDPressed)
	{
		_character->setRotation(_character->getRotation() + 40 * dt);
	}
	if (_isKeyWPressed && !_isKeySPressed)
	{
		auto speedX = cos(_character->getRotation() * (M_PI / 180)) * 5;
		auto speedY = sin(_character->getRotation() * (M_PI / 180)) * 5;
		_character->setPosition(_character->getPosition().x + speedY, _character->getPosition().y + speedX);
	}
}

void Assignment2::BulletMovment()
{
	if (_bullets[0]->sprite.first->isVisible())
	{
		//--------------------------FirstBullet init---------------------------------------
		auto cosValues = _bullets[0]->launchingPos.first * cos(-_character->getRotation() * (M_PI / 180));
		auto sinValues = _bullets[0]->launchingPos.first * sin(-_character->getRotation() * (M_PI / 180));

		auto initPos1 = _character->getPositionX() + cosValues.x - sinValues.y;
		auto initPos2 = _character->getPositionY() + sinValues.x + cosValues.y;

		_bullets[0]->sprite.first->setPosition(initPos1, initPos2);
		_bullets[0]->sprite.first->setRotation(_character->getRotation());

		//--------------------------SecondBullet init---------------------------------------
		cosValues = _bullets[0]->launchingPos.second * cos(-_character->getRotation() * (M_PI / 180));
		sinValues = _bullets[0]->launchingPos.second * sin(-_character->getRotation() * (M_PI / 180));

		initPos1 = _character->getPositionX() + cosValues.x - sinValues.y;
		initPos2 = _character->getPositionY() + sinValues.x + cosValues.y;

		_bullets[0]->sprite.second->setPosition(initPos1, initPos2);
		_bullets[0]->sprite.second->setRotation(_character->getRotation());
	}
}

//----------------------Input Events---------------------------------------------------------------------

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
		_bullets[0]->sprite.first->setVisible(true);
		_bullets[0]->sprite.second->setVisible(true);
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
	}
}

void Assignment2::EnableKeyboard()
{
	_keyboardListener = EventListenerKeyboard::create();
	_keyboardListener->onKeyPressed = CC_CALLBACK_2(Assignment2::KeyPressed, this);
	_keyboardListener->onKeyReleased = CC_CALLBACK_2(Assignment2::KeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_keyboardListener, this);
}


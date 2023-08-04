#include "MidTerm.h"

USING_NS_CC;

Scene* MidTerm::createScene()
{
	return MidTerm::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MidTerm::init()
{
	//----------------------------------Map Info--------------------------------------------
	_origin = Director::getInstance()->getVisibleOrigin();
	_screenPos = Director::getInstance()->getVisibleSize();
	auto centerOfScreen = Vec2(_screenPos.width / 2, _screenPos.height / 2);
	auto playerPosition = Vec2(_screenPos.width / 2, _screenPos.height / 10);
	auto enemyPosition = Vec2(_screenPos.width / 2, _screenPos.height / 1.2);

	//----------------------------------Game Objects Init----------------------------------
	player = new Player(playerPosition);
	this->addChild(player->GetSprite(), 0);
	
	enemy = new Enemy(enemyPosition);
	this->addChild(enemy->GetSprite(), 0);

	InitBullets();

	//---------------------------------For Update----------------------------------------
	this->scheduleUpdate();
	InitKeyboardListener();

	return true;
}

void MidTerm::update(float dt)
{
	player->Move(dt, _origin.x, _screenPos.width);
	player->BulletMovement(dt, _screenPos.height);

	enemy->Move(dt, _origin.x, _screenPos.width);
}


void MidTerm::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

void MidTerm::InitKeyboardListener()
{
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_W:
			break;
		case EventKeyboard::KeyCode::KEY_A:
			player->SetLeft(true);
			break;
		case EventKeyboard::KeyCode::KEY_S:
			break;
		case EventKeyboard::KeyCode::KEY_D:
			player->SetRight(true);
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			player->lasers[GetIndex()].LaunchBullet(player->GetPos());
			break;
		};
	};

	keyboardListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_W:
			break;
		case EventKeyboard::KeyCode::KEY_A:
			player->SetLeft(false);
			break;
		case EventKeyboard::KeyCode::KEY_S:
			break;
		case EventKeyboard::KeyCode::KEY_D:
			player->SetRight(false);
			break;
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void MidTerm::InitBullets()
{
	for (size_t i = 0; i < MAXBULLETS; i++)
	{
		this->addChild(player->lasers[i].GetSprite().first, 0);
		this->addChild(player->lasers[i].GetSprite().second, 0);
	}

	bulletIndex = 0;
}

int MidTerm::GetIndex()
{
	if (bulletIndex >= MAXBULLETS)
	{
		bulletIndex = 0;
	}

	return bulletIndex++;
}

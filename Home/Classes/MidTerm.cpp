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

	//----------------------------------Game Objects Init----------------------------------
	player = new Player(playerPosition);
	this->addChild(player->GetSprite(), 0);
	this->addChild(player->debug, 0);

	InitEnemies(centerOfScreen);

	InitBullets();

	enemySize = enemy[0]->GetSprite()->getContentSize() / 2;
	enemyBulletS = enemy[0]->lasers[0].GetSprite()->getContentSize() / 2;
	playerSize = player->GetSprite()->getContentSize() / 2;
	playerBulletS = player->lasers[0].GetSprite().first->getContentSize() / 2;

	isColliderOn = false;

	//---------------------------------For Update----------------------------------------
	this->scheduleUpdate();
	InitKeyboardListener();

	return true;
}

void MidTerm::update(float dt)
{
	Movements(dt);
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
		case EventKeyboard::KeyCode::KEY_A:
			player->SetLeft(true);
			break;
		case EventKeyboard::KeyCode::KEY_D:
			player->SetRight(true);
			break;
		case EventKeyboard::KeyCode::KEY_C:
			isColliderOn = !isColliderOn;
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			player->lasers[GetIndex()].LaunchBullet(player->GetPos());
			break;
		default: break;
		};
	};

	keyboardListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_A:
			player->SetLeft(false);
			break;
		case EventKeyboard::KeyCode::KEY_D:
			player->SetRight(false);
			break;
		default: break;
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

void MidTerm::InitEnemies(Vec2 pos)
{
	Vec2 initPos = pos;
	Vec2 speed = { 700, 100 };

	for (int i = 0; i < ENEMIESCOUNT; ++i)
	{
		initPos.x = random(_origin.x, _screenPos.width);
		initPos.y += 10;
		speed = { random(400.0f, 1000.0f), random(0.0f, 200.0f) };

		enemy[i] = new Enemy(initPos, speed);

		this->addChild(enemy[i]->GetSprite(), 0);
		this->addChild(enemy[i]->debug, 1);

		for (int j = 0; j < BULLETCOUNT; ++j)
		{
			this->addChild(enemy[i]->lasers[j].GetSprite(), 0);
		}
	}
}

void MidTerm::Movements(float dt)
{
	player->Move(dt, _origin.x, _screenPos.width);
	player->BulletMovement(dt, _screenPos.height);

	player->debug->clear();
	if (isColliderOn)
	{
		player->debug->setLineWidth(5);
		player->DrawCollisionBox();
	}

	for (int i = 0; i < ENEMIESCOUNT; ++i)
	{
		enemy[i]->Move(dt, _origin.x, _screenPos.width);
		enemy[i]->debug->clear();

		if (isColliderOn)
		{
			enemy[i]->debug->setLineWidth(5);
			enemy[i]->DrawCollisionBox();
		}
	}
}

void MidTerm::EnemyCollision(Vec2 playerBullet, Vec2 enemyPos, int enemyNum, int bulletNum)
{
	for (int i = 0; i < MAXBULLETS; i++)
	{
		if (player->lasers[i].GetSprite().first->isVisible() && InsideBounds(GetEnemyBounds(enemyPos), GetPlayerBulletBounds(playerBullet)))
		{
			player->lasers[bulletNum].GetSprite().first->setVisible(false);
			player->lasers[bulletNum].GetSprite().second->setVisible(false);

			delete enemy[enemyNum];
			enemy[enemyNum] = nullptr;
		}
	}
}

std::vector<Vec2, Vec2> MidTerm::GetEnemyBounds(Vec2 pos)
{
	return { pos - enemySize, pos + enemySize };
}

std::vector<Vec2, Vec2> MidTerm::GetPlayerBounds(Vec2 pos)
{
	return { pos - playerSize, pos + playerSize };
}

std::vector<Vec2, Vec2> MidTerm::GetEnemyBulletBounds(Vec2 pos)
{
	return { pos - enemyBulletS, pos + enemyBulletS };
}

std::vector<Vec2, Vec2> MidTerm::GetPlayerBulletBounds(Vec2 pos)
{
	return { pos - playerBulletS, pos + playerBulletS };
}

bool MidTerm::InsideBounds(std::vector<Vec2, Vec2> obj1, std::vector<Vec2, Vec2> obj2)
{
	return false;
}



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
	this->addChild(player->GetSprite(), 10);
	this->addChild(player->debug, 10);
	this->addChild(player->health, 10);

	InitEnemies(centerOfScreen);

	InitBullets();

	enemySize = enemy[0]->GetSprite()->getContentSize() / 2;
	enemyBulletS = enemy[0]->lasers[0].GetSprite()->getContentSize() / 2;
	playerSize = player->GetSprite()->getContentSize() / 2;
	playerBulletS = player->lasers[0].GetSprite().first->getContentSize() / 2;

	isColliderOn = false;
	countEnemies = ENEMIESCOUNT;

	InitBackground(centerOfScreen);

	//---------------------------------For Update----------------------------------------
	this->scheduleUpdate();
	InitKeyboardListener();

	return true;
}

void MidTerm::update(float dt)
{
	Movements(dt);
	BackgroundMovement(dt);

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
		this->addChild(player->lasers[i].GetSprite().first, 10);
		this->addChild(player->lasers[i].GetSprite().second, 10);
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
	enemy.resize(ENEMIESCOUNT, nullptr);

	for (int i = 0; i < ENEMIESCOUNT; ++i)
	{
		initPos.x = random(_origin.x, _screenPos.width);
		initPos.y += 10;
		speed = { random(400.0f, 1000.0f), random(0.0f, 200.0f) };

		enemy[i] = new Enemy(initPos, speed);

		this->addChild(enemy[i]->GetSprite(), 10);
		this->addChild(enemy[i]->debug, 10);

		for (int j = 0; j < BULLETCOUNT; ++j)
		{
			this->addChild(enemy[i]->lasers[j].GetSprite(), 10);
		}
	}
}

void MidTerm::Movements(float dt)
{
	player->Move(dt, _origin.x, _screenPos.width);
	player->BulletMovement(dt, _screenPos.height);
	PlayerCollision();

	player->debug->clear();
	if (isColliderOn)
	{
		player->debug->setLineWidth(5);
		player->DrawCollisionBox();
	}

	for (int i = 0; i < countEnemies; ++i)
	{
		enemy[i]->Move(dt, _origin.x, _screenPos.width);
		enemy[i]->debug->clear();

		if (isColliderOn)
		{
			enemy[i]->debug->setLineWidth(5);
			enemy[i]->DrawCollisionBox();
		}

		EnemyCollision(enemy[i]->GetSprite()->getPosition(), i);
	}
}

void MidTerm::EnemyCollision(Vec2 enemyPos, int enemyNum)
{
	for (int i = 0; i < MAXBULLETS; ++i)
	{
		if (player->lasers[i].GetSprite().first->isVisible() && InsideBounds(GetBounds(enemyPos, enemySize), GetPlayerBulletBounds(player->lasers[i].GetSprite().second->getPosition(), player->lasers[i].GetSprite().first->getPosition())))
		{
			player->lasers[i].GetSprite().first->setVisible(false);
			player->lasers[i].GetSprite().second->setVisible(false);

			enemy[enemyNum]->GetSprite()->setVisible(false);
			enemy[enemyNum]->lasers[0].GetSprite()->setVisible(false);
			enemy[enemyNum]->lasers[1].GetSprite()->setVisible(false);
			enemy[enemyNum]->debug->clear();
			delete enemy[enemyNum];
			enemy[enemyNum] = nullptr;
			enemy.erase(enemy.begin() + enemyNum);
			--countEnemies;
		}
	}
}

void MidTerm::PlayerCollision()
{
	for (int i = 0; i < countEnemies; ++i)
	{
		for (int j = 0; j < BULLETCOUNT; ++j)
		{
			if (enemy[i]->lasers[j].GetSprite()->isVisible() && InsideBounds(GetBounds(enemy[i]->lasers[j].GetSprite()->getPosition(), enemyBulletS), GetBounds(player->GetSprite()->getPosition(), playerSize)))
			{
				player->PlayerGotHit();
				enemy[i]->lasers[j].GetSprite()->setVisible(false);
				if (player->health->getScaleX() <= 0)
				{
					Director::getInstance()->replaceScene(MidTerm::create());
				}
			}
		}
	}
}

Vec4 MidTerm::GetBounds(Vec2 pos, Vec2 offset)
{
	return { pos.x - offset.x,
			 pos.y - offset.y,
			 pos.x + offset.x,
			 pos.y + offset.y };
}

Vec4 MidTerm::GetPlayerBulletBounds(Vec2 pos1, Vec2 pos2)
{
	return { pos1.x - playerBulletS.x,
			 pos1.y - playerBulletS.y,
			 pos2.x + playerBulletS.x,
			 pos2.y + playerBulletS.y };
}

bool MidTerm::InsideBounds(Vec4 obj1, Vec4 obj2)
{
	return (obj1.x <= obj2.z && obj1.z >= obj2.x) && (obj1.y <= obj2.w && obj1.w >= obj2.y);
}

void MidTerm::InitBackground(Vec2 pos)
{
	for (int i = 0; i < PARALAXCOUNT; ++i)
	{
		background[i] = Sprite::create("parallax-space-backgound.png");
		planet[i] = Sprite::create("parallax-space-big-planet.png");
		planetsCorners[i] = Sprite::create("parallax-space-far-planets.png");
		dust[i] = Sprite::create("parallax-space-stars.png");

		background[i]->setScale(10);
		planet[i]->setScale(10);
		planetsCorners[i]->setScale(10);
		dust[i]->setScale(10);

		background[i]->setPosition(pos.x - background[i]->getContentSize().width * 20, pos.y);
		planet[i]->setPosition(pos.x - planet[i]->getContentSize().width * 20, pos.y);
		planetsCorners[i]->setPosition(pos.x - planetsCorners[i]->getContentSize().width * 20, pos.y);
		dust[i]->setPosition(pos.x - dust[i]->getContentSize().width * 20, pos.y);

		this->addChild(background[i], 0);
		this->addChild(dust[i], 1);
		this->addChild(planet[i], 2);
		this->addChild(planetsCorners[i], 3);

		pos.x += background[0]->getContentSize().width * 10;
	}
}

void MidTerm::BackgroundMovement(float dt)
{
	for (int i = 0; i < PARALAXCOUNT; ++i)
	{
		background[i]->setPosition(background[i]->getPositionX() + 100 * dt, background[i]->getPositionY());
		planet[i]->setPosition(planet[i]->getPositionX() + 50 * dt, planet[i]->getPositionY());
		planetsCorners[i]->setPosition(planetsCorners[i]->getPositionX() + 20 * dt, planetsCorners[i]->getPositionY());
		dust[i]->setPosition(dust[i]->getPositionX() + 100 * dt, dust[i]->getPositionY());

		if (background[i]->getPositionX() - background[i]->getContentSize().width * 5 >= _screenPos.width)
		{
			background[i]->setPositionX(_origin.x - background[i]->getContentSize().width * 5);
		}
		if (planet[i]->getPositionX() - planet[i]->getContentSize().width * 5 >= _screenPos.width)
		{
			planet[i]->setPositionX(_origin.x - planet[i]->getContentSize().width * 5);
		}
		if (planetsCorners[i]->getPositionX() - planetsCorners[i]->getContentSize().width * 5 >= _screenPos.width)
		{
			planetsCorners[i]->setPositionX(_origin.x - planetsCorners[i]->getContentSize().width * 5);
		}
		if (dust[i]->getPositionX() - dust[i]->getContentSize().width * 5 >= _screenPos.width)
		{
			dust[i]->setPositionX(_origin.x - dust[i]->getContentSize().width * 5);
		}
	}
}



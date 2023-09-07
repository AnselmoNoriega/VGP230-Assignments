#include "mainF.h"

USING_NS_CC;

Scene* MainF::createScene()
{
	auto ret = new (std::nothrow) MainF();
	if (ret && ret->initWithPhysics() && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	else
	{
		CC_SAFE_DELETE(ret);
		return nullptr;
	}

	return ret;
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool MainF::init()
{
	origin = Director::getInstance()->getVisibleOrigin();
	screenSize = Director::getInstance()->getVisibleSize();

	Vec2 midlePos = Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2);

	InitWorld(midlePos);

	auto level = TMXTiledMap::create("tmx/FirstLevel.tmx");
	addChild(level, -1);
	level->getLayer("EnemySpawn")->setVisible(false);
	level->getLayer("Exit")->setVisible(false);

	SetPhysicsMap(level, "Collision");

	scheduleUpdate();

	return true;
}

void MainF::update(float dt)
{
	player.Update(dt);

	for (auto& enemy : enemies)
	{
		enemy->Update(dt);
	}

	if (player.Get()->isVisible())
	{
		_defaultCamera->setPosition(player.Get()->getPosition());
	}
}


void MainF::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

void MainF::SetPhysicsMap(TMXTiledMap* map, std::string tileName)
{
	auto physicsWorld = getPhysicsWorld();
	physicsWorld->setGravity(cocos2d::Vec2(0, -980));
	physicsWorld->setDebugDrawMask(NULL);

	auto collisionFloor = map->getLayer(tileName);

	for (int row = 0; row < map->getMapSize().height; ++row)
	{
		for (int col = 0; col < map->getMapSize().width; ++col)
		{
			auto tile = collisionFloor->getTileAt(cocos2d::Vec2(col, row));

			if (tile)
			{
				auto physicsBody = cocos2d::PhysicsBody::createBox(tile->getContentSize(), PHYSICSSHAPE_MATERIAL_DEFAULT);
				physicsBody->setDynamic(false);
				physicsBody->setCategoryBitmask(2);
				physicsBody->setCollisionBitmask(1);
				physicsBody->setContactTestBitmask(1);
				physicsBody->setName(tileName);
				tile->setPhysicsBody(physicsBody);
			}
		}
	}
}

void MainF::InitWorld(Vec2 midlePos)
{
	player.SetSpawn(midlePos);
	player.Init(getPhysicsWorld(), _eventDispatcher, this);

	enemies.push_back(std::make_unique<Enemy>(FLYING, midlePos, 2.0f));

	for (auto& enemy : enemies)
	{
		enemy->Init(_eventDispatcher, this);
	}
}

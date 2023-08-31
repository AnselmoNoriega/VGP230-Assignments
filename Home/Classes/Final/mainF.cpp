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

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MainF::init()
{
	origin = Director::getInstance()->getVisibleOrigin();
	screenSize = Director::getInstance()->getVisibleSize();

	Vec2 midlePos = Vec2(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2);

	auto level = TMXTiledMap::create("tmx/TestMap.tmx");
	this->addChild(level);
	SetPhysicsMap(level);

	this->scheduleUpdate();

	return true;
}

void MainF::update(float dt)
{

}


void MainF::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();
}

void MainF::SetPhysicsMap(TMXTiledMap* map)
{
	auto physicsWorld = getPhysicsWorld();
	physicsWorld->setGravity(cocos2d::Vec2(0, -980));

	physicsWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto collicionFloor = map->getLayer("Tile Layer");

	for (int row = 0; row < map->getMapSize().height; ++row)
	{
		for (int col = 0; col < map->getMapSize().width; ++col)
		{
			auto tile = collicionFloor->getTileAt(cocos2d::Vec2(col, row));

			if (tile)
			{
				auto physicsBody = cocos2d::PhysicsBody::createBox(tile->getContentSize(), PHYSICSSHAPE_MATERIAL_DEFAULT);
				physicsBody->setDynamic(false);
				physicsBody->setCategoryBitmask(2);
				physicsBody->setCollisionBitmask(1); 
				physicsBody->setContactTestBitmask(1);
				tile->setPhysicsBody(physicsBody);
			}
		}
	}

	/*auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = [=](PhysicsContact& contact) -> bool
	{
		auto a = contact.getShapeA()->getBody();
		auto b = contact.getShapeB()->getBody();

		auto other = marioPhysicsBody == a ? b : a;

		if (marioPhysicsBody->getPosition().y > other->getPosition().y && abs(contact.getContactData()->normal.y) > 0.9f)
		{
			contacts.push_back(other);
		}

		return true;
	};
	contactListener->onContactSeparate = [=](PhysicsContact& contact)
	{
		auto a = contact.getShapeA()->getBody();
		auto b = contact.getShapeB()->getBody();

		auto separate = marioPhysicsBody == a ? b : a;

		for (int i = 0; i < contacts.size(); ++i)
		{
			if (contacts[i] == separate)
			{
				contacts[i] = contacts[contacts.size() - 1];
				contacts.pop_back();
				break;
			}
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);*/
}

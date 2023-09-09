#include "Door.h"

void Door::Init(PhysicsWorld* pWorld, EventDispatcher* _eventDispatcher, Scene* scene)
{
	sprite = Sprite::create("Trap/tile000.png");

	scene->addChild(sprite, 1);

	ObjectPhysics(_eventDispatcher, scene);

	LevelComplete = false;
}

void Door::SetSpawn(Vec2 pos)
{
	sprite->setPosition({ pos.x, pos.y + sprite->getContentSize().height / 2 });
}

bool Door::LevelIsComplete()
{
	return LevelComplete;
}

void Door::LevelComplited()
{
	sprite->runAction(Repeat::create(Animate::create(Animation::createWithSpriteFrames(GetAnimation(6))), 1));
}

void Door::ObjectPhysics(EventDispatcher* _eventDispatcher, Scene* scene)
{
	physicsBody = cocos2d::PhysicsBody::createBox(sprite->getContentSize() / 1.1, PHYSICSSHAPE_MATERIAL_DEFAULT);
	physicsBody->setDynamic(false);
	physicsBody->setCategoryBitmask(1);
	physicsBody->setCollisionBitmask(2);
	physicsBody->setContactTestBitmask(1);
	physicsBody->setName("Exit");
	sprite->setPhysicsBody(physicsBody);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = [=](PhysicsContact& contact) -> bool
		{
			auto a = contact.getShapeA()->getBody();
			auto b = contact.getShapeB()->getBody();

			auto other = physicsBody == a ? b : a;
			auto mySelf = physicsBody != a ? b : a;

			if (other->getName() == "Player" && mySelf->getName() == "Exit")
			{
				LevelComplited();
				LevelComplete = true;
			}

			return true;
		};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, scene);
}

Vector<SpriteFrame*> Door::GetAnimation(int count)
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Trap/DoorMove.plist");
	auto spriteCache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> animFrames;
	char str[100];

	for (int i = 0; i <= count; i++)
	{
		snprintf(str, sizeof(str), "tile0%02d.png", i);
		animFrames.pushBack(spriteCache->getSpriteFrameByName(str));
	}
	SpriteFrameCache::getInstance()->removeSpriteFrames();

	return animFrames;
}

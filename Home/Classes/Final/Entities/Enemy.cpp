#include "Enemy.h"

Enemy::Enemy(Vec2 SpawnPoint): speed(100.0f)
{
	Animations(); 
	sprite = Sprite::create("Enemy/tile001.png");
	sprite->setScale(2);
	spawnPoint = SpawnPoint;
}

void Enemy::Init(EventDispatcher* _eventDispatcher, Scene* scene)
{
	scene->addChild(sprite, 0);

	sprite->runAction(RepeatForever::create(Animate::create(anim)));
	CharacterPhysics(_eventDispatcher, scene);
	physicsBody->setName("Enemy");
	sprite->setPosition(spawnPoint);
}

void Enemy::Update(float dt)
{
	/*if (abs(physicsBody->getVelocity().x) < 100 && physicsBody->getVelocity().x != 0)
	{
		speed *= -1;
	}*/

	physicsBody->setVelocity({speed, physicsBody->getVelocity().y});
}

//--------------------------------------------------------------------------------------------------

Sprite* Enemy::Get()
{
	return sprite;
}

void Enemy::MovePosition(Vec2 pos)
{
	sprite->setPosition(sprite->getPosition() + pos);
}

//----------------------------------------------------------------------------------------------------

void Enemy::CharacterPhysics(EventDispatcher* _eventDispatcher, Scene* scene)
{
	physicsBody = cocos2d::PhysicsBody::createBox(sprite->getContentSize() / 1.7, PHYSICSSHAPE_MATERIAL_DEFAULT);
	physicsBody->setPositionOffset({0, -10});
	physicsBody->setRotationEnable(false);
	physicsBody->setDynamic(true);
	physicsBody->setCategoryBitmask(1);
	physicsBody->setCollisionBitmask(2);
	physicsBody->setContactTestBitmask(1);//
	sprite->setPhysicsBody(physicsBody);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = [=](PhysicsContact& contact) -> bool
		{
			if (abs(contact.getContactData()->normal.x) < 0.1f)
			{
				//speed *= -1;
			}

			return true;
		};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, scene);
}

void Enemy::CharacterLogic(PhysicsWorld* pWorld, EventDispatcher* _eventDispatcher, Scene* scene)
{
}

//----------------------------------------------------------------------------------------------------

void Enemy::Animations()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Enemy/EnemyMove.plist");
	anim = (Animation::createWithSpriteFrames(GetAnimation(18), 0.2f));

	SpriteFrameCache::getInstance()->removeSpriteFrames();
}

Vector<SpriteFrame*> Enemy::GetAnimation(int count)
{
	auto spriteCache = SpriteFrameCache::getInstance();
	Vector<SpriteFrame*> animFrames;
	char str[100];

	for (int i = 1; i <= count; i++)
	{
		snprintf(str, sizeof(str), "tile0%02d.png", i);
		animFrames.pushBack(spriteCache->getSpriteFrameByName(str));
	}

	return animFrames;
}

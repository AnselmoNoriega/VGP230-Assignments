#include "Enemy.h"

Enemy::Enemy(EnemyType type, Vec2 SpawnPoint, float moveTime) : speed({ 100.0f, 0.0f }), isFlipped(false), movementTime(moveTime), timer(movementTime)
{
	myType = type;
	Animations();
	sprite = Sprite::create(enemyName[myType] + "/tile001.png");
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
	if (myType == OBSTACLE) { speed = Vec2::ZERO; }
}

void Enemy::Update(float dt)
{
	if (myType == GROUND) { speed.y = physicsBody->getVelocity().y; }
	physicsBody->setVelocity(speed);

	MoveTimer(dt);
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
	physicsBody = cocos2d::PhysicsBody::createBox(sprite->getContentSize(), PHYSICSSHAPE_MATERIAL_DEFAULT);
	physicsBody->setRotationEnable(false);
	physicsBody->setDynamic(true);
	physicsBody->setCategoryBitmask(1);
	physicsBody->setCollisionBitmask(2);
	physicsBody->setContactTestBitmask(1);//
	sprite->setPhysicsBody(physicsBody);
}

void Enemy::CharacterLogic(PhysicsWorld* pWorld, EventDispatcher* _eventDispatcher, Scene* scene)
{
}

void Enemy::MoveTimer(float dt)
{
	timer -= dt;

	if (timer <= 0)
	{
		timer = movementTime;
		speed *= -1;
		sprite->setFlippedX(isFlipped = !isFlipped);
	}
}

//----------------------------------------------------------------------------------------------------

void Enemy::Animations()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(enemyName[myType] + "/EnemyMove.plist");
	anim = (Animation::createWithSpriteFrames(GetAnimation(5 + (myType - 1) * (myType - 1) * 3), 0.2f));

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

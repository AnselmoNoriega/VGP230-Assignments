#include "Character.h"

Character::Character() : physicsBody(nullptr), speed(300.0f), jumpSpeed(400), up(false), left(false), right(false)
{
	Animations();
	sprite = Sprite::create("Idle/tile001.png");
	sprite->setScale(2);
}

void Character::Init(PhysicsWorld* pWorld, EventDispatcher* _eventDispatcher, Scene* scene)
{
	sprite->runAction(RepeatForever::create(Animate::create(anims.at(0))));
	CharacterPhysics(pWorld, _eventDispatcher, scene);
	CharacterController(pWorld, _eventDispatcher, scene);
}

void Character::Update(float dt)
{
	if (!right && !left)
	{
		ChangeAnim(IDLE, 0.2f);
	}

	if (right)
	{
		physicsBody->setVelocity({ speed,physicsBody->getVelocity().y});
		sprite->setFlippedX(false);
	}
	else if (left)
	{
		physicsBody->setVelocity({-speed,physicsBody->getVelocity().y });
		sprite->setFlippedX(true);
	}
	else
	{
		physicsBody->setVelocity({ 0.0f,physicsBody->getVelocity().y });
	}
	if (up)
	{
		physicsBody->applyImpulse({ 0, jumpSpeed });
		up = false;
	}
}

//----------------------------------------------------------------------------------------------------

Sprite* Character::Get()
{
	return sprite;
}

void Character::SetPosition(Vec2 pos)
{
	sprite->setPosition(pos);
}

//-----------------------------------------------------------------------------------------------------

void Character::CharacterPhysics(PhysicsWorld* pWorld, EventDispatcher* _eventDispatcher, Scene* scene)
{
	auto physicsWorld = pWorld;
	physicsWorld->setGravity(cocos2d::Vec2(0, -980));

	///TODO: make code below toggleable (aka can turn on and off debug draw) 
	physicsWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	physicsBody = cocos2d::PhysicsBody::createBox(sprite->getContentSize() / 1.1, PHYSICSSHAPE_MATERIAL_DEFAULT);
	physicsBody->setRotationEnable(false);
	physicsBody->setDynamic(true);
	physicsBody->setCategoryBitmask(1);
	physicsBody->setCollisionBitmask(2);
	physicsBody->setContactTestBitmask(2);
	sprite->setPhysicsBody(physicsBody);

	contactsD.reserve(5);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = [=](PhysicsContact& contact) -> bool
	{
		auto a = contact.getShapeA()->getBody();
		auto b = contact.getShapeB()->getBody();

		auto other = physicsBody == a ? b : a;

		if (physicsBody->getPosition().y > other->getPosition().y && abs(contact.getContactData()->normal.y) > 0.9f)
		{
			contactsD.push_back(other);
		}

		return true;
	};
	contactListener->onContactSeparate = [=](PhysicsContact& contact)
	{
		auto a = contact.getShapeA()->getBody();
		auto b = contact.getShapeB()->getBody();

		auto separate = physicsBody == a ? b : a;

		for (int i = 0; i < contactsD.size(); ++i)
		{
			if (contactsD[i] == separate)
			{
				contactsD[i] = contactsD[contactsD.size() - 1];
				contactsD.pop_back();
				break;
			}
		}
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, scene);
}

void Character::CharacterController(PhysicsWorld* pWorld, EventDispatcher* _eventDispatcher, Scene* scene)
{
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_D:
			right = true;
			ChangeAnim(RUNNING, 0.1f);
			break;
		case EventKeyboard::KeyCode::KEY_A:
			left = true;
			ChangeAnim(RUNNING, 0.1f);
			break;
		case EventKeyboard::KeyCode::KEY_W:
			up = contactsD.size() > 0;
			break;
		case EventKeyboard::KeyCode::KEY_SHIFT:
			speed = 500.0f;
			break;
		case EventKeyboard::KeyCode::KEY_C:
			DebugDraw(pWorld);
			break;
		};
	};
	keyboardListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_D:
			right = false;
			break;
		case EventKeyboard::KeyCode::KEY_A:
			left = false;
			break;
		case EventKeyboard::KeyCode::KEY_SHIFT:
			speed = 300.0f;
		};
	};


	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, scene);
}

//-----------------------------------------------------------------------------------------------------

void Character::Animations()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Idle/KnightIdle.plist");
	anims.pushBack(Animation::createWithSpriteFrames(GetAnimation(10), 0.2f));

	SpriteFrameCache::getInstance()->removeSpriteFrames();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Run/KnightRun.plist");
	anims.pushBack(Animation::createWithSpriteFrames(GetAnimation(10), 0.1f));
}

void Character::ChangeAnim(PlayerState state, float speed)
{
	if (state != playerState)
	{
		playerState = state;
		sprite->stopAllActions();
		sprite->runAction(RepeatForever::create(Animate::create(anims.at((int)state))));
	}
}

Vector<SpriteFrame*> Character::GetAnimation(int count)
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

void Character::DebugDraw(PhysicsWorld* pWorld)
{
	if (pWorld->getDebugDrawMask() == PhysicsWorld::DEBUGDRAW_ALL)
	{
		pWorld->setDebugDrawMask(NULL);
	}
	else
	{
		pWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	}
}

#include "Character.h"

Character::Character()
{
	sprite = Sprite::create("_Idle.png");
	sprite->setScale(2);
}

void Character::Init(PhysicsWorld* pWorld, EventDispatcher* _eventDispatcher, Scene* scene)
{
	CharacterPhysics(pWorld, _eventDispatcher, scene);
}

Sprite* Character::Get()
{
	return sprite;
}

void Character::SetPosition(Vec2 pos)
{
	sprite->setPosition(pos);
}

void Character::CharacterPhysics(PhysicsWorld* pWorld, EventDispatcher* _eventDispatcher, Scene* scene)
{
	auto physicsWorld = pWorld;
	physicsWorld->setGravity(cocos2d::Vec2(0, -980));

	///TODO: make code below toggleable (aka can turn on and off debug draw) 
	physicsWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	physicsBody = cocos2d::PhysicsBody::createBox(sprite->getContentSize(), PHYSICSSHAPE_MATERIAL_DEFAULT);
	physicsBody->setRotationEnable(false);
	physicsBody->setDynamic(true);
	physicsBody->setCategoryBitmask(1);
	physicsBody->setCollisionBitmask(2);
	physicsBody->setContactTestBitmask(2);
	sprite->setPhysicsBody(physicsBody);

	contacts.reserve(5);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = [=](PhysicsContact& contact) -> bool
	{
		auto a = contact.getShapeA()->getBody();
		auto b = contact.getShapeB()->getBody();

		auto other = physicsBody == a ? b : a;

		if (physicsBody->getPosition().y > other->getPosition().y && abs(contact.getContactData()->normal.y) > 0.9f)
		{
			contacts.push_back(other);
		}

		return true;
	};
	contactListener->onContactSeparate = [=](PhysicsContact& contact)
	{
		auto a = contact.getShapeA()->getBody();
		auto b = contact.getShapeB()->getBody();

		auto separate = physicsBody == a ? b : a;

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

	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, scene);
}

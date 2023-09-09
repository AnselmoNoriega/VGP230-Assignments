#include "Character.h"

Character::Character() : physicsBody(nullptr), speed(0.0f), jumpSpeed(650), up(false), left(false), right(false), boost(1.0f), isTimeRunning(false), spawnTime(1.0f), timer(1.0f), hasDoubleJump(false), canMove(true)
{
	Animations();
	sprite = Sprite::create("Idle/tile001.png");
	sprite->setScale(2);
	deathExplotion = ParticleSystemQuad::create("DeathParticle.plist");
	deathExplotion->setScale(0.25f);
}

void Character::Init(PhysicsWorld* pWorld, EventDispatcher* _eventDispatcher, Scene* scene)
{
	scene->addChild(sprite, 2);

	sprite->runAction(RepeatForever::create(Animate::create(anims.at(0))));
	CharacterPhysics(_eventDispatcher, scene);
	CharacterController(pWorld, _eventDispatcher, scene);
	sprite->setPosition(spawnPoint);

	scene->addChild(deathExplotion, 1);
	deathExplotion->setVisible(false);

	physicsWorld = pWorld;
}

void Character::Update(float dt)
{
	CharacterMovement();
	auto t = sprite->getPositionY();

	if (sprite->getPositionY() < spawnPoint.y - 1000)
	{
		isWithEnemy = true;
	}

	if (isWithEnemy && canMove)
	{
		isTimeRunning = true;
		deathExplotion->setPosition(sprite->getPosition());
		deathExplotion->setVisible(true);
		deathExplotion->start();

		sprite->setPosition(spawnPoint);
		sprite->setVisible(false);

		physicsBody->setVelocity({ 0.0f, 0.0f });
		physicsWorld->setSpeed(0.0f);
		isWithEnemy = false;
	}

	SpawnTimer(dt);
}

//----------------------------------------------------------------------------------------------------

Sprite* Character::Get()
{
	return sprite;
}

void Character::MovePosition(Vec2 pos)
{
	sprite->setPosition(sprite->getPosition() + pos);
}

void Character::SetSpawn(Vec2 pos)
{
	spawnPoint = pos;
}

void Character::PlayerWin()
{
	canMove = false;
}

//-----------------------------------------------------------------------------------------------------

void Character::CharacterPhysics(EventDispatcher* _eventDispatcher, Scene* scene)
{

	physicsBody = cocos2d::PhysicsBody::createBox(sprite->getContentSize() / 1.1, PHYSICSSHAPE_MATERIAL_DEFAULT);
	physicsBody->setRotationEnable(false);
	physicsBody->setDynamic(true);
	physicsBody->setCategoryBitmask(1);
	physicsBody->setCollisionBitmask(3);
	physicsBody->setContactTestBitmask(3);
	physicsBody->setName("Player");
	sprite->setPhysicsBody(physicsBody);

	contactsD.reserve(5);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = [=](PhysicsContact& contact) -> bool
		{
			auto a = contact.getShapeA()->getBody();
			auto b = contact.getShapeB()->getBody();

			auto other = physicsBody == a ? b : a;
			auto mySelf = physicsBody != a ? b : a;

			if (physicsBody->getPosition().y > other->getPosition().y && abs(contact.getContactData()->normal.y) > 0.9f)
			{
				contactsD.push_back(other);
			}
			if (other->getName() == "Enemy" && mySelf->getName() == "Player")
			{
				isWithEnemy = true;
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
				speed += 300.0f;
				break;
			case EventKeyboard::KeyCode::KEY_A:
				left = true;
				speed -= 300.0f;
				break;
			case EventKeyboard::KeyCode::KEY_W:
				up = (contactsD.size() > 0 || hasDoubleJump);
				break;
			case EventKeyboard::KeyCode::KEY_SHIFT:
				boost = 1.5f;
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
				speed -= 300.0f;
				break;
			case EventKeyboard::KeyCode::KEY_A:
				left = false;
				speed += 300.0f;
				break;
			case EventKeyboard::KeyCode::KEY_W:
				up = false;
				break;
			case EventKeyboard::KeyCode::KEY_SHIFT:
				boost = 1.0f;
			};
		};


	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, scene);
}

void Character::CharacterMovement()
{
	if (!canMove)
	{
		physicsBody->setVelocity({ 0.0f, 0.0f });
		return;
	}

	physicsBody->setVelocity({ speed * boost,physicsBody->getVelocity().y });

	if (contactsD.size() == 0)
	{
		ChangeAnim(JUMPING, 0.2f);
	}

	if ((right || left) && contactsD.size() > 0)
	{
		sprite->setFlippedX(speed < 0);
		ChangeAnim(RUNNING, 0.1f);
	}
	else if (contactsD.size() > 0)
	{
		ChangeAnim(IDLE, 0.2f);
	}

	if (up)
	{
		physicsBody->setVelocity({ physicsBody->getVelocity().x, 0.0f });
		physicsBody->applyImpulse({ 0, jumpSpeed });

		if (contactsD.size() > 0)
		{
			up = false;
			hasDoubleJump = true;
		}
		else
		{
			up = false;
			hasDoubleJump = false;
		}
	}
}

//-----------------------------------------------------------------------------------------------------

void Character::Animations()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Idle/KnightIdle.plist");
	anims.pushBack(Animation::createWithSpriteFrames(GetAnimation(10), 0.2f));

	SpriteFrameCache::getInstance()->removeSpriteFrames();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Run/KnightRun.plist");
	anims.pushBack(Animation::createWithSpriteFrames(GetAnimation(10), 0.1f));

	SpriteFrameCache::getInstance()->removeSpriteFrames();

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Jump/KnightJump.plist");
	anims.pushBack(Animation::createWithSpriteFrames(GetAnimation(3), 0.1f));

	SpriteFrameCache::getInstance()->removeSpriteFrames();
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

void Character::SpawnTimer(float dt)
{
	if (isTimeRunning)
	{
		timer -= dt;

		if (timer <= 0.0f)
		{
			sprite->setVisible(true);
			timer = spawnTime;
			physicsWorld->setSpeed(1.0f);
			isTimeRunning = false;
		}
	}
}

#include "Week7_HelloMario.h"


Scene* HelloMario::createScene()
{
	auto ret = new (std::nothrow) HelloMario();
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

bool HelloMario::init()
{
	if (!cocos2d::Scene::init())
	{
		return false;
	}

	auto visibleSize = _director->getVisibleSize();
	auto origin = _director->getVisibleOrigin();

	/// TODO Design your own level(s)
	auto level = TMXTiledMap::create("tmx/MarioSampleLevel.tmx");

	this->addChild(level);

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("mario.plist");
	auto walkingFrames = getAnimation("mario_walk_%02d", 3);
	auto idleFrames = getAnimation("mario_idle_%02d", 2);
	auto fallingFrames = getAnimation("mario_fall_%02d", 1);
	auto jumpingFrames = getAnimation("mario_jump_%02d", 1);

	anims[0] = Animation::createWithSpriteFrames(idleFrames, 1.0f);
	anims[1] = Animation::createWithSpriteFrames(walkingFrames, 1.0f);
	anims[2] = Animation::createWithSpriteFrames(jumpingFrames, 1.0f);
	anims[3] = Animation::createWithSpriteFrames(fallingFrames, 1.0f);

	mario = Sprite::createWithSpriteFrame(idleFrames.front());
	addChild(mario);
	mario->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	mario->setScale(2);

	mario->runAction(RepeatForever::create(Animate::create(anims[0])));

	controller = KeyboardControllerComponent::create(KeyboardControllerComponent::WASD);
	mario->addComponent(controller);
	controller->initInput();

	InitPhysics(level);

	scheduleUpdate();

	return true;
}

void HelloMario::InitPhysics(TMXTiledMap* level)
{
	auto physicsWorld = getPhysicsWorld();
	physicsWorld->setGravity(cocos2d::Vec2(0, -980));

	///TODO: make code below toggleable (aka can turn on and off debug draw) 
	physicsWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	marioPhysicsBody = cocos2d::PhysicsBody::createBox(mario->getContentSize(), PHYSICSSHAPE_MATERIAL_DEFAULT);
	///TODO: Disallow mario's rotation to be effected by physics
	marioPhysicsBody->setRotationEnable(false);
	///TODO: Set mario to be dynamic (physics is applied to it)
	marioPhysicsBody->setDynamic(true);
	///TODO: Set mario physics body's category bitmask
	marioPhysicsBody->setCategoryBitmask(1);
	///TODO: Set mario physics body's collision bitmask
	marioPhysicsBody->setCollisionBitmask(2);
	///TODO: Set mario physics body's contact test bitmask
	marioPhysicsBody->setContactTestBitmask(2);
	mario->setPhysicsBody(marioPhysicsBody);

	contacts.reserve(5);

	auto collisionLayer = level->getLayer("Collision");
	for (int row = 0; row < level->getMapSize().height; ++row)
	{
		for (int col = 0; col < level->getMapSize().width; ++col)
		{
			auto tile = collisionLayer->getTileAt(cocos2d::Vec2(col, row));
			if (tile)
			{
				auto physicsBody = cocos2d::PhysicsBody::createBox(tile->getContentSize(), PHYSICSSHAPE_MATERIAL_DEFAULT);
				physicsBody->setDynamic(false);
				///TODO: set tile category bitmask 
				physicsBody->setCategoryBitmask(2);
				///TODO: set tile collision bitmask 
				physicsBody->setCollisionBitmask(1);
				///TODO: set tile contact test bitmask 
				physicsBody->setContactTestBitmask(1);
				tile->setPhysicsBody(physicsBody);
			}
		}
	}

	auto contactListener = EventListenerPhysicsContact::create();
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
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void HelloMario::ChangeAnim(AnimationState anim)
{
	if (anim != animationState)
	{
		animationState = anim;
		mario->stopAllActions();
		mario->runAction(RepeatForever::create(Animate::create(anims[(int)anim])));
	}
}

void HelloMario::update(float dt)
{
	auto contact = contacts.size() > 0;

	if (contact) /// mario is on the ground
	{
		movingSpeed = 0;

		if (controller->IsLeftPressed())
		{
			//ChangeAnim(AnimationState::Walking);
			movingSpeed -= 200;
		}
		if (controller->IsRightPressed())
		{
			//ChangeAnim(AnimationState::Walking);
			movingSpeed += 200;
		}

		if (controller->IsDownPressed())
		{
			/// TODO (optional):
			/// Make mario crouch
		}

		if (controller->IsUpPressed())
		{
			//ChangeAnim(AnimationState::Jumping);
			marioPhysicsBody->applyImpulse({ 0, 400 });
		}

		if (!controller->IsLeftPressed() && !controller->IsRightPressed() && !controller->IsDownPressed() && !controller->IsUpPressed())
		{
			/// TODO:
			/// switch to idle animation
		}
	}
	else
	{
		if (controller->IsLeftPressed())
		{
			/// TODO:
			/// Move mario left with some velocity
			/// Set Position, and Flip X scale to negative
		}
		else if (controller->IsRightPressed())
		{
			/// TODO:
			/// Move mario right with some velocity
			/// Set Position, and Flip X scale to positive
		}

		if (animationState != Falling && mario->getPhysicsBody()->getVelocity().y < 0)
		{
			/// change animation to falling animation
		}
	}

	
	mario->setPosition(mario->getPosition().x + movingSpeed * dt, mario->getPosition().y);

	/// TODO:
	/// Set camera to follow mario
}
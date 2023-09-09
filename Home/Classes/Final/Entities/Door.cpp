#include "Door.h"
#include "Final/Menu.h"
#pragma warning(push)
#pragma warning(disable: 4996)
#include "json/document.h"
#include "json/prettywriter.h"
#include "json/stringbuffer.h"
#pragma warning(pop)

extern int levelsUnlucked;
extern std::string mapNames[3];
extern std::string mapName;

Door::Door() : LevelComplete(false), timer(2.0f)
{
	sprite = Sprite::create("Trap/tile000.png");
}

void Door::Init(PhysicsWorld* pWorld, EventDispatcher* _eventDispatcher, Scene* scene)
{
	scene->addChild(sprite, 1);

	ObjectPhysics(_eventDispatcher, scene);
}

void Door::Update(float dt)
{
	timer -= dt;
	if (timer <= 0.0f)
	{
		if (levelsUnlucked == 2)
		{
			return;
		}
		mapName = mapNames[++levelsUnlucked];
		Save();
		Director::getInstance()->replaceScene(MainF::createScene());
	}
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

void Door::Save()
{
	rapidjson::Document document;
	document.SetObject();

	document.AddMember("levelsUnlucked", levelsUnlucked, document.GetAllocator());

	rapidjson::StringBuffer buffer;
	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);

	std::string jsonStr = buffer.GetString();
	auto fullPath = cocos2d::FileUtils::getInstance()->fullPathForFilename("Save.json");
	cocos2d::FileUtils::getInstance()->writeStringToFile(jsonStr, fullPath);
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

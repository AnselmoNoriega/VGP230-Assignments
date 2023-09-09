#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Door
{
public:
	void Init(PhysicsWorld* pWorld, EventDispatcher* _eventDispatcher, Scene* scene);
	void SetSpawn(Vec2 pos);
	bool LevelIsComplete();

private:
	void ObjectPhysics(EventDispatcher* _eventDispatcher, Scene* scene);
	static Vector<SpriteFrame*> GetAnimation(int count);

	void LevelComplited();

	bool LevelComplete;

	Sprite* sprite;
	SpriteFrame* anim;

	PhysicsBody* physicsBody;
};

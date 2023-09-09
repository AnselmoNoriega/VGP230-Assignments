#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Door
{
public:
	Door();

	void Init(PhysicsWorld* pWorld, EventDispatcher* _eventDispatcher, Scene* scene);
	void Update(float dt);
	void SetSpawn(Vec2 pos);
	bool LevelIsComplete();

private:
	void ObjectPhysics(EventDispatcher* _eventDispatcher, Scene* scene);
	static Vector<SpriteFrame*> GetAnimation(int count);

	void LevelComplited();
	void Save();

	bool LevelComplete;

	Sprite* sprite;
	SpriteFrame* anim;

	float timer;

	PhysicsBody* physicsBody;
};

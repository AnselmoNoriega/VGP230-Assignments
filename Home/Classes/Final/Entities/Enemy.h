#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Enemy
{
public:

	Enemy(Vec2 SpawnPoint);

	void Init(EventDispatcher* _eventDispatcher, Scene* scene);
	void Update(float dt);

	Sprite* Get(); 
	void MovePosition(Vec2 pos);

private:

	void CharacterPhysics(EventDispatcher* _eventDispatcher, Scene* scene);
	void CharacterLogic(PhysicsWorld* pWorld, EventDispatcher* _eventDispatcher, Scene* scene);

	void Animations(); 
	static Vector<SpriteFrame*> GetAnimation(int count);

	Sprite* sprite;
	bool isFlipped;
	float speed;
	Vec2 spawnPoint;

	PhysicsBody* physicsBody;
	Animation* anim;
};


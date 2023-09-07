#pragma once
#include "cocos2d.h"

using namespace cocos2d;

enum EnemyType
{
	NONE,
	FLYING,
	GROUND,
	OBSTACLE
};

class Enemy
{
public:

	Enemy(EnemyType type, Vec2 SpawnPoint, float moveTime);

	void Init(EventDispatcher* _eventDispatcher, Scene* scene);
	void Update(float dt);

	Sprite* Get(); 
	void MovePosition(Vec2 pos);

private:

	void CharacterPhysics(EventDispatcher* _eventDispatcher, Scene* scene);
	void CharacterLogic(PhysicsWorld* pWorld, EventDispatcher* _eventDispatcher, Scene* scene);
	void MoveTimer(float dt);

	void Animations(); 
	static Vector<SpriteFrame*> GetAnimation(int count);

	Sprite* sprite;
	bool isFlipped;
	Vec2 speed;
	Vec2 spawnPoint;
	EnemyType myType;

	PhysicsBody* physicsBody;
	Animation* anim;

	const float movementTime;
	float timer;
};


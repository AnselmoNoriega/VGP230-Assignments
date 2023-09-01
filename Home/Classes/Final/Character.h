#include "cocos2d.h"

using namespace cocos2d;

class Character
{
public:

	Character();

	void Init(PhysicsWorld* pWorld, EventDispatcher* _eventDispatcher, Scene* scene);
	void Update(float dt);

	Sprite* Get();
	void SetPosition(Vec2 pos);

private:
	void CharacterPhysics(PhysicsWorld* pWorld, EventDispatcher* _eventDispatcher, Scene* scene);

	Sprite* sprite;

	PhysicsBody* physicsBody;
	std::vector<PhysicsBody*> contacts;
};

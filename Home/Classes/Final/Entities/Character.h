#include "cocos2d.h"

using namespace cocos2d;

class Character
{
public:

	Character();

	void Init(PhysicsWorld* pWorld, EventDispatcher* _eventDispatcher, Scene* scene);
	void Update(float dt);

	Sprite* Get();
	void MovePosition(Vec2 pos);
	void SetSpawn(Vec2 pos);

private:
	enum PlayerState
	{
		IDLE,
		RUNNING
	} playerState = IDLE;

	void CharacterPhysics(EventDispatcher* _eventDispatcher, Scene* scene);
	void CharacterController(PhysicsWorld* pWorld, EventDispatcher* _eventDispatcher, Scene* scene);

	void Animations();
	void ChangeAnim(PlayerState state, float speed);
	static Vector<SpriteFrame*> GetAnimation(int count);

	void DebugDraw(PhysicsWorld* pWorld);

	Sprite* sprite;
	float speed;
	float jumpSpeed;
	Vec2 spawnPoint;

	bool up;
	bool right;
	bool left;

	PhysicsBody* physicsBody;
	std::vector<PhysicsBody*> contactsD;
	Vector<Animation*> anims;
};
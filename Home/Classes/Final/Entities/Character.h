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
		RUNNING,
		JUMPING
	} playerState = IDLE;

	void CharacterPhysics(EventDispatcher* _eventDispatcher, Scene* scene);
	void CharacterController(PhysicsWorld* pWorld, EventDispatcher* _eventDispatcher, Scene* scene);

	void CharacterMovement();

	void Animations();
	void ChangeAnim(PlayerState state, float speed);
	static Vector<SpriteFrame*> GetAnimation(int count);

	void DebugDraw(PhysicsWorld* pWorld);
	void SpawnTimer(float dt);

	Sprite* sprite;
	float speed;
	float boost;
	const float jumpSpeed;

	Vec2 spawnPoint;
	bool isWithEnemy;

	bool up;
	bool right;
	bool left;
	bool hasDoubleJump;

	float timer;
	const float spawnTime;
	bool isTimeRunning;

	PhysicsWorld* physicsWorld;

	std::vector<PhysicsBody*> contactsD;
	PhysicsBody* physicsBody;
	Vector<Animation*> anims;

	ParticleSystemQuad* deathExplotion;
};

#pragma once
#include "cocos2d.h"
#include "Player.h"
#include "Enemy.h"
#include <math.h>

#define ENEMIESCOUNT 20

class MidTerm : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void update(float dt);

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(MidTerm)

private:

	cocos2d::Vec2 _origin;
	cocos2d::Size _screenPos;

	void InitKeyboardListener();

	//-------------------PlayerHelpers-------------------------
	Player* player;
	std::vector<Enemy*> enemy;
	int bulletIndex;
	int countEnemies;

	void InitBullets();
	int GetIndex();
	void InitEnemies(Vec2 pos);
	void Movements(float dt);
	void EnemyCollision(Vec2 enemyPos, int enemyNum);
	Vec4 GetEnemyBounds(Vec2 pos);
	Vec4 GetPlayerBounds(Vec2 pos);
	Vec4 GetEnemyBulletBounds(Vec2 pos);
	Vec4 GetPlayerBulletBounds(Vec2 pos1, Vec2 pos2);

	bool InsideBounds(Vec4 obj1, Vec4 obj2);

	bool isColliderOn;
	Vec2 enemySize;
	Vec2 enemyBulletS;
	Vec2 playerSize;
	Vec2 playerBulletS;
	
};

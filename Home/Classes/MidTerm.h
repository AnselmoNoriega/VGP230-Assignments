#pragma once
#include "cocos2d.h"
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"
#include <math.h>

#define ENEMIESCOUNT 30
#define PARALAXCOUNT 3

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
	Boss* boss;

	void InitBullets();
	int GetIndex();
	void InitEnemies(Vec2 pos);
	void InitBoss(Vec2 pos);
	void Movements(float dt);
	void BossCollision(Vec2 bossPos);
	void EnemyCollision(Vec2 enemyPos, int enemyNum);
	void PlayerCollision();
	Vec4 GetBounds(Vec2 pos, Vec2 offset);
	Vec4 GetPlayerBulletBounds(Vec2 pos1, Vec2 pos2);

	bool InsideBounds(Vec4 obj1, Vec4 obj2);

	bool isColliderOn;
	Vec2 enemySize;
	Vec2 enemyBulletS;
	Vec2 playerSize;
	Vec2 playerBulletS;
	Vec2 bossSize;

	//--------------background------------------------
	Sprite* background[PARALAXCOUNT];
	Sprite* planet[PARALAXCOUNT];
	Sprite* planetsCorners[PARALAXCOUNT];
	Sprite* dust[PARALAXCOUNT];

	void InitBackground(Vec2 pos);
	void BackgroundMovement(float dt);
	
};

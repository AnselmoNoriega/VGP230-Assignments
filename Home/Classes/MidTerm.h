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
	Enemy* enemy[ENEMIESCOUNT];
	int bulletIndex;

	void InitBullets();
	int GetIndex();
	void InitEnemies(Vec2 pos);
	void Movements(float dt);

	bool isColliderOn;
	
};

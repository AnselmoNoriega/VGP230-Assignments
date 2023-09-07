#pragma once

#include "cocos2d.h"
#include "Entities/Character.h"
#include "Entities/Enemy.h"

extern std::string mapName;

class MainF : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void update(float dt);

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(MainF)

private:
	cocos2d::Vec2 origin;
	cocos2d::Vec2 screenSize;

	void SetPhysicsMap(cocos2d::TMXTiledMap* map, std::string tileName);
	void SetEntityPos(cocos2d::TMXTiledMap* map, std::string tileName);
	cocos2d::Vec2 LookForTile(cocos2d::TMXTiledMap* map, std::string tileName);

	void InitWorld(cocos2d::TMXTiledMap* map);

	//---------------------------Entities--------------------------------
	Character player;
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::vector<Vec2> enemyPositions;
};

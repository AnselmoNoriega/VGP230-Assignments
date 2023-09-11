#pragma once

#include "cocos2d.h"
#include "Menu.h"
#include "Entities/Character.h"
#include "Entities/Enemy.h"
#include "Entities/Door.h"

extern std::string mapName;

class MainF : public Scene
{
public:
	static Scene* createScene();

	virtual bool init();
	virtual void update(float dt);

	// a selector callback
	void menuCloseCallback(Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(MainF)

private:
	Vec2 origin;
	Vec2 screenSize;
	Sprite* background[3];

	bool musicOn = true;

	void SetPhysicsMap(TMXTiledMap* map, std::string tileName);
	void SetEntityPos(TMXTiledMap* map, std::string tileName);
	Vec2 LookForTile(TMXTiledMap* map, std::string tileName);

	void InitWorld(cocos2d::TMXTiledMap* map);

	//---------------------------Entities--------------------------------
	Character player;
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::vector<Vec2> enemyPositions;

	Door exitDoor;
};

#pragma once

#include "cocos2d.h"
#include "MazeEnemy.h"

USING_NS_CC;

class MazeScene : public Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	virtual void update(float dt);

	void initialize(Sprite* spr, TMXLayer* layer, std::pair<int, int>& position, bool draw = true);

	const std::pair<int, int> FlipY(std::pair<int, int> const position);

	void setPosition(Sprite* spr, std::pair<int, int> playerPosition, std::pair<int, int>& oldPosition, bool draw = true);

	bool canSetPosition(std::pair<int, int> playerPosition);

	void changeActiveSprite(Sprite* newActive);

	CREATE_FUNC(MazeScene)

	const Size* mapSize;
	const Size* tileSize;

	std::pair<int, int> playerPosition;
	std::vector < std::pair<int, int>> endPosition;

	TMXLayer* path;
	DrawNode* drawNode;
	std::vector<MazeEnemy> enemies;

	bool draw = false;

private:
	enum GameState
	{
		Start,
		Running,
		FoundCheese,
		Victory
	} gameState = Start;

	TMXLayer* collision;
	TMXLayer* playerStartLayer;

	std::vector<std::vector<bool>> cheeseVisited;

	Sprite* active;
	Sprite* ratDown;
	Sprite* ratLeft;
	Sprite* ratUp;
	Sprite* ratRight;
	std::vector < Sprite*> cheese;

	TMXTiledMap* map;
	void CheesePath();

	bool isPlayerMoving;
	int playerLives;

	float cheeseAnimationTimer = 0;

	void ResetInput();
	void PlayerHit();

	bool down = false;
	bool left = false;
	bool up = false;
	bool right = false;
};
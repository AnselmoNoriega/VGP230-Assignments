#pragma once
#include "cocos2d.h" 

class MazeEnemy
{
public:
	MazeEnemy(cocos2d::Sprite* sprite, cocos2d::Color3B color, const cocos2d::Size* worldSize);

	cocos2d::Sprite* GetSprite();
	bool Move(cocos2d::TMXLayer* path, std::pair<int, int> const& target);

	std::pair<int, int> enemyPos;
	std::pair<int, int> newPos;
	std::pair<int, int> spawnPoint;

	std::vector<std::pair<int, int>> bfsPath;

private:
	struct TileNode
	{
		TileNode(std::pair<int, int> tPos, std::shared_ptr<TileNode> father): pos(tPos), parent(father)
		{}
		std::pair<int, int> pos;
		std::shared_ptr<TileNode> parent;
	};

	const std::pair<int, int> FlipY(std::pair<int, int> const position);
	bool canSetPosition(std::pair<int, int> playerPosition, cocos2d::TMXLayer* path);

	bool BFSPath(std::pair<int, int> current, std::pair<int, int>const& target, cocos2d::TMXLayer* path);

	cocos2d::Sprite* mSprite;
	std::vector<std::vector<bool>> bfsVisited;
	const cocos2d::Size* mapSize;
	std::deque<std::shared_ptr<TileNode>> nodes;

};
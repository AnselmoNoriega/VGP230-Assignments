#pragma once
#include "cocos2d.h" 

class MazeEnemy
{
public:
	MazeEnemy(cocos2d::Sprite* sprite, cocos2d::Color3B color, const cocos2d::Size* worldSize);

	cocos2d::Sprite* GetSprite();
	void Move();

	std::pair<int, int> enemyPos;

private:
	const std::pair<int, int> FlipY(std::pair<int, int> const position);
	bool canSetPosition(std::pair<int, int> playerPosition, TMXLayer* path);

	int DFSPath(std::pair<int, int> current, std::pair<int, int>const& target, int depth, TMXLayer* path);

	cocos2d::Sprite* mSprite;
	std::vector<std::vector<bool>> dfsVisited;
	std::vector<std::pair<int, int>> dfsPath;
	const cocos2d::Size* mapSize;
};
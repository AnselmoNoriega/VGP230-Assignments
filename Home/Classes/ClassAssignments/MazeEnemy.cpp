#include "MazeEnemy.h"
#include "MazeScene.h"

MazeEnemy::MazeEnemy(cocos2d::Sprite* sprite, cocos2d::Color3B color, const cocos2d::Size* worldSize)
	:mSprite(sprite), mapSize(worldSize)
{
	mSprite->setColor(color);
}

cocos2d::Sprite* MazeEnemy::GetSprite()
{
	return mSprite;
}

void MazeEnemy::Move()
{

}

const std::pair<int, int> MazeEnemy::FlipY(std::pair<int, int> const position)
{
	return std::make_pair(position.first, mapSize->height - position.second - 1);
}

bool MazeEnemy::canSetPosition(std::pair<int, int> playerPosition, TMXLayer* path)
{
	auto flipP = FlipY(playerPosition);
	return flipP.first >= 0 && flipP.second >= 0 && flipP.first < mapSize->width && flipP.second < mapSize->height && path->getTileAt({ (float)flipP.first, (float)flipP.second }) != NULL;
}

int MazeEnemy::DFSPath(std::pair<int, int> current, std::pair<int, int> const& target, int depth, TMXLayer* path)
{
	auto& [x1, y1] = FlipY(current);
	auto& [a1, b1] = current;

	if (!canSetPosition(current, path) || dfsVisited[x1][y1])
	{
		return -1;
	}

	dfsVisited[x1][y1] = true;
	++depth;

	if (current == target)
	{
		dfsPath.push_back({ x1, y1 });
		return depth;
	}

	std::pair<int, int> adjacentCells[4] = { {a1 + 1, b1}, {a1 - 1, b1} , {a1, b1 + 1} , {a1, b1 - 1} };

	for (auto& adjacentCell : adjacentCells)
	{
		if (int length = DFSPath(adjacentCell, target, depth, path) != -1)
		{
			dfsPath.push_back({ x1, y1 });
			return length;
		}
	}

	return -1;
}


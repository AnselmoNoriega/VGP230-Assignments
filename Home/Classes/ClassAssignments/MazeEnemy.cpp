#include "MazeEnemy.h"
#include "MazeScene2.h"

MazeEnemy::MazeEnemy(cocos2d::Sprite* sprite, cocos2d::Color3B color, const cocos2d::Size* worldSize)
	:mSprite(sprite), mapSize(worldSize)
{
	mSprite->setColor(color);

	bfsVisited.resize((int)mapSize->width);

	for (int i = 0; i < (int)mapSize->width; ++i)
	{
		bfsVisited[i].resize((int)mapSize->height);
	}
}

cocos2d::Sprite* MazeEnemy::GetSprite()
{
	return mSprite;
}

bool MazeEnemy::Move(cocos2d::TMXLayer* path, std::pair<int, int> const& target)
{
	bool found = false;
	bfsPath.clear();

	if (BFSPath(enemyPos, target, path))
	{
		std::shared_ptr<TileNode> currentNode;
		currentNode = std::move(nodes.front());

		while (currentNode)
		{
			bfsPath.push_back(FlipY(currentNode->pos));
			currentNode = std::move(currentNode->parent);
		}
		if (bfsPath.size() >= 2)
		{
			newPos = FlipY(bfsPath.at(bfsPath.size() - 2));
			found = true;
		}
	}


	for (int i = 0; i < mapSize->width; ++i)
	{
		for (int j = 0; j < mapSize->height; ++j)
		{
			bfsVisited[i][j] = false;
		}
	}
	return found;
}

const std::pair<int, int> MazeEnemy::FlipY(std::pair<int, int> const position)
{
	return std::make_pair(position.first, mapSize->height - position.second - 1);
}

bool MazeEnemy::canSetPosition(std::pair<int, int> playerPosition, cocos2d::TMXLayer* path)
{
	auto flipP = FlipY(playerPosition);
	return flipP.first >= 0 && flipP.second >= 0 && flipP.first < mapSize->width && flipP.second < mapSize->height && path->getTileAt({ (float)flipP.first, (float)flipP.second }) != NULL;
}

bool MazeEnemy::BFSPath(std::pair<int, int> current, std::pair<int, int> const& target, cocos2d::TMXLayer* path)
{
	nodes.clear();
	std::pair<int, int> p = FlipY(current);
	std::shared_ptr<TileNode> currentNode(std::make_unique<TileNode>(current, nullptr));

	nodes.push_back(currentNode);
	bfsVisited[p.first][p.second] = true;

	while (!nodes.empty())
	{
		currentNode = std::move(nodes.front());
		nodes.pop_front();

		if (currentNode->pos == target)
		{
			nodes.push_front(std::move(currentNode));
			return true;
		}
		else
		{
			std::pair<int, int> adjacentCells[4] = {
				{currentNode->pos.first + 1, currentNode->pos.second},
				{currentNode->pos.first - 1, currentNode->pos.second},
				{currentNode->pos.first, currentNode->pos.second + 1},
				{currentNode->pos.first, currentNode->pos.second - 1}
			};

			for (auto& cell : adjacentCells)
			{
				p = FlipY(cell);
				if (!canSetPosition(cell, path) || bfsVisited[p.first][p.second])
				{
					continue;
				}

				nodes.push_back(std::make_unique<TileNode>(cell, currentNode));
				bfsVisited[p.first][p.second] = true;
			}
		}
	}


	return false;
}

template<typename T>
T toScreenSpaceT(std::pair<int, int>const& position)
{
	return
	{
	  tileSize->width * (float)position.first,
	  tileSize->height * (float)((int)mapSize->height - position.second - 1)
	};
}

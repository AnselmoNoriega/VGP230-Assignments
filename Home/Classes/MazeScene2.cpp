#include "MazeScene2.h"

bool MazeScene2::init()
{
	if (!MazeScene::init())
	{
		return false;
	}

	dfsVisited.resize((int)mapSize->width);

	for (int i = 0; i < (int)mapSize->width; ++i)
	{
		dfsVisited[i].resize((int)mapSize->height);
	}

	dfsPath.reserve((int)mapSize->width * (int)mapSize->height);

	bfsVisited.resize((int)mapSize->width);

	for (int i = 0; i < (int)mapSize->width; ++i)
	{
		bfsVisited[i].resize((int)mapSize->height);
	}

	bfsPath.reserve((int)mapSize->width * (int)mapSize->height);

	return true;
}

void MazeScene2::update(float dt)
{
	MazeScene::update(dt);

	Vec2 size = { tileSize->width, tileSize->height };

	if (true)
	{
		reset(dfsVisited, dfsPath, false);
		if (int l = dfs(playerPosition, endPosition, 0); l != -1)
		{
			drawVisited(dfsVisited, Color4F::ORANGE, { 0.0f,0.0f }, size, false);
			drawPath(dfsPath, { 0.0f, 0.0f }, Color4F::RED);
		}
		else
		{
			drawVisited(dfsVisited, Color4F::ORANGE, { 0.0f,0.0f }, size, false);
		}
	}
	else
	{
		auto bfsOffset = std::pair{ 0.0f, 0.0f };

		reset(bfsVisited, bfsPath, { -1, -1 });
		if (bfs(playerPosition, endPosition))
		{
			bfsBacktrack();
			drawVisited(bfsVisited, Color4F::GREEN, bfsOffset, size, { -1, -1 });
			drawPath(bfsPath, { 5.0f, -5.0f }, Color4F::BLUE);
		}
		else
		{
			drawVisited(bfsVisited, Color4F::GREEN, bfsOffset, size, { -1, -1 });
		}
	}
}

int MazeScene2::dfs(std::pair<int, int> current, std::pair<int, int>const& target, int depth)
{
	auto& [x1, y1] = current;

	if (dfsVisited[x1][y1] || !canSetPosition(current))
	{
		return -1;
	}

	dfsVisited[x1][y1] = true;
	++depth;

	if (current == target)
	{
		return depth;
	}

	std::pair<int, int> adjacentCells[4] = { {x1 + 1, y1}, {x1 - 1, y1} , {x1, y1 + 1} , {x1, y1 - 1} };

	for (auto& adjacentCell : adjacentCells)
	{
		if (auto length = dfs(adjacentCell, target, depth) != -1)
		{
			return length;
		}
	}

	return -1;
}

bool MazeScene2::bfs(std::pair<int, int> current, std::pair<int, int>const& target)
{
	/*auto parents = { current };

	while (parents.size() > 0)
	{
		auto children = { current };

		for (auto parent : parents)
		{
			for (auto child : parent)
			{
				l(child)
					children.add(child)
			}
		}

		parents = children;
	}*/
}

bool MazeScene2::bfsVisitChild(std::pair<int, int> const& parent, std::pair<int, int> const& c, std::pair<int, int> const& t, std::vector<std::pair<int, int>>& children)
{
	/// TODO: Fill in
	return false;
}

void MazeScene2::bfsBacktrack()
{
	/// TODO: Fill in
}
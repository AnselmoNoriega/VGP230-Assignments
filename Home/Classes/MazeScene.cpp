#include "MazeScene.h"

cocos2d::Scene* MazeScene::createScene()
{
	return MazeScene::create();
}

bool MazeScene::init()
{
	auto map = TMXTiledMap::create("tmx/desert.tmx");
	path = map->getLayer("Path");
	collision = map->getLayer("Collision");
	auto playerStartLayer = map->getLayer("Player");
	auto playerEndLayer = map->getLayer("Player End");

	mapSize = &path->getLayerSize();
	tileSize = &path->getMapTileSize();

	this->addChild(map);

	map->setScale(1.5f);

	ratUp = Sprite::create("mouse-0.png");     //0, 1, 2
	ratUp->setVisible(false);
	ratRight = Sprite::create("mouse-3.png");  //3, 4, 5
	ratDown = Sprite::create("mouse-6.png");   //6, 7, 8
	ratDown->setVisible(false);
	ratLeft = Sprite::create("mouse-9.png");   //9, 10, 11
	ratLeft->setVisible(false);

	cheese = Sprite::create("Cheese.png");

	drawNode = DrawNode::create(10);

	map->addChild(ratUp, 5);
	map->addChild(ratRight, 5);
	map->addChild(ratDown, 5);
	map->addChild(ratLeft, 5);
	map->addChild(drawNode, 4);
	map->addChild(cheese, 4);

	active = ratRight;

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event)
	{
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			left = true;
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			right = true;
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			down = true;
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			up = true;
			break;
		};
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	this->scheduleUpdate();

	initialize(active, playerStartLayer, playerPosition);
	initialize(cheese, playerEndLayer, endPosition, false);

	playerStartLayer->setVisible(false);
	playerEndLayer->setVisible(false);

	gameState = Running;

	return true;
}

void MazeScene::initialize(Sprite* spr, TMXLayer* layer, std::pair<int, int>& position, bool draw)
{
	for (float r = 0; r < layer->getLayerSize().width; ++r)
	{
		for (float c = 0; c < layer->getLayerSize().height; ++c)
		{
			if (layer->getTileAt({ r,c }) != NULL)
			{
				setPosition(spr, FlipY(std::make_pair(r, c)), position, draw);
				return;
			}
		}
	}
}

std::pair<int, int> MazeScene::FlipY(std::pair<int, int> position)
{
	return std::make_pair(position.first, mapSize->height - position.second - 1);
}

void MazeScene::setPosition(Sprite* spr, std::pair<int, int> newPosition, std::pair<int, int>& oldPosition, bool draw)
{
	oldPosition = newPosition;

	auto x = tileSize->width * newPosition.first + tileSize->width / 2;
	auto y = tileSize->height * newPosition.second + tileSize->width / 2;

	spr->setPosition(x, y);

	drawNode->clear();

	if (draw)
	{
		auto dx = tileSize->width / 2;
		auto dy = tileSize->height / 2;
		drawNode->drawRect(Vec2(x - dx, y + dy), Vec2(x + dx, y + dy), Vec2(x + dx, y - dy), Vec2(x - dx, y - dy), Color4F::RED);
	}
}

bool MazeScene::canSetPosition(std::pair<int, int> p)
{
	auto flipP = FlipY(p);
	return flipP.first >= 0 && flipP.second >= 0 && flipP.first < mapSize->width && flipP.second < mapSize->height && path->getTileAt({ (float)flipP.first, (float)flipP.second }) != NULL;
}

void MazeScene::update(float dt)
{
	/// TODO: Check if game state is running

	if (gameState == Running)
	{
		if (down)
		{
			/// TODO: fix line below and determine correct new location
			auto p = std::make_pair(playerPosition.first, playerPosition.second - 1);

			changeActiveSprite(ratDown);

			if (canSetPosition(p))
			{
				/// TODO: call Change Active Sprite
				setPosition(active, p, playerPosition);
			}
		}
		else if (left)
		{
			/// TODO: fix line below and determine correct new location
			auto p = std::make_pair(playerPosition.first - 1, playerPosition.second);

			changeActiveSprite(ratLeft);

			if (canSetPosition(p))
			{
				/// TODO: call Change Active Sprite
				setPosition(active, p, playerPosition);
			}
		}
		else if (up)
		{
			/// TODO: fix line below and determine correct new location
			auto p = std::make_pair(playerPosition.first, playerPosition.second + 1);

			changeActiveSprite(ratUp);

			if (canSetPosition(p))
			{
				setPosition(active, p, playerPosition);
			}
		}
		else if (right)
		{
			/// TODO: fix line below and determine correct new location
			auto p = std::make_pair(playerPosition.first + 1, playerPosition.second);

			changeActiveSprite(ratRight);

			if (canSetPosition(p))
			{
				/// TODO: call Change Active Sprite
				setPosition(active, p, playerPosition);
			}
		}

		if (playerPosition == endPosition)
		{
			gameState = FoundCheese;
		}
	}

	if (gameState == FoundCheese)
	{
		active->setRotation(active->getRotation() + 180 * dt);

		if (active->getRotation() >= 360)
		{
			gameState = Victory;
		}
	}

	ResetInput();
}

void MazeScene::changeActiveSprite(Sprite* newActive)
{
	if (active != newActive)
	{
		auto temp = active->getPosition();
		active->setVisible(false);
		active = newActive;
		active->setPosition(temp);
		active->setVisible(true);
	}
}

void MazeScene::ResetInput()
{
	down = false;
	left = false;
	up = false;
	right = false;
}


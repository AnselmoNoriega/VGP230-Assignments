#include "MazeScene.h"
#include "MidTerm/VictoryScene.h"
#include "LW.h"

cocos2d::Scene* MazeScene::createScene()
{
	return MazeScene::create();
}

bool MazeScene::init()
{
	map = TMXTiledMap::create("tmx/desert.tmx");
	path = map->getLayer("Path");
	collision = map->getLayer("Collision");
	playerStartLayer = map->getLayer("Player");
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

	enemies.push_back(MazeEnemy(Sprite::create("oqzome.png"), cocos2d::Color3B::RED, mapSize));
	enemies.push_back(MazeEnemy(Sprite::create("oqzome.png"), cocos2d::Color3B::RED, mapSize));

	drawNode = DrawNode::create(10);

	map->addChild(ratUp, 5);
	map->addChild(ratRight, 5);
	map->addChild(ratDown, 5);
	map->addChild(ratLeft, 5);
	map->addChild(drawNode, 4);

	CheesePath();

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
			case EventKeyboard::KeyCode::KEY_C:
				draw = !draw;
				break;
			};
		};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	this->scheduleUpdate();

	initialize(active, playerStartLayer, playerPosition, draw);

	enemies[0].spawnPoint = { 10, 3 };
	enemies[1].spawnPoint = { 10, 5 };

	for (auto& enemy : enemies)
	{
		enemy.GetSprite()->setScale(0.15f);
		map->addChild(enemy.GetSprite(), 5);
		setPosition(enemy.GetSprite(), enemy.spawnPoint, enemy.enemyPos, draw);
	}

	playerStartLayer->setVisible(false);
	playerEndLayer->setVisible(false);
	playerLives = 3;

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

const std::pair<int, int> MazeScene::FlipY(std::pair<int, int> const position)
{
	return std::make_pair(position.first, mapSize->height - position.second - 1);
}

void MazeScene::setPosition(Sprite* spr, std::pair<int, int> newPosition, std::pair<int, int>& oldPosition, bool draw)
{
	oldPosition = newPosition;

	auto x = tileSize->width * newPosition.first + tileSize->width / 2;
	auto y = tileSize->height * newPosition.second + tileSize->width / 2;

	spr->setPosition(x, y);

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
	isPlayerMoving = false;

	if (gameState == Running)
	{
		if (down)
		{
			/// TODO: fix line below and determine correct new location
			auto p = std::make_pair(playerPosition.first, playerPosition.second - 1);

			changeActiveSprite(ratDown);
			drawNode->clear();

			if (canSetPosition(p))
			{
				/// TODO: call Change Active Sprite
				setPosition(active, p, playerPosition, draw);
			}

			isPlayerMoving = true;
		}
		else if (left)
		{
			/// TODO: fix line below and determine correct new location
			auto p = std::make_pair(playerPosition.first - 1, playerPosition.second);

			changeActiveSprite(ratLeft);
			drawNode->clear();

			if (canSetPosition(p))
			{
				/// TODO: call Change Active Sprite
				setPosition(active, p, playerPosition, draw);
			}

			isPlayerMoving = true;
		}
		else if (up)
		{
			/// TODO: fix line below and determine correct new location
			auto p = std::make_pair(playerPosition.first, playerPosition.second + 1);

			changeActiveSprite(ratUp);
			drawNode->clear();

			if (canSetPosition(p))
			{
				setPosition(active, p, playerPosition, draw);
			}

			isPlayerMoving = true;
		}
		else if (right)
		{
			/// TODO: fix line below and determine correct new location
			auto p = std::make_pair(playerPosition.first + 1, playerPosition.second);

			changeActiveSprite(ratRight);
			drawNode->clear();

			if (canSetPosition(p))
			{
				/// TODO: call Change Active Sprite
				setPosition(active, p, playerPosition, draw);
			}

			isPlayerMoving = true;
		}

		for (int i = 0; i < endPosition.size(); ++i)
		{
			if (playerPosition == endPosition[i])
			{
				if (cheese[i]->getColor() == Color3B::BLUE)
				{
					playerState = Invincible;
					stateDuration = 11;
					for (auto& enemy : enemies)
					{
						enemy.GetSprite()->setColor(Color3B::WHITE);
					}
				}

				cheese[i]->setVisible(false);
				cheese.erase(cheese.begin() + i);
				endPosition.erase(endPosition.begin() + i);
			}
		}
	}

	if (endPosition.size() == 0)
	{
		gameState = FoundCheese;
	}

	if (gameState == FoundCheese)
	{
		active->setRotation(active->getRotation() + 180 * dt);

		if (active->getRotation() >= 360)
		{
			gameState = Victory;
			Director::getInstance()->replaceScene(VictoryScene::createScene());
		}
	}

	ResetInput();

	for (auto& enemy : enemies)
	{
		if (isPlayerMoving && enemy.Move(path, playerPosition))
		{
			setPosition(enemy.GetSprite(), enemy.newPos, enemy.enemyPos, draw);
		}

		if (enemy.enemyPos == playerPosition && playerState == Normal)
		{
			PlayerHit();
		}
		else if (enemy.enemyPos == playerPosition && playerState == Invincible)
		{
			setPosition(enemy.GetSprite(), enemy.spawnPoint, enemy.enemyPos, draw);
		}

	}

	if (stateDuration <= 0)
	{
		playerState = Normal;
		for (auto& enemy : enemies)
		{
			enemy.GetSprite()->setColor(Color3B::RED);
		}
	}
	else if (isPlayerMoving && playerState == Invincible)
	{
		--stateDuration;
	}
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

void MazeScene::CheesePath()
{
	std::pair<int, int> temp = { -1, -1 };
	auto& [x1, y1] = temp;

	for (int i = 0; i < mapSize->width; ++i)
	{
		++x1;
		y1 = -1;

		for (int j = 0; j < mapSize->height; ++j)
		{
			++y1;

			if (canSetPosition({ x1, y1 }))
			{
				auto rand = cocos2d::random(0, 15);
				endPosition.push_back({ x1, y1 });
				cheese.push_back(Sprite::create("Cheese.png"));
				map->addChild(cheese.back(), 4);
				setPosition(cheese.back(), { x1, y1 }, temp, false);

				if (rand == 5)
				{
					cheese.back()->setColor(Color3B::BLUE);
				}
			}
		}
	}
}

void MazeScene::PlayerHit()
{
	changeActiveSprite(ratRight);
	initialize(active, playerStartLayer, playerPosition);
	--playerLives;

	if (playerLives <= 0)
	{
		Director::getInstance()->replaceScene(LW::createScene());
	}
}


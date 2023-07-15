#pragma once
#include "cocos2d.h"
#define MAX 3;

class Assignment1 : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	virtual void update(float dt);

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(Assignment1)

private:
	static const int MAXCHARACTERS = MAX;
	cocos2d::Sprite* character[MAXCHARACTERS];
	cocos2d::Vec2 origin;
	cocos2d::Size ScreenSize;
	cocos2d::Vec2 mSpeed[MAXCHARACTERS];
	cocos2d::Vec2 frameSize[MAXCHARACTERS];
	cocos2d::Vec2 frameEndSize[MAXCHARACTERS];

	void CreateCharacters(int characterIndex, std::string fileName, cocos2d::Vec2 pos, cocos2d::Vec2 speed);
	void CharacterMovemnt(int characterIndex, float deltaTime);
	bool FrameSizeX(int characterIndex);
	bool FrameSizeY(int characterIndex);
};

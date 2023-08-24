#pragma once

#include "cocos2d.h"
#include "KeyboardControllerComponent.h"

USING_NS_CC;

class HelloMario : public Scene
{
public:
  static Scene* createScene();

  virtual bool init();

  virtual void update(float dt);

protected:

  float walkSpeed = 200;
  float jumpSpeed = 400;
  int scale = 2;
  cocos2d::Vec2 startPosition = { origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 };
  Sprite* mario;

  CREATE_FUNC(HelloMario)
private:
  static Vector<SpriteFrame*> getAnimation(const char* format, int count)
  {
    auto spritecache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> animFrames;
    char str[100];
    for (int i = 1; i <= count; i++)
    {
      snprintf(str, sizeof(str), format, i);
      animFrames.pushBack(spritecache->getSpriteFrameByName(str));
    }
    return animFrames;
  }

  void InitPhysics(TMXTiledMap* map);

  enum AnimationState
  {
    Idle,
    Walking,
    Jumping,
    Falling
  } animationState = Idle;

  void ChangeAnim(AnimationState anim, float speed);

  Vector<SpriteFrame*> animFrames[4];
  PhysicsBody* marioPhysicsBody;
  std::vector<PhysicsBody*> contacts;
  KeyboardControllerComponent* controller;

  int movingSpeed = 0;
  bool contact = false;
  Vec2 origin;
  Size visibleSize;
};
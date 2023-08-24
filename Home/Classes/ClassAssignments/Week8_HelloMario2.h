#pragma once

#include "Week7_HelloMario.h"

class HelloMario2 : public HelloMario
{
public:
  static Scene* createScene();

  virtual bool init();

  virtual void update(float dt);

  void load();

  void save();

  void initPauseMenu();

  void showPauseMenu();
  void hidePauseMenu();

  CREATE_FUNC(HelloMario)
private:
  cocos2d::Menu* menu;
};
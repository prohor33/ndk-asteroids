#include "game_logic.h"
#include "graphic_engine.h"
#include "physics_engine.h"

void GameLogic::Initialize() {
  PEngine->addObject(Vec2(), Vec2(), SpaceObject::SPACE_SHIP);
  PEngine->addObject(Vec2(), Vec2(5, 5), SpaceObject::BULLET);
  return;
}

void GameLogic::MainGameLoop(double dt) {
  // TODO: some game stuff here
  boost::shared_ptr<int> a(new int);
  vector<boost::shared_ptr<int> > v;
  v.push_back(boost::shared_ptr<int>(new int));

  PEngine->updateGameState(dt);

  Graphic->renderFrame();
  return;
}

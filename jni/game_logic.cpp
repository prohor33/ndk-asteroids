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
  PEngine->updateGameState(dt);

  Graphic->renderFrame();
  return;
}

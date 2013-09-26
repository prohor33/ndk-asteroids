#include "game_logic.h"
#include "graphic_engine.h"
#include "physics_engine.h"

void GameLogic::Initialize() {
  PEngine->addObject(Vec2(), Vec2(), SpaceObject::SPACE_SHIP);
  return;
}

void GameLogic::MainGameLoop(double dt) {
  // TODO: some game stuff here
  PEngine->updateGameState( dt );

  Graphic->renderFrame();
  return;
}

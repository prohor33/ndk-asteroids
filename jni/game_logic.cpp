#include "game_logic.h"
#include "graphic_engine.h"
#include "physics_engine.h"
#include "space_ship.h"
#include "app.h"

void GameLogic::Initialize() {
  if (justResume)
    return;
  // in case if we need reinitialize the ship
  // for example, we run application
  // after it's finished before
  __android_log_print(ANDROID_LOG_INFO, "Asteroids", "shouldDeinitialise = %i", shouldDeinitialise);
  if (shouldDeinitialise) {
    SpaceShip::needReinitializing = true;
    Ship;
  }
  else
    PEngine->addObject(Vec2(), Vec2(), SpaceObject::SPACE_SHIP);
  newGame();
  justResume = true;
  return;
}

void GameLogic::DeInitialize() {
  shouldDeinitialise = true;
  justResume = false;
  PEngine->deleteAllObjects();
  paused = false;
}

void GameLogic::newGame() {
  // TODO: set scores to zero
  // or something like that
}

void GameLogic::gameOver() {
  if (paused)
    return;
  paused = true;
  _pause();
}

void GameLogic::restartGame() {
  DeInitialize();
  Initialize();
}

void GameLogic::MainGameLoop(double dt) {
  // TODO: some game stuff here
  PEngine->updateGameState(dt);

  Graphic->renderFrame();
  return;
}

#include "game_logic.h"
#include "graphic_engine.h"
#include "physics_engine.h"
#include "space_ship.h"
#include "app.h"

// it's level switch time, actually
float GameLogic::levelTime[] = { 30, 30+30, 30+30+-1 };

void GameLogic::Initialize() {
  if (justResume)
    return;
  // in case if we need reinitialize the ship
  // for example, we run application
  // after it's finished before
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
  level = 0;
  score = 0;
  timePassed = 0;
  debug_flag1 = true;
  debug_flag2 = true;
}

void GameLogic::gameOver() {
  if (paused)
    return;
  paused = true;
  _pause();
}

void GameLogic::setNeedRestart() {
  needRestart = true;
}

void GameLogic::restartGame() {
  needRestart = false;
  _resume();
  DeInitialize();
  Initialize();
}

void GameLogic::MainGameLoop(double dt) {
  if (needRestart)
    restartGame();
  timePassed += dt;
  if (timePassed > levelTime[level]) {
    if (level < 2) {
      level++;
      __android_log_print(ANDROID_LOG_INFO, "Asteroids", "level up!");
    }
  }
  PEngine->updateGameState(dt);
  Graphic->renderFrame();
  return;
}

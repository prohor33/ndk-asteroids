#include "game_logic.h"
#include "graphic_engine.h"
#include "physics_engine.h"
#include "space_ship.h"
#include "app.h"

// level switch time
float GameLogic::levelEndTime[] =
{ 30, 30+30, 30+30+30, 30+30+30+45, 30+30+30+45+-1 /* never mind */ };

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
  if (paused) {
    _resume();
    paused = false;
  }
  needRestart = false;
  return;
}

void GameLogic::DeInitialize() {
  shouldDeinitialise = true;
  justResume = false;
  PEngine->deleteAllObjects();
  if (!paused) {
    paused = true;
    _pause();
  }
}

void GameLogic::newGame() {
  level = 0;
  score = 0;
  timePassed = 0;
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
  DeInitialize();
  Initialize();
}

void GameLogic::MainGameLoop(double dt) {
  if (needRestart)
    restartGame();
  timePassed += dt;
  if (timePassed > levelEndTime[level]) {
    if (level < 3) {
      // level up!
      level++;
    }
  }
  PEngine->updateGameState(dt);
  Graphic->renderFrame();
  return;
}

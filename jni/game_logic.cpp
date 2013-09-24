#include "game_logic.h"
#include "graphic_engine.h"
#include "physics_engine.h"
#include "bullets_container.h"

void GameLogic::Initialize() {
  return;
}

void GameLogic::MainGameLoop(double dt) {
  // TODO: some game stuff here
  PEngine->UpdateGameState( dt );

  Graphic->RenderFrame();
  return;
}

#include "game_logic.h"
#include "graphic_engine.h"
#include "physics_engine.h"
#include "bullets_container.h"

void GameLogic::Initialize() {
  Vec2 p(20,20);
  Vec2 v(1,4);
  BulletsCont->addBullet( p, v );
  p.x() = -30;
  p.y() = 50;
  v.x() = 2;
  v.y() = -3;
  BulletsCont->addBullet( p, v );
  return;
}

void GameLogic::MainGameLoop(double dt) {
  // TODO: some game stuff here
  PEngine->UpdateGameState( dt );

  Graphic->RenderFrame();
  return;
}

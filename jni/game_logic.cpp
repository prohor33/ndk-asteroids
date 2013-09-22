#include "game_logic.h"
#include "graphic_engine.h"
#include "physics_engine.h"
#include "bullets_container.h"

void GameLogic::Initialize() {
  Vec2 p(0.5,0.5);
  Vec2 v(0.1,0);
  BulletsCont->addBullet( p, v );
  p.x() = 0;
  p.y() = 0;
  v.x() = 0.2;
  v.y() = -0.3;
  BulletsCont->addBullet( p, v );
  return;
}

void GameLogic::MainGameLoop() {
  // TODO: some game stuff here
  // TODO: count real dt
  double dt = 0.01f;
  PEngine->UpdateGameState( dt );

  Graphic->RenderFrame();
  return;
}

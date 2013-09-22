#include "game_logic.h"
#include "graphic_engine.h"
#include "physics_engine.h"
#include "bullets_container.h"

void GameLogic::Initialize() {
  Vec2 p(0.5,0.5);
  Vec2 v(0.1,0);
  BulletsCont->addBullet( p, v );
  v.x() = 0.2;
  v.y() = -0.3;
  BulletsCont->addBullet( p, v );
  return;
}

void GameLogic::MainGameLoop() {
  // TODO: some game stuff here
  // TODO: count real dt
  double dt = 1.0f;
  PEngine->UpdateGameState( dt );

  Graphic->RenderFrame();
  return;
}

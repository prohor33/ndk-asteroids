#include "game_logic.h"
#include "graphic_engine.h"
#include "physics_engine.h"
#include "bullets_container.h"

void GameLogic::Initialize() {
//  Vec2 p(20,20);
//  Vec2 v(1,4);
//  BulletsCont->addBullet( p, v );
//  p.x() = 50;
//  p.y() = 50;
//  v.x() = 2;
//  v.y() = -3;
//  BulletsCont->addBullet( p, v );
  BulletsCont->addBullet( Vec2(0, 0), Vec2(1,1) );
  BulletsCont->addBullet( Vec2(0, GLogic->getScreenSize().y()), Vec2() );
  BulletsCont->addBullet( GLogic->getScreenSize(), Vec2() );
  BulletsCont->addBullet( GLogic->getScreenSize()/2, Vec2() );
  BulletsCont->addBullet( Vec2(GLogic->getScreenSize().x(), 0), Vec2() );
  return;
}

void GameLogic::MainGameLoop(double dt) {
  // TODO: some game stuff here
  PEngine->UpdateGameState( dt );

  Graphic->RenderFrame();
  return;
}

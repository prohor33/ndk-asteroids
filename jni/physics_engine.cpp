#include "physics_engine.h"
#include "bullet.h"
#include "bullets_container.h"
#include "obstacle.h"
#include "obstacles_container.h"
#include "space_ship.h"

void PhysicsEngine::UpdateGameState( double dt ) {
	UpdateObstacles( dt );
	UpdateBullets( dt );
	UpdateSpaceShip( dt );
	return;
}

void PhysicsEngine::UpdateObstacles( double dt ) {
  //__android_log_print(ANDROID_LOG_INFO, "Asteroids", "UpdateObstacles");
  vector<Obstacle*>::iterator cii;
  for( cii=ObstCont->getMass().begin(); cii!=ObstCont->getMass().end(); ++cii )
    (*cii)->getPos() += (*cii)->getVel()*dt;
  //__android_log_print(ANDROID_LOG_INFO, "Asteroids", "UpdateObstacles end");
  return;
}

void PhysicsEngine::UpdateBullets( double dt ) {
//  __android_log_print(ANDROID_LOG_INFO, "Asteroids", "UpdateBullets size = %i, size2 = %i",
//      BulletsCont->getMass().size(), BulletsCont->mBullets.size());
  vector<Bullet*>::iterator cii;
  //for( cii=BulletsCont->mBullets.begin(); cii!=BulletsCont->mBullets.end(); ++cii )
  for( cii=BulletsCont->getMass().begin(); cii!=BulletsCont->getMass().end(); ++cii )
    (*cii)->getPos() += (*cii)->getVel()*dt;
  //__android_log_print(ANDROID_LOG_INFO, "Asteroids", "UpdateBullets end");
  return;
}

void PhysicsEngine::UpdateSpaceShip( double dt ) {
  Ship->getPos() += Ship->getVel()*dt;
  Ship->update(dt);
  return;
}




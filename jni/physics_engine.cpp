#include "physics_engine.h"
#include "bullet.h"
#include "bullets_container.h"

void PhysicsEngine::UpdateGameState( double dt ) {
	UpdateObstacles( dt );
	UpdateBullets( dt );
	UpdateSpaceShip( dt );
	return;
}

void PhysicsEngine::UpdateObstacles( double dt ) {
  return;
}

void PhysicsEngine::UpdateBullets( double dt ) {
  vector<Bullet*>::iterator cii;
  for( cii=BulletsCont->mBullets.begin(); cii!=BulletsCont->mBullets.end(); ++cii ) {
    (*cii)->getPos().x() += (*cii)->getVel().x()*dt;
    (*cii)->getPos().y() += (*cii)->getVel().y()*dt;
  }
  return;
}

void PhysicsEngine::UpdateSpaceShip( double dt ) {
  return;
}




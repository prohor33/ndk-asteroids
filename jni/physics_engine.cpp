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
  vector<Obstacle*>::iterator cii;
  for( cii=ObstCont->getMass().begin(); cii!=ObstCont->getMass().end(); ++cii )
    (*cii)->getPos() += (*cii)->getVel()*dt;
  return;
}

void PhysicsEngine::UpdateBullets( double dt ) {
  vector<Bullet*>::iterator cii;
  for( cii=BulletsCont->getMass().begin(); cii!=BulletsCont->getMass().end(); ++cii )
    (*cii)->getPos() += (*cii)->getVel()*dt;
  return;
}

void PhysicsEngine::UpdateSpaceShip( double dt ) {
  Ship->getPos() += Ship->getVel()*dt;
  Ship->update(dt);
  return;
}




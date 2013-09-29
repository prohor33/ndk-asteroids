#include "physics_engine.h"
#include "bullet.h"
#include "obstacle.h"
#include "space_ship.h"

void PhysicsEngine::updateGameState(float dt) {
	update(dt);
//	computeCollisions();
	return;
}

void PhysicsEngine::update(float dt) {
  size_t a;
  vector<shared_ptr<SpaceObject> >::iterator cii;
  objContainer.reserve(std::size_t(objContainer.size()+10));
  for (cii=objContainer.begin(); cii!=objContainer.end(); ++cii)
    (*cii)->update(dt);
  return;
}

void PhysicsEngine::computeCollisions() {
  vector<shared_ptr<SpaceObject> >::iterator cii;
//  for( cii=objContainer.begin(); cii!=objContainer.end(); ++cii )
//    (*cii)->update(dt);
}

void PhysicsEngine::addObject(Vec2 p, Vec2 v,
    SpaceObject::ObjectType objectType) {
  switch (objectType) {
  case SpaceObject::BULLET:
    objContainer.push_back(shared_ptr<SpaceObject> (new Bullet(p, v)));
    break;
  case SpaceObject::OBSTACLE:
    objContainer.push_back(shared_ptr<SpaceObject> (new Obstacle(p, v)));
    break;
  case SpaceObject::SPACE_SHIP:
    objContainer.push_back(shared_ptr<SpaceObject> (Ship));
    break;
  }
}



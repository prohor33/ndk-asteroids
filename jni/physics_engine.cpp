#include "physics_engine.h"
#include "bullet.h"
#include "obstacle.h"
#include "space_ship.h"
#include "game_logic.h"

void PhysicsEngine::updateGameState(float dt) {
	update(dt);
	computeCollisions();
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
  vector<shared_ptr<SpaceObject> >::iterator cii2;
  for (cii=objContainer.begin(); cii!=objContainer.end(); ++cii) {
    // tracking the borders
    if ((*cii)->getPos().x() > GLogic->getHScrSize().x() ||
        (*cii)->getPos().x() < -GLogic->getHScrSize().x() ||
        (*cii)->getPos().y() > GLogic->getHScrSize().y() ||
        (*cii)->getPos().y() < -GLogic->getHScrSize().y()) {
      objContainer.erase(cii);
      continue;
    }
    continue;
    for (cii2=objContainer.begin(); cii2!=objContainer.end(); ++cii2) {
      if (cii == cii2)
        continue;
      if ((*cii)->getObjType() == (*cii2)->getObjType())
        continue;
      switch ((*cii)->getObjType()) {
      case SpaceObject::BULLET:
        // TODO: check whether it intersects
        // if so, invoke blowUp() or something
        if (intesects(*cii, *cii2)) {
          objContainer.erase(cii);
          objContainer.erase(cii2);
        }
        break;
      }
    }
  }
}

bool PhysicsEngine::intesects(shared_ptr<SpaceObject> o1, shared_ptr<SpaceObject> o2) {
  shared_ptr<SpaceObject> max_x =
      o1->getPos().x() > o2->getPos().x() ? o1 : o2;
  shared_ptr<SpaceObject> min_x =
      o1->getPos().x() <= o2->getPos().x() ? o1 : o2;
  shared_ptr<SpaceObject> max_y =
      o1->getPos().y() > o2->getPos().y() ? o1 : o2;
  shared_ptr<SpaceObject> min_y =
      o1->getPos().y() <= o2->getPos().y() ? o1 : o2;
  if (max_x->getPos().x() - max_x->getSize().x() <
      min_x->getPos().x() + min_x->getSize().x()) {
    if (max_x->getPos().y() - max_y->getSize().y() <
          min_x->getPos().y() + min_x->getSize().y()) {
      return true;
    }
  }
  return false;
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



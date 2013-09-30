#include "physics_engine.h"
#include "bullet.h"
#include "obstacle.h"
#include "space_ship.h"
#include "game_logic.h"

void PhysicsEngine::updateGameState(float dt) {
	update(dt);
	spawnObstacles(dt);
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
  // we have some trouble here with erasing and iterators
  for (cii=objContainer.begin(); cii!=objContainer.end();) {
    // tracking the borders
    if ((*cii)->getPos().x() > GLogic->getHScrSize().x() ||
        (*cii)->getPos().x() < -GLogic->getHScrSize().x() ||
        (*cii)->getPos().y() > GLogic->getHScrSize().y() ||
        (*cii)->getPos().y() < -GLogic->getHScrSize().y()) {
      if ((*cii)->getErasable()) {
        objContainer.erase(cii);
        continue;
      }
    }
    else {
      if (!(*cii)->getErasable())
        (*cii)->setErasable(true);
    }
    for (cii2=objContainer.begin(); cii2!=objContainer.end(); ++cii2) {
      if ((*cii) == (*cii2))
        continue;
      if ((*cii)->getObjType() == (*cii2)->getObjType())
        continue;
      switch ((*cii)->getObjType()) {
      case SpaceObject::BULLET:
        switch ((*cii2)->getObjType()) {
        // with
        case SpaceObject::OBSTACLE:
          // TODO: check whether it intersects
          // if so, invoke blowUp() or something
          if (intesects(*cii, *cii2)) {
            eraseFromObjCont(cii, cii2);
            goto this_object;
          }
          break;
        }
        break;
      }
    }
    ++cii;
    this_object: {}
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
    if (max_y->getPos().y() - max_y->getSize().y() <
          min_y->getPos().y() + min_y->getSize().y()) {
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
    objContainer.push_back(shared_ptr<SpaceObject> (new Obstacle()));
    break;
  case SpaceObject::SPACE_SHIP:
    objContainer.push_back(shared_ptr<SpaceObject> (Ship));
    break;
  }
}

void PhysicsEngine::spawnObstacles(float dt) {
  deltaSpawnObstacle_t += dt;
  if (deltaSpawnObstacle_t > 1.0f) {
    deltaSpawnObstacle_t = 0;
    // spawn new obstacle
    addObject(Vec2(), Vec2(), SpaceObject::OBSTACLE);
  }
}

void PhysicsEngine::eraseFromObjCont(
    vector<shared_ptr<SpaceObject> >::iterator& it1,
    vector<shared_ptr<SpaceObject> >::iterator& it2) {
  if (it1 == it2) {
    objContainer.erase(it1);
    --it2;
    return;
  }
  if (it1 < it2) {
    objContainer.erase(it2);
    objContainer.erase(it1);
    it2--;
    return;
  }
  if (it2 < it1) {
    objContainer.erase(it1);
    objContainer.erase(it2);
    it1--;
    return;
  }
}

#include "physics_engine.h"
#include "bullet.h"
#include "obstacle.h"
#include "space_ship.h"
#include "game_logic.h"

void PhysicsEngine::updateGameState(float dt) {
  if (GLogic->getPaused())
    return;
	update(dt);
	spawnObstacles(dt);
	computeCollisions();
	return;
}

void PhysicsEngine::update(float dt) {
  vector<shared_ptr<SpaceObject> >::iterator cii;
  objContainer.reserve(std::size_t(objContainer.size()+50));
  for (cii=objContainer.begin(); cii!=objContainer.end();) {
    if (!(*cii)->update(dt)) {
      objContainer.erase(cii);
      continue;
    }
    ++cii;
  }
  return;
}

void PhysicsEngine::computeCollisions() {
  vector<shared_ptr<SpaceObject> >::iterator cii;
  vector<shared_ptr<SpaceObject> >::iterator cii2;
  objContainer.reserve(std::size_t(objContainer.size()+50));
  for (cii=objContainer.begin(); cii!=objContainer.end();) {
    // tracking objects out of borders
    if ((*cii)->getPos().x() - (*cii)->getSize().x()*3/2 > GLogic->getHScrSize().x() ||
        (*cii)->getPos().x() + (*cii)->getSize().x()*3/2 < -GLogic->getHScrSize().x() ||
        (*cii)->getPos().y() - (*cii)->getSize().y()*3/2 > GLogic->getHScrSize().y() ||
        (*cii)->getPos().y() + (*cii)->getSize().y()*3/2 < -GLogic->getHScrSize().y()) {
      objContainer.erase(cii);
      continue;
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
          if (intesects(*cii, *cii2)) {
            (*cii2)->collide(SpaceObject::BULLET);
            GLogic->addScore(1);
            eraseFromObjCont(cii, cii2);
            goto this_object;
          }
          break;
        }
        break;
      case SpaceObject::SPACE_SHIP:
        switch ((*cii2)->getObjType()) {
        // with
        case SpaceObject::OBSTACLE:
          if (intesects(*cii, *cii2)) {
            (*cii)->collide((*cii2)->getObjType());
          }
        }
        break;
      case SpaceObject::BONUS:
        switch ((*cii2)->getObjType()) {
        // with
        case SpaceObject::SPACE_SHIP:
          if (intesects(*cii, *cii2)) {
            (*cii)->collide((*cii2)->getObjType());
            objContainer.erase(cii);
            continue;
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

typedef boost::geometry::model::d2::point_xy<GLfloat> point;
typedef boost::geometry::model::polygon<point,false, false> b_polygon;
// "false, false" is counterclockwise order and open polygons

point rotateVector(point p, float angle) {
  float alpha;
  float rad;
  // compute alpha
  if (p.x() == 0) {
    // vector can be vertical
    // so dividing by zero will occur
    if (p.y() > 0)
      alpha = PI/2;
    else
      alpha = -PI/2;
  }
  else {
    alpha = atan(p.y() / p.x());
    if (p.x() < 0)
      alpha += PI;
  }
  alpha += angle;
  rad = sqrt(p.x()*p.x() + p.y()*p.y());
  return point(rad * cos(alpha), rad * sin(alpha));
}

b_polygon createPolygon(shared_ptr<SpaceObject> obj) {
  b_polygon pol;
  point p;
  int i = 0;
  switch (obj->getObjType()) {
  case SpaceObject::OBSTACLE:
    if (dynamic_cast<Obstacle*>(obj.get())->getObstType() == Obstacle::WHOLE)
      i = 1;
    break;
  case SpaceObject::SPACE_SHIP:
  case SpaceObject::BONUS:
      i = 1;
    break;
  }
  for (i;i<obj->getPolPointsSize();++i) {
    p = point(obj->getPolPoints()[2*i], obj->getPolPoints()[2*i+1]);
    // considering objects rotation
    p = rotateVector(p, obj->getAngle());
    pol.outer().push_back(point(p.x() + obj->getPos().x(),
            p.y() + obj->getPos().y()));
  }
  return pol;
}

bool PhysicsEngine::intesects(shared_ptr<SpaceObject> o1, shared_ptr<SpaceObject> o2) {
  b_polygon pol1, pol2;
  point p;
  pol1 = createPolygon(o1);
  pol2 = createPolygon(o2);

  std::deque<b_polygon> output;
  boost::geometry::intersection(pol1, pol2, output);

  if (o1->getObjType() == SpaceObject::SPACE_SHIP && output.size() > 0 ) {
    // let's mark the ship intersection
    o1->setColor(Color(1, 0, 0, 0));
    o2->setColor(Color(1, 0, 0, 0));
  }

  if (output.size() > 0)
    return true;
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
  case SpaceObject::BONUS:
    objContainer.push_back(shared_ptr<SpaceObject> (new Bonus(p)));
    break;
  }
}

void PhysicsEngine::spawnObstacles(float dt) {
  deltaSpawnObstacle_t += dt;
  float maxDeltaSpawnObstacles[] = { 2.0, 1.5, 1.0, 0.8, 0.3 };
  if (deltaSpawnObstacle_t > maxDeltaSpawnObstacles[GLogic->getLevel()]) {
    deltaSpawnObstacle_t = 0;
    // spawn new obstacle
    addObject(Vec2(), Vec2(), SpaceObject::OBSTACLE);
  }
}

void PhysicsEngine::eraseFromObjCont(
    vector<shared_ptr<SpaceObject> >::iterator& it1,
    vector<shared_ptr<SpaceObject> >::iterator& it2) {
  // we have two iterators at once.
  // when you erase two elements from vector
  // it may "corrupt" one of the iterators
  // so, we have to do some trick here
  if (it1 == it2) {
    objContainer.erase(it1);
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

void PhysicsEngine::deleteAllObjects() {
  // we should prevent static
  // spaceship from deleting
  shared_ptr<SpaceObject> copy;
  vector<shared_ptr<SpaceObject> >::iterator cii;
  for (cii=objContainer.begin(); cii!=objContainer.end(); ++cii) {
    if ((*cii)->getObjType() == SpaceObject::SPACE_SHIP) {
      copy = (*cii);
      break;
    }
  }
  objContainer.clear();
  objContainer.push_back(copy);
}

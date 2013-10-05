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
  vector<shared_ptr<SpaceObject> >::iterator cii;
  objContainer.reserve(std::size_t(objContainer.size()+50));
  for (cii=objContainer.begin(); cii!=objContainer.end(); ++cii)
    (*cii)->update(dt);
  return;
}

void PhysicsEngine::computeCollisions() {
  vector<shared_ptr<SpaceObject> >::iterator cii;
  vector<shared_ptr<SpaceObject> >::iterator cii2;
  objContainer.reserve(std::size_t(objContainer.size()+50));
  for (cii=objContainer.begin(); cii!=objContainer.end();) {
    // tracking intersections with borders
    if ((*cii)->getPos().x() - (*cii)->getSize().x()/2 > GLogic->getHScrSize().x() ||
        (*cii)->getPos().x() + (*cii)->getSize().x()/2 < -GLogic->getHScrSize().x() ||
        (*cii)->getPos().y() - (*cii)->getSize().y()/2 > GLogic->getHScrSize().y() ||
        (*cii)->getPos().y() + (*cii)->getSize().y()/2 < -GLogic->getHScrSize().y()) {
      if ((*cii)->getErasable() && (*cii)->getObjType() != SpaceObject::SPACE_SHIP) {
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
          if (intesects(*cii, *cii2)) {
            //__android_log_print(ANDROID_LOG_INFO, "Asteroids", "intersects_1");
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
            (*cii)->collide(SpaceObject::OBSTACLE);
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
// "false, false" is counterclockwise order and close polygons

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
  for (int i=0;i<obj->getPolPointsSize();++i) {
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

  if (o1->getObjType() == SpaceObject::SPACE_SHIP && output.size() > 0 && GLogic->debug_flag1) {
    for (std::deque<b_polygon>::iterator it = output.begin(); it!=output.end(); ++it) {
      if ((*it).outer().size() < 3)
        continue;
      shared_ptr<SpaceObject> obj = shared_ptr<SpaceObject>(new Obstacle());
      Obstacle* obst = static_cast<Obstacle*>(obj.get());
      obst->setObstType(Obstacle::PIECE);
      obst->polPoints = shared_ptr<GLfloat[]>(new GLfloat[2*(*it).outer().size()]);
      for (int i=0; i<(*it).outer().size(); i++) {
        __android_log_print(ANDROID_LOG_INFO, "Asteroids", "deq p%i: %f %f",
            i, (*it).outer()[i].x(), (*it).outer()[i].y());
        obst->polPoints[2*i] = (*it).outer()[i].x();
        obst->polPoints[2*i+1] = (*it).outer()[i].y();
        obj->setVel(Vec2());
        obj->setPos(Vec2());
        obj->setAngleVelocity(0);
        obj->setColor(Color(1, 0, 0, 0));
        obj->setPolPointsSize((*it).outer().size());
      }
      objContainer.push_back(obj);
    }
    GLogic->debug_flag1 = false;
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
  }
}

void PhysicsEngine::spawnObstacles(float dt) {
  deltaSpawnObstacle_t += dt;
  float maxDeltaSpawnObstacles[] = { 2.0, 1.5, 1.0 };
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

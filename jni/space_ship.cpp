#include "space_ship.h"
#include "game_logic.h"
#include "physics_engine.h"

SpaceShip::SpaceShip() :
SpaceObject (Vec2(0, -GLogic->getHScrSize().y()+20 ),
    Vec2(), Vec2(20, 30), 50, SpaceObject::SPACE_SHIP),
    deltaFire_t(0), haveTarget(false), dragging(false)  {
  // let it be polygon
  polPointsSize = 4;
  polPoints = shared_ptr<GLfloat[]>(new GLfloat[2*polPointsSize]);
  polPoints[0] = -size.x()/2; polPoints[1] = -size.y()/2;
  polPoints[2] = size.x()/2; polPoints[3] = -size.y()/2;
  polPoints[4] = size.x()/2; polPoints[5] = size.y()/2;
  polPoints[6] = -size.x()/2; polPoints[7] = size.y()/2;
  color = Color(0.0f, 0.0f, 1.0f, 0.0f);
};

void SpaceShip::_fire() {
  PEngine->addObject(p+Vec2(0, size.y()/2), Vec2(0, 25), SpaceObject::BULLET);
  return;
}

void SpaceShip::update(float dt) {
  // firstly we should invoke superclass method
  this->SpaceObject::update(dt);
  deltaFire_t += dt;
  if (deltaFire_t > 0.5f) {
    deltaFire_t = 0;
    _fire();
  }
  // check whether ship reach
  // the target
  if (haveTarget) {
    if ((target_p-p).x() * v.x() < 0 ||
        (target_p-p).y() * v.y() < 0) {
      haveTarget = false;
      v = Vec2();
    }
  }
  return;
}

void SpaceShip::collide(ObjectType withObj) {
  if (withObj == SpaceObject::OBSTACLE) {
    // here we die
  }
}

void SpaceShip::goTo(Vec2 target_p) {
  this->target_p = target_p;
  Vec2 delta = target_p - p;
  delta.normalize();
  v = delta * velocity;
  haveTarget = true;
}

void SpaceShip::eventHandler(EventType eventType, Vec2 pos) {
  switch (eventType) {
  case DOWN:
    // check whether it's start of dragging
    if (pos.x() > p.x() - size.x()/2 &&
        pos.x() < p.x() + size.x()/2 &&
        pos.y() > p.y() - size.y()/2 &&
        pos.y() < p.y() + size.y()/2) {
      dragging = true;
      deltaDragging = p - pos;
      break;
    }
    goTo(pos);
    break;
  case UP:
    dragging = false;
    break;
  case DRAG:
    if (dragging)
      setPos(pos + deltaDragging);
    break;
  }
}

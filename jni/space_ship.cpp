#include "space_ship.h"
#include "game_logic.h"
#include "physics_engine.h"

SpaceShip::SpaceShip() :
SpaceObject (Vec2(0, -GLogic->getHScrSize().y()+20 ),
    Vec2(), Vec2(20, 30), 3, SpaceObject::SPACE_SHIP),
    deltaFire_t(0)  {
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
  return;
}

void SpaceShip::collide(ObjectType withObj) {
  if (withObj == SpaceObject::OBSTACLE) {
    // here we die
  }
}

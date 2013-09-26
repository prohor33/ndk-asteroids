#include "space_ship.h"
#include "game_logic.h"
#include "physics_engine.h"

SpaceShip::SpaceShip() :
SpaceObject (Vec2(0, -GLogic->getHScrSize().y()+20 ),
    Vec2(), Vec2(20, 30), 3, SpaceObject::SPACE_SHIP),
    deltaFire(0)  {};

void SpaceShip::_fire() {
  PEngine->addObject(p, Vec2(0, 50), SpaceObject::BULLET);
}

void SpaceShip::update(float dt) {
  // firstly we should invoke superclass method
  this->SpaceObject::update(dt);
  deltaFire += dt;
  if (deltaFire > 0.3f) {
    deltaFire = 0;
    _fire();
  }
}

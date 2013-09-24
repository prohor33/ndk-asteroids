#include "space_ship.h"
#include "game_logic.h"
#include "bullets_container.h"

SpaceShip::SpaceShip() :
SpaceObject (Vec2(0, -GLogic->getHScrSize().y()+20 ),
    Vec2(), Vec2(20, 30)),
    deltaFire(0)  {};

void SpaceShip::_fire() {
  BulletsCont->addBullet(p, Vec2(0, 50));
}

void SpaceShip::update(float dt) {
  deltaFire += dt;
  if (deltaFire > 0.3f) {
    deltaFire = 0;
    _fire();
  }
}

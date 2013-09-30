#include "obstacle.h"
#include "space_object.h"

Obstacle::Obstacle(Vec2 p, Vec2 v) : SpaceObject (p, v,
    Vec2(30, 30), 2, SpaceObject::OBSTACLE) {
  erasable = false;
};

void Obstacle::update(float dt) {
  // firstly we should invoke superclass method
  this->SpaceObject::update(dt);
}

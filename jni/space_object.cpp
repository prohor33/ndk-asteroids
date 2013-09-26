#include "space_object.h"

void SpaceObject::goTo(Vec2 target_p) {
  this->target_p = target_p;
  Vec2 delta = target_p - p;
  delta.normalize();
  v = delta * velocity;
}

void SpaceObject::update(float dt) {
  p += v * dt;
}

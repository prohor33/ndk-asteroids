#include "space_object.h"

bool SpaceObject::update(float dt) {
  p += v * dt;
  angle += angleVelocity * dt;
  if (angle > 2*PI)
    angle = 0;
  return true;
}

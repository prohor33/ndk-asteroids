#include "space_object.h"

void SpaceObject::update(float dt) {
  p += v * dt;
  return;
}

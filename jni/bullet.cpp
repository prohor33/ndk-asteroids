#include "bullet.h"
#include "game_logic.h"

Bullet::Bullet(Vec2 p, Vec2 v) : SpaceObject (p, v, Vec2(5, 5), 5, SpaceObject::BULLET) {
  // let it be triangle
  polPointsSize = 3;
  polPoints = shared_ptr<GLfloat[]>(new GLfloat[2*polPointsSize]);
  float l = size.x();
  polPoints[0] = -sqrt(3)*l/2; polPoints[1] = -l/2;
  polPoints[2] = 0; polPoints[3] = l;
  polPoints[4] = sqrt(3)*l/2; polPoints[5] = -l/2;
  color = Color(0.0f, 1.0f, 0.0f, 0.0f);
};

void Bullet::update(float dt) {
  // firstly we should invoke superclass method
  this->SpaceObject::update(dt);
}

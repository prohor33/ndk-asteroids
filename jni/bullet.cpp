#include "bullet.h"
#include "game_logic.h"

Bullet::Bullet(Vec2 p, Vec2 v) : SpaceObject (p, v, Vec2(6, 6), -1, SpaceObject::BULLET) {
  // let it be a triangle
  polPointsSize = 4;
  polPoints = shared_ptr<GLfloat[]>(new GLfloat[2*polPointsSize]);
  float l = size.x()/2;
  // counterclockwise order
  polPoints[0] = -sqrt(3)*l/2; polPoints[1] = -l/2;
  polPoints[2] = sqrt(3)*l/2; polPoints[3] = -l/2;
  polPoints[4] = 0; polPoints[5] = l;
  polPoints[6] = -sqrt(3)*l/2; polPoints[7] = -l/2;
  color = Color(0.0f, 1.0f, 0.0f, 0.0f);
  angleVelocity = 8*PI;
};

bool Bullet::update(float dt) {
  // firstly we should invoke superclass method
  return this->SpaceObject::update(dt);
}

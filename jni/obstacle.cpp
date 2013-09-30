#include "obstacle.h"
#include "space_object.h"
#include "game_logic.h"

Obstacle::Obstacle() : SpaceObject (Vec2(), Vec2(),
    Vec2(10, 10), 2, SpaceObject::OBSTACLE),
    obstType(WHOLE) {
  p = Vec2(GLogic->getHScrSize().x()*(rand()%100-50)/50.0f,
      GLogic->getHScrSize().y()+15);
  v = Vec2(0, -5);
  // superclass value
  erasable = false;
  // here we generate random polygon
  float size = 10;
  float size_coef = 0.5;
  float min_size = size * (1 - size_coef);
  float max_size = size * (1 + size_coef);
  polPointsSize = 10;
  float rand_size;
  polPoints = shared_ptr<GLfloat[]>(new GLfloat[2*polPointsSize]);
  // TODO: make delta angle random too
  int k=0;
  for (float alpha = 0; alpha <= 2*PI; alpha+=2*PI/polPointsSize) {
    rand_size = min_size + (max_size-min_size) * (rand() % 100) / 100.0;
    polPoints[k*2] = rand_size * cos(alpha);
    polPoints[k*2+1] = rand_size * sin(alpha);
    k++;
  }
};

void Obstacle::update(float dt) {
  // firstly we should invoke superclass method
  this->SpaceObject::update(dt);
}

#include "obstacle.h"
#include "space_object.h"
#include "game_logic.h"
#include "physics_engine.h"

Obstacle::Obstacle() : SpaceObject (Vec2(), Vec2(),
    Vec2(10, 10), 2, SpaceObject::OBSTACLE),
    obstType(WHOLE) {
  p = Vec2(GLogic->getHScrSize().x()*(rand()%100-50)/50.0f,
      GLogic->getHScrSize().y()/2+15);
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
  polPoints[0] = 0;
  polPoints[1] = 0;
  // something going not right here (+1 -1 somewhere)
  int k=1;
  for (float alpha = 0; alpha <= 2*PI; alpha+=2*PI/(polPointsSize-2)) {
    rand_size = min_size + (max_size-min_size) * (rand() % 100) / 100.0;
    polPoints[k*2] = rand_size * cos(alpha);
    polPoints[k*2+1] = rand_size * sin(alpha);
    k++;
  }
  __android_log_print(ANDROID_LOG_INFO, "Asteroids", "k=%i", k);
};

void Obstacle::update(float dt) {
  // firstly we should invoke superclass method
  this->SpaceObject::update(dt);
}

void Obstacle::blowUp() {
  shared_ptr<SpaceObject> obj;
  int k=0;
  float vel = 5;
  for (float alpha = 1; alpha <= 2*PI; alpha+=2*PI/polPointsSize) {
    obj = shared_ptr<SpaceObject>(new Obstacle());
    obj->setPos(p);
    obj->setVel(Vec2(vel * cos(alpha), vel * sin(alpha)));
    Obstacle* obst = static_cast<Obstacle*>(obj.get());
    obst->setObstType(PIECE);
    obst->polPoints = shared_ptr<GLfloat[]>(new GLfloat[2*3]);
    obst->polPoints[0] = p.x();
    obst->polPoints[1] = p.y();
    obst->polPoints[2] = polPoints[k*2-2];
    obst->polPoints[3] = polPoints[k*2-1];
    obst->polPoints[4] = polPoints[k*2];
    obst->polPoints[5] = polPoints[k*2+1];
    PEngine->objContainer.push_back(obj);
    k++;
  }
}

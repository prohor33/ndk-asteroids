#include "obstacle.h"
#include "space_object.h"
#include "game_logic.h"
#include "physics_engine.h"

Obstacle::Obstacle() : SpaceObject (Vec2(), Vec2(),
    Vec2(20, 20), 2, SpaceObject::OBSTACLE),
    obstType(WHOLE) {
  p = Vec2(GLogic->getHScrSize().x()*(rand()%100-50)/50.0f,
      GLogic->getHScrSize().y()+10);
  float v_y[] = { -10, -15, -20 };
  v = Vec2((rand()%100-50)/50.0 * 4.0, (rand()%30+70)/100.0 * v_y[GLogic->getLevel()]);
  // superclass value
  erasable = false;
  // here we generate random polygon
  float size = this->size.x();
  float size_coef = 0.5;
  float min_rad = size * (1 - size_coef) / 2;
  float max_rad = size * (1 + size_coef) / 2;
  polPointsSize = 8; // real quantity of pieces is polPointsSize-2
  float rand_rad;
  polPoints = shared_ptr<GLfloat[]>(new GLfloat[2*polPointsSize]);
  polPoints[0] = 0;
  polPoints[1] = 0;
  int k=1;
  // this is counterclockwise order too
  for (float alpha = 0; alpha <= 2*PI; alpha+=2*PI/(polPointsSize-2)) {
    rand_rad = min_rad + (max_rad-min_rad) * (rand() % 100) / 100.0;
    polPoints[k*2] = rand_rad * cos(alpha);
    polPoints[k*2+1] = rand_rad * sin(alpha);
    k++;
  }
  // generate random obstacles color and angle velocity
  color = Color((rand()%90+10)/100.0, (rand()%90+10)/100.0, (rand()%90+10)/100.0, 0);
  angleVelocity = (rand()%100-50)/50.0 * 0.2;
};

void Obstacle::update(float dt) {
  // firstly we should invoke superclass method
  this->SpaceObject::update(dt);
}

void Obstacle::collide(ObjectType withObj) {
  if (withObj == SpaceObject::BULLET)
    blowUp();
}

// the most complicated function in that project =)
void Obstacle::blowUp() {
  if (obstType == PIECE)
    return;
  shared_ptr<SpaceObject> obj;
  int k=2;  // because k=0 and k=1 is Vec2(0,0) point
  // and we use [k*2-2] in this loop
  float vel = 5;  // velocity of expansion
  float angle_now;
  float rand_rad;
  Vec2 delta_p;
  // create a bunch of new obstacles (triangles)
  for (float alpha = 2*PI/(polPointsSize-2); alpha <= 2*PI;
      alpha+=2*PI/(polPointsSize-2)) {
    // angle considering rotation
    angle_now = alpha + angle;
    obj = shared_ptr<SpaceObject>(new Obstacle());
    // delta_p is vector between position of new triangle
    // and position of an old obstacle
    delta_p = Vec2(size.x() / 4 * cos(angle_now),
        size.y() / 4 * sin(angle_now));
    obj->setPos(p + delta_p);
    obj->setVel(v + Vec2(vel * cos(angle_now),
        vel * sin(angle_now)));
    obj->setAngleVelocity(0);
    Obstacle* obst = static_cast<Obstacle*>(obj.get());
    obst->setObstType(PIECE);
    // set triangle vertices
    obst->polPoints = shared_ptr<GLfloat[]>(new GLfloat[2*3]);
    obst->polPoints[0] = 0-delta_p.x();
    obst->polPoints[1] = 0-delta_p.y();
    // we will compute rand_rad in order
    // to get rotate it
    rand_rad = Vec2(polPoints[k*2-2], polPoints[k*2-1]).length();
    obst->polPoints[2] = rand_rad * cos(angle_now-2*PI/(polPointsSize-2)) - delta_p.x();
    obst->polPoints[3] = rand_rad * sin(angle_now-2*PI/(polPointsSize-2)) - delta_p.y();
    rand_rad = Vec2(polPoints[k*2], polPoints[k*2+1]).length();
    obst->polPoints[4] = rand_rad * cos(angle_now) - delta_p.x();
    obst->polPoints[5] = rand_rad * sin(angle_now) - delta_p.y();
    // this is triangle
    obst->setPolPointsSize(3);
    obj->setSize(size/2);
    // just keep parent color
    obj->setColor(color);
    PEngine->objContainer.push_back(obj);
    k++;
  }
}

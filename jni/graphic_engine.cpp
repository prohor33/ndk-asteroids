#include "graphic_engine.h"
#include "physics_engine.h"
#include "bullet.h"
#include "obstacle.h"
#include "space_ship.h"
#include "main.h"

void GraphicEngine::renderFrame() {
  vector<shared_ptr<SpaceObject> >::iterator cii;
  for( cii=PEngine->objContainer.begin(); cii!=PEngine->objContainer.end(); ++cii )
    drawObj((*cii));
  return;
}

void GraphicEngine::drawObj(shared_ptr<SpaceObject> obj) {
  GLfloat vertBullet[8] = {
      -0.5f, -0.5f,
      +0.5f, -0.5f,
      +0.5f, +0.5f,
      -0.5f, +0.5f
    };
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glTranslatef(obj->getPos().x(), obj->getPos().y(), 0);
  switch(obj->getObjType()) {
  case SpaceObject::BULLET:
    glColor4f(0.0f, 1.0f, 0.0f, 0.0f);
    break;
  case SpaceObject::OBSTACLE:
    glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
    break;
  case SpaceObject::SPACE_SHIP:
    glColor4f(0.0f, 0.0f, 1.0f, 0.0f);
    break;
  }
  glEnableClientState(GL_VERTEX_ARRAY);
  // TODO: switch again?
  // do we really need it?
  Obstacle* obstacle;
  switch(obj->getObjType()) {
  case SpaceObject::OBSTACLE:
    obstacle = static_cast<Obstacle*>(obj.get());
    __android_log_print(ANDROID_LOG_INFO, "Asteroids",
        "graphic=%i", obstacle->getPolPointsSize());
    glVertexPointer(2, GL_FLOAT, 0, obstacle->getPolPoints());
    glDrawArrays(GL_TRIANGLE_FAN, 0, obstacle->getPolPointsSize());
    break;
  case SpaceObject::SPACE_SHIP:
  case SpaceObject::BULLET:
    glScalef(obj->getSize().x(), obj->getSize().y(), 1);
    glVertexPointer(2, GL_FLOAT, 0, vertBullet);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    break;
  }
  glDisableClientState(GL_VERTEX_ARRAY);
  glPopMatrix();
  return;
}

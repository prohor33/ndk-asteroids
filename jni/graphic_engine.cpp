#include "graphic_engine.h"
#include "physics_engine.h"
#include "bullet.h"
#include "obstacle.h"
#include "space_ship.h"
#include "main.h"

void GraphicEngine::renderFrame() {
  vector<SpaceObject*>::iterator cii;
  for( cii=PEngine->objContainer.begin(); cii!=PEngine->objContainer.end(); ++cii )
    drawObj((*cii));
  return;
}

void GraphicEngine::drawObj(SpaceObject* obj) {
  GLfloat vertBullet[8] = {
      -0.5f, -0.5f,
      +0.5f, -0.5f,
      +0.5f, +0.5f,
      -0.5f, +0.5f
    };

  glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glTranslatef(obj->getPos().x(), obj->getPos().y(), 0);
  glScalef(obj->getSize().x(), obj->getSize().y(), 1);
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_FLOAT, 0, vertBullet);
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
  glDisableClientState(GL_VERTEX_ARRAY);
  glPopMatrix();
  return;
}

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
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glTranslatef(obj->getPos().x(), obj->getPos().y(), 0);
  Color c = obj->getColor();
  glColor4f(c.r(), c.g(), c.b(), c.a());
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_FLOAT, 0, obj->getPolPoints());
  glDrawArrays(GL_TRIANGLE_FAN, 0, obj->getPolPointsSize());
  glDisableClientState(GL_VERTEX_ARRAY);
  glPopMatrix();
  return;
}

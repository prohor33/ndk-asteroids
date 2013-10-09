#include "graphic_engine.h"
#include "physics_engine.h"
#include "bullet.h"
#include "obstacle.h"
#include "space_ship.h"
#include "main.h"
#include "game_logic.h"

void GraphicEngine::renderFrame() {
  vector<shared_ptr<SpaceObject> >::iterator cii;
  for( cii=PEngine->objContainer.begin(); cii!=PEngine->objContainer.end(); ++cii )
    drawObj((*cii));
  return;
}

// here we decide whether draw lines or polygons
#define DRAW_LINES

void GraphicEngine::drawObj(shared_ptr<SpaceObject> obj) {
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glTranslatef(obj->getPos().x(), obj->getPos().y(), 0);
  glRotatef(obj->getAngle()*180/PI, 0, 0, 1);
  Color c = obj->getColor();
  glColor4f(c.r(), c.g(), c.b(), c.a());
  glEnableClientState(GL_VERTEX_ARRAY);
#ifdef DRAW_LINES
  glLineWidth(4.0f);
  int first_point = 0;
  switch (obj->getObjType()) {
  case SpaceObject::OBSTACLE:
    if (dynamic_cast<Obstacle*>(obj.get())->getObstType() == Obstacle::WHOLE)
      first_point = 1;
    break;
  case SpaceObject::SPACE_SHIP:
  case SpaceObject::BONUS:
    first_point = 1;
    break;
  }
  glVertexPointer(2, GL_FLOAT, 0, obj->getPolPoints()+first_point*2);
  glDrawArrays(GL_LINE_STRIP, 0, obj->getPolPointsSize()-first_point);
#else
  glVertexPointer(2, GL_FLOAT, 0, obj->getPolPoints());
  glDrawArrays(GL_TRIANGLE_FAN, 0, obj->getPolPointsSize());
#endif
  glDisableClientState(GL_VERTEX_ARRAY);
  glPopMatrix();
  return;
}

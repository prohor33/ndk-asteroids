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
  glTranslatef(obj->p().x(), obj->p().y(), 0);
  glRotatef(obj->angle()*180/PI, 0, 0, 1);
  Color c = obj->color();
  glColor4f(c.r(), c.g(), c.b(), c.a());
  glEnableClientState(GL_VERTEX_ARRAY);
#ifdef DRAW_LINES
  glLineWidth(4.0f);
  int first_point = 0;
  switch (obj->obj_type()) {
  case SpaceObject::OBSTACLE:
    // TODO: fix the code structure
    if (((Obstacle*)(obj.get()))->obstacle_type() == Obstacle::WHOLE)
      first_point = 1;
//        first_point = 0;
    break;
  case SpaceObject::SPACE_SHIP:
  case SpaceObject::BONUS:
    first_point = 1;
//    first_point = 0;
    break;
  }
  glVertexPointer(2, GL_FLOAT, 0, obj->GetObjectPointsArray() + first_point * 2);
  glDrawArrays(GL_LINE_STRIP, 0, obj->GetObjectPointsArraySize() - first_point);
#else
  glVertexPointer(2, GL_FLOAT, 0, obj->GetObjectPointsArray());
  glDrawArrays(GL_TRIANGLE_FAN, 0, obj->GetObjectPointsArraySize());
#endif
  glDisableClientState(GL_VERTEX_ARRAY);
  glPopMatrix();
  return;
}

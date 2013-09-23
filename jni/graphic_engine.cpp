#include "graphic_engine.h"
#include "bullet.h"
#include "bullets_container.h"
#include "main.h"

void GraphicEngine::RenderFrame() {
  DrawBullets();
  return;
}

void GraphicEngine::DrawBullets() {
  // something like this

  GLfloat size = 5;
  GLfloat vertBullet[8];
  vertBullet[0] = -size/2;
  vertBullet[1] = -size/2;
  vertBullet[2] = +size/2;
  vertBullet[3] = -size/2;
  vertBullet[4] = +size/2;
  vertBullet[5] = +size/2;
  vertBullet[6] = -size/2;
  vertBullet[7] = +size/2;

  glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
  glMatrixMode(GL_PROJECTION);

  vector<Bullet*>::iterator cii;
  for( cii=BulletsCont->mBullets.begin(); cii!=BulletsCont->mBullets.end(); ++cii ) {
    glPushMatrix();
    glTranslatef((*cii)->getPos().x(), (*cii)->getPos().y(), 0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, vertBullet);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
  }

  return;
}

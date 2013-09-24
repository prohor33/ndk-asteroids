#include "graphic_engine.h"
#include "bullet.h"
#include "bullets_container.h"
#include "obstacle.h"
#include "obstacles_container.h"
#include "space_ship.h"
#include "main.h"

void GraphicEngine::RenderFrame() {
  DrawBullets();
  DrawObstacles();
  DrawSpaceShip();
  return;
}

void GraphicEngine::DrawBullets() {
  GLfloat vertBullet[8] = {
      -0.5f, -0.5f,
      +0.5f, -0.5f,
      +0.5f, +0.5f,
      -0.5f, +0.5f
    };

  glColor4f(1.0f, 0.0f, 0.0f, 0.0f);
  glMatrixMode(GL_PROJECTION);

  vector<Bullet*>::iterator cii;
  for( cii=BulletsCont->getMass().begin(); cii!=BulletsCont->getMass().end(); ++cii ) {
    glPushMatrix();
    glTranslatef((*cii)->getPos().x(), (*cii)->getPos().y(), 0);
    glScalef((*cii)->getSize().x(), (*cii)->getSize().y(), 1);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, vertBullet);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
  }

  return;
}

void GraphicEngine::DrawObstacles() {
  GLfloat vertBullet[8] = {
      -0.5f, -0.5f,
      +0.5f, -0.5f,
      +0.5f, +0.5f,
      -0.5f, +0.5f
    };

  glColor4f(0.0f, 1.0f, 0.0f, 0.0f);
  glMatrixMode(GL_PROJECTION);

  vector<Obstacle*>::iterator cii;
  for( cii=ObstCont->getMass().begin(); cii!=ObstCont->getMass().end(); ++cii ) {
    glPushMatrix();
    glTranslatef((*cii)->getPos().x(), (*cii)->getPos().y(), 0);
    glScalef((*cii)->getSize().x(), (*cii)->getSize().y(), 1);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, vertBullet);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
  }

  return;
}

void GraphicEngine::DrawSpaceShip() {
  GLfloat vertBullet[8] = {
      -0.5f, -0.5f,
      +0.5f, -0.5f,
      +0.5f, +0.5f,
      -0.5f, +0.5f
    };

  glColor4f(0.0f, 0.0f, 1.0f, 0.0f);
  glMatrixMode(GL_PROJECTION);

  glPushMatrix();
  glTranslatef(Ship->getPos().x(), Ship->getPos().y(), 0);
  glScalef(Ship->getSize().x(), Ship->getSize().y(), 1);
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_FLOAT, 0, vertBullet);
  glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
  glDisableClientState(GL_VERTEX_ARRAY);
  glPopMatrix();

  return;
}

#include "graphic_engine.h"
#include "bullet.h"
#include "bullets_container.h"
#include "main.h"
#include "gl_code.h"

void GraphicEngine::RenderFrame() {
  glClearColor( 50.0f/255.0f, 56.0f/255.0f, 73.0f/255.0f, 1.0f );
  checkGlError("glClearColor");
  glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  checkGlError("glClear");

  DrawBullets();
  return;
}

void GraphicEngine::DrawBullets() {
  // smth like this

  glUseProgram(gProgram);
  checkGlError("glUseProgram");

  GLfloat gTriangleBulletVertices[] = { 0.0f, 0.5f, -0.5f, -0.5f,
          0.5f, -0.5f };
  GLfloat gBulletSize = 0.05;
  vector<Bullet*>::iterator cii;
  for( cii=BulletsCont->mBullets.begin(); cii!=BulletsCont->mBullets.end(); ++cii ) {
    gTriangleBulletVertices[0] = (*cii)->getPos().x();
    gTriangleBulletVertices[1] = (*cii)->getPos().y()+gBulletSize;
    gTriangleBulletVertices[2] = (*cii)->getPos().x()-gBulletSize;
    gTriangleBulletVertices[3] = (*cii)->getPos().y()-gBulletSize;
    gTriangleBulletVertices[4] = (*cii)->getPos().x()+gBulletSize;
    gTriangleBulletVertices[5] = (*cii)->getPos().y()-gBulletSize;

    glVertexAttribPointer(gvPositionHandle, 2, GL_FLOAT, GL_FALSE, 0, gTriangleBulletVertices);
    checkGlError("glVertexAttribPointer");
    glEnableVertexAttribArray(gvPositionHandle);
    checkGlError("glEnableVertexAttribArray");
    glDrawArrays(GL_TRIANGLES, 0, 3);
    checkGlError("glDrawArrays");
  }
  return;
}

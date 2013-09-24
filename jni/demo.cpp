#include "main.h"
#include "app.h"
#include "graphic_engine.h"
#include "game_logic.h"

static long sStartTick = 0;
static long sTick = 0;

static void drawFadeQuad()
{
    static const GLfixed quadVertices[] = {
        -0x10000, -0x10000,
         0x10000, -0x10000,
        -0x10000,  0x10000,
         0x10000, -0x10000,
         0x10000,  0x10000,
        -0x10000,  0x10000
    };

        glDisable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_ZERO, GL_SRC_COLOR);
        glDisable(GL_LIGHTING);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glVertexPointer(2, GL_FIXED, 0, quadVertices);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glEnableClientState(GL_COLOR_ARRAY);

        glMatrixMode(GL_MODELVIEW);

        glEnable(GL_LIGHTING);
        glDisable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);

}

/* Following gluLookAt implementation is adapted from the
 * Mesa 3D Graphics library. http://www.mesa3d.org
 */
static void gluLookAt(GLfloat eyex, GLfloat eyey, GLfloat eyez,
                GLfloat centerx, GLfloat centery, GLfloat centerz,
                GLfloat upx, GLfloat upy, GLfloat upz)
{
    GLfloat m[16];
    GLfloat x[3], y[3], z[3];
    GLfloat mag;

    /* Make rotation matrix */

    /* Z vector */
    z[0] = eyex - centerx;
    z[1] = eyey - centery;
    z[2] = eyez - centerz;
    mag = (float)sqrt(z[0] * z[0] + z[1] * z[1] + z[2] * z[2]);
    if (mag) {      /* mpichler, 19950515 */
        z[0] /= mag;
        z[1] /= mag;
        z[2] /= mag;
    }

    /* Y vector */
    y[0] = upx;
    y[1] = upy;
    y[2] = upz;

    /* X vector = Y cross Z */
    x[0] = y[1] * z[2] - y[2] * z[1];
    x[1] = -y[0] * z[2] + y[2] * z[0];
    x[2] = y[0] * z[1] - y[1] * z[0];

    /* Recompute Y = Z cross X */
    y[0] = z[1] * x[2] - z[2] * x[1];
    y[1] = -z[0] * x[2] + z[2] * x[0];
    y[2] = z[0] * x[1] - z[1] * x[0];

    /* mpichler, 19950515 */
    /* cross product gives area of parallelogram, which is < 1.0 for
     * non-perpendicular unit-length vectors; so normalize x, y here
     */

    mag = (float)sqrt(x[0] * x[0] + x[1] * x[1] + x[2] * x[2]);
    if (mag) {
        x[0] /= mag;
        x[1] /= mag;
        x[2] /= mag;
    }

    mag = (float)sqrt(y[0] * y[0] + y[1] * y[1] + y[2] * y[2]);
    if (mag) {
        y[0] /= mag;
        y[1] /= mag;
        y[2] /= mag;
    }

#define M(row,col)  m[col*4+row]
    M(0, 0) = x[0];
    M(0, 1) = x[1];
    M(0, 2) = x[2];
    M(0, 3) = 0.0;
    M(1, 0) = y[0];
    M(1, 1) = y[1];
    M(1, 2) = y[2];
    M(1, 3) = 0.0;
    M(2, 0) = z[0];
    M(2, 1) = z[1];
    M(2, 2) = z[2];
    M(2, 3) = 0.0;
    M(3, 0) = 0.0;
    M(3, 1) = 0.0;
    M(3, 2) = 0.0;
    M(3, 3) = 1.0;
#undef M
    {
        int a;
        GLfixed fixedM[16];
        for (a = 0; a < 16; ++a)
            fixedM[a] = (GLfixed)(m[a] * 65536);
        glMultMatrixx(fixedM);
    }

    /* Translate Eye to Origin */
    glTranslatex((GLfixed)(-eyex * 65536),
                 (GLfixed)(-eyey * 65536),
                 (GLfixed)(-eyez * 65536));
}

// Called from the app framework.
void appInit()  {
  GLogic->Initialize();
}

// Called from the app framework.
void appDeinit()  {
  GLogic->DeInitialize();
}

static void prepareFrame(int width, int height) {
  glViewport(0, 0, width, height);

  glClearColorx((GLfixed)(0.1f * 65536),
                (GLfixed)(0.2f * 65536),
                (GLfixed)(0.3f * 65536), 0x10000);
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  float aspect = (float)height / width;
  glFrustumf(-50, 50, -aspect*50, aspect*50, 50, 100);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(0, 0, 50, 0, 0, 0, 0, 1, 0);
}

// Called from the app framework.
/* The tick is current time in milliseconds, width and height
 * are the image dimensions to be rendered.
 */
void appRender (long tick, int width, int height)  {
  if (sStartTick == 0)
    sStartTick = tick;
  if (!gAppAlive)
    return;

  // Actual tick value is "blurred" a little bit.
  sTick = (sTick + tick - sStartTick) >> 1;
  sStartTick = tick;

  // Prepare OpenGL ES for rendering of the frame.
  prepareFrame(width, height);

  GLogic->MainGameLoop((double)sTick/1000);
}

void appResize(int width, int height) {
  float aspect = (float)height / width;
  GLogic->setScreenSize(Vec2(100, aspect*100));
}

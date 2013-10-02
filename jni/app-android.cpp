#include <jni.h>
#include <sys/time.h>
#include <time.h>
#include <android/log.h>
#include <stdint.h>
#include "app.h"
#include "game_logic.h"

int   gAppAlive   = 1;

static int  sWindowWidth  = 320;
static int  sWindowHeight = 480;
static int  sDemoStopped  = 0;
static long sTimeOffset   = 0;
static int  sTimeOffsetInit = 0;
static long sTimeStopped  = 0;

extern "C"
{

static long
_getTime(void)
{
    struct timeval  now;

    gettimeofday(&now, NULL);
    return (long)(now.tv_sec*1000 + now.tv_usec/1000);
}

/* Call to initialize the graphics state */
void
Java_com_example_SanAngeles_DemoRenderer_nativeInit( JNIEnv*  env )
{
    appInit();
    __android_log_print(ANDROID_LOG_INFO, "Asteroids", "Init");
    gAppAlive  = 1;
}

void
Java_com_example_SanAngeles_DemoRenderer_nativeResize( JNIEnv*  env, jobject  thiz, jint w, jint h )
{
    sWindowWidth  = w;
    sWindowHeight = h;
    __android_log_print(ANDROID_LOG_INFO, "Asteroids", "resize w=%d h=%d", w, h);
    appResize(w, h);
}

/* Call to finalize the graphics state */
void
Java_com_example_SanAngeles_DemoActivity_nativeDone( JNIEnv*  env )
{
    appDeinit();
    __android_log_print(ANDROID_LOG_INFO, "Asteroids", "Done");
}

/* This is called to indicate to the render loop that it should
 * stop as soon as possible.
 */

void _pause()
{
  /* we paused the animation, so store the current
   * time in sTimeStopped for future nativeRender calls */
    sDemoStopped = 1;
    sTimeStopped = _getTime();
    __android_log_print(ANDROID_LOG_INFO, "Asteroids", "Paused!");
}

void _resume()
{
  /* we resumed the animation, so adjust the time offset
   * to take care of the pause interval. */
    sDemoStopped = 0;
    sTimeOffset -= _getTime() - sTimeStopped;
}


void
Java_com_example_SanAngeles_DemoGLSurfaceView_nativeTogglePauseResume( JNIEnv*  env )
{
    sDemoStopped = !sDemoStopped;
    if (sDemoStopped)
        _pause();
    else
        _resume();
}

void
Java_com_example_SanAngeles_DemoGLSurfaceView_nativePause( JNIEnv*  env )
{
    if (!GLogic->getPaused())
        _pause();
    __android_log_print(ANDROID_LOG_INFO, "Asteroids", "Pause");
}

void
Java_com_example_SanAngeles_DemoGLSurfaceView_nativeResume( JNIEnv*  env )
{
    if (!GLogic->getPaused())
      _resume();
    __android_log_print(ANDROID_LOG_INFO, "Asteroids", "Resume");
}

void
Java_com_example_SanAngeles_DemoGLSurfaceView_nativeTouch( JNIEnv*  env, jobject  thiz, jfloat x, jfloat y )
{
    __android_log_print(ANDROID_LOG_INFO, "Asteroids", "Touch x=%f y=%f", x, y);
    appTouch(x, y);
}

void
Java_com_example_SanAngeles_DemoGLSurfaceView_nativeMove( JNIEnv*  env, jobject  thiz, jfloat x, jfloat y )
{
    appMove(x, y);
}

void
Java_com_example_SanAngeles_DemoGLSurfaceView_nativeUp( JNIEnv*  env, jobject  thiz, jfloat x, jfloat y )
{
    appUp(x, y);
}

/* Call to render the next GL frame */
void
Java_com_example_SanAngeles_DemoRenderer_nativeRender( JNIEnv*  env )
{
    long   curTime;

    /* NOTE: if sDemoStopped is TRUE, then we re-render the same frame
     *       on each iteration.
     */
    if (sDemoStopped) {
        curTime = sTimeStopped + sTimeOffset;
    } else {
        curTime = _getTime() + sTimeOffset;
        if (sTimeOffsetInit == 0) {
            sTimeOffsetInit = 1;
            sTimeOffset     = -curTime;
            curTime         = 0;
        }
    }

    //__android_log_print(ANDROID_LOG_INFO, "Asteroids", "curTime=%ld", curTime);

    appRender(curTime, sWindowWidth, sWindowHeight);
}

} // extern "C" end

#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED


#ifdef __cplusplus
extern "C" {
#endif

// The simple framework expects the application code to define these functions.
extern void appInit();
extern void appDeinit();
extern void appRender(long tick, int width, int height);
extern void appResize(int width, int height);
extern void appTouch(float x, float y);
extern void appMove(float x, float y);
extern void appUp(float x, float y);

void _pause();
void _resume();
/* Value is non-zero when application is alive, and 0 when it is closing.
 * Defined by the application framework.
 */
extern int gAppAlive;


#ifdef __cplusplus
}
#endif


#endif // !APP_H_INCLUDED

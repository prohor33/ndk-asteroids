#ifndef GL_CODE_H_
#define GL_CODE_H_

#define  LOG_TAG    "libgl2jni"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#include "main.h"

void printGLString(const char *name, GLenum s);
void checkGlError(const char* op);
GLuint loadShader(GLenum shaderType, const char* pSource);
GLuint createProgram(const char* pVertexSource, const char* pFragmentSource);

// TODO: do smth with this
// TODO: find out what extern actually do =)
extern GLuint gProgram;
extern GLuint gvPositionHandle;

#endif /* GL_CODE_H_ */

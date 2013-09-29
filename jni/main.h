#ifndef _JNI_MAIN_H__
#define _JNI_MAIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <assert.h>
#include <vector>

#include <GLES/gl.h>
#include <android/log.h>

#include <boost/shared_ptr.hpp>

#include "vec2.h"

#undef PI
#define PI 3.1415926535897932f

using namespace std;

struct bad_cast : public exception {bad_cast operator()(){}};

using namespace boost;

#endif	// _JNI_MAIN_H__

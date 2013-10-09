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

// for polygon intersects
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/polygon/polygon.hpp>

#include "vec2.h"

#undef PI
#define PI 3.1415926535897932f

using namespace std;

struct bad_cast : public exception {bad_cast operator()(){}};

class Color {
public:
  Color() {};
  Color(float r, float g, float b, float a) :
    _r(r), _g(g), _b(b), _a(a) {};
  float r() { return _r; };
  float g() { return _g; };
  float b() { return _b; };
  float a() { return _a; };
private:
  float _r, _g, _b, _a;
};

using namespace boost;

#endif	// _JNI_MAIN_H__

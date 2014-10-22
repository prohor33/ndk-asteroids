#pragma once

//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//#include <float.h>
//#include <assert.h>
//#include <vector>
//#include <memory>
//
//#include <GLES/gl.h>
//#include <android/log.h>
//struct bad_cast : public exception {bad_cast operator()(){}};

#include "vec2.h"

namespace utils {

     #undef PI
     #define PI 3.1415926535897932f

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

    Vec2 PixelsToNormal(Vec2 pix_p);
    float RandMinusXtoX(float x = 1.0f);
    float Rand0toX(float x = 1.0f);
    bool RandOneOf(int x);
    Vec2 RotateVector(Vec2 v, float angle);
 }
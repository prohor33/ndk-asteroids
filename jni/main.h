#ifndef _JNI_MAIN_H__
#define _JNI_MAIN_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <assert.h>
#include <vector>

#include <GLES/gl.h>

#undef PI
#define PI 3.1415926535897932f

using namespace std;

class Vec2 {
public:
	Vec2() : x_(0), y_(0) {};
	Vec2( double x, double y ) : x_(x), y_(y) {};
	Vec2( Vec2 &v ){
		x_ = v.x();
		y_ = v.y();
	};
	double& x() { return x_; }
	double& y() { return y_; }
private:
	double x_;
	double y_;
};

#endif	// _JNI_MAIN_H__

#ifndef _JNI_MAIN_H__
#define _JNI_MAIN_H__

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>

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

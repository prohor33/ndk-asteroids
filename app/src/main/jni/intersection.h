#pragma once

#include "vec2.h"

class Object;

namespace intersection {

#define MIN_FLOAT 1e-8

struct LineSegment {
	LineSegment() {};
	LineSegment(Vec2 s_tmp, Vec2 e_tmp) : s(s_tmp), e(e_tmp) {}
	Vec2 s;
	Vec2 e;
};

struct Line {
	Line() : a(0.0f), b(0.0f) {};
	Line(float a_tmp, float b_tmp) : a(a_tmp), b(b_tmp) {};
	float a;
	float b;
};

bool CheckObjectIntersection(Object* obj1, Object* obj2);

}
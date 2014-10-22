#pragma once

#include "vec2.h"
#include <vector>


class Object;

class Physics {
public:
    static bool CheckCollision(Object* obj1, Object* obj2);
    static void PreventOutOfBorders(Vec2& p, const std::vector<Vec2>& polygon);
    static bool PointApproxInsidePolygon(const Vec2& p, const std::vector<Vec2>& polygon);
    static bool CheckOutOfBorders(const Vec2& p);
};


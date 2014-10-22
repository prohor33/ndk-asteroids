#pragma once

#include "vec2.h"
#include <vector>


class Object;

class Physics {
public:
    static bool CheckCollision(Object* obj1, Object* obj2);
    static void PreventOutOfBorders(Vec2& p, const std::vector<Vec2>& polygon);
    static bool PointApproxInsidePolygon(const Vec2& p, Object* obj);
    static bool CheckOutOfBorders(const Vec2& p);
    static void FindManMax(Vec2& min, Vec2& max, Object* obj);
    static bool CheckNoCollisionFast(Object* obj1, Object* obj2);
};


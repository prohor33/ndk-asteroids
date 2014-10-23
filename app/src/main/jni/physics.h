#pragma once

#include "vec2.h"
#include <vector>


class Object;

namespace physics {
    void PreventOutOfBorders(Vec2& p, const std::vector<Vec2>& polygon);
    bool PointApproxInsidePolygon(const Vec2& p, Object* obj);
    bool CheckOutOfBorders(const Vec2& p);
    void FindManMax(Vec2& min, Vec2& max, Object* obj);
    bool CheckNoCollisionFast(Object* obj1, Object* obj2);
    void RotateVector(Vec2& p, float angle);
};


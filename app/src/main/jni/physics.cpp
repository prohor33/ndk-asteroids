#include "physics.h"
#include "object.h"
#include "game.h"
#include <stdlib.h>
#include <android/log.h>

bool Physics::CheckCollision(Object* obj1, Object* obj2) {
    // TODO: to implement
    return false;
}

void Physics::PreventOutOfBorders(Vec2& pos, const std::vector<Vec2>& points) {
    // TODO: to implement
}

// TODO: make it more precisely
bool Physics::PointApproxInsidePolygon(const Vec2& pos, const std::vector<Vec2>& polygon,
    Vec2 polygon_shift) {

    Vec2 min_p, max_p;
    Physics::FindManMax(min_p, max_p, polygon);
    Vec2 p = pos - polygon_shift;
    if (p.x() < min_p.x() ||
        p.y() < min_p.y() ||
        p.x() > max_p.x() ||
        p.y() > max_p.y()) {

        return false;
    }
    return true;
}

void Physics::FindManMax(Vec2& min_p, Vec2& max_p, const std::vector<Vec2>& polygon) {
    if (!polygon.size()) {
        __android_log_print(ANDROID_LOG_INFO, "Asteroids",
         "Error: in FindManMax() empty inout");
        return;
    }
    min_p = polygon[0];
    max_p = polygon[0];
    for (auto point : polygon) {
        if (point.x() < min_p.x())
            min_p.x() = point.x();
        if (point.y() < min_p.y())
            min_p.y() = point.y();

        if (point.x() > max_p.x())
            max_p.x() = point.x();
        if (point.y() > max_p.y())
            max_p.y() = point.y();
    }
}

bool Physics::CheckOutOfBorders(const Vec2& p) {
    const Vec2& scr_half_size = Game::Instance()->GetHalfScreenSize();
    const int dead_band = 100;
    if (abs(p.x()) > (scr_half_size.x() + dead_band) ||
        abs(p.y()) > (scr_half_size.y() + dead_band)) {
        return true;
    }
    return false;
}


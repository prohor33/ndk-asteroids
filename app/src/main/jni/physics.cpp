#include "physics.h"
#include "object.h"
#include "game.h"
#include <stdlib.h>
#include <android/log.h>

namespace physics {

bool CheckNoCollisionFast(Object* obj1, Object* obj2) {
    Vec2 min_p1, max_p1;
    physics::FindManMax(min_p1, max_p1, obj1);
    Vec2 min_p2, max_p2;
    physics::FindManMax(min_p2, max_p2, obj2);
    if (min_p1.x() < max_p2.x() &&
        max_p1.x() > min_p2.x() &&
        min_p1.y() < max_p2.y() &&
        max_p1.y() > min_p2.y()) {

            return false;
    }
    return true;
}

void PreventOutOfBorders(Vec2& pos, const std::vector<Vec2>& points) {
    // TODO: to implement
}

// TODO: make it more precisely
bool PointApproxInsidePolygon(const Vec2& p, Object* obj) {

    Vec2 min_p, max_p;
    physics::FindManMax(min_p, max_p, obj);
    if (p.x() < min_p.x() ||
        p.y() < min_p.y() ||
        p.x() > max_p.x() ||
        p.y() > max_p.y()) {

        return false;
    }
    return true;
}

void FindManMax(Vec2& min_p, Vec2& max_p, Object* obj) {
    if (!obj) {
         __android_log_print(ANDROID_LOG_INFO, "Asteroids",
          "Error: in FindManMax() null input");
         return;
     }
    const std::vector<Vec2>& polygon = obj->object_points();
    if (!polygon.size()) {
        __android_log_print(ANDROID_LOG_INFO, "Asteroids",
         "Error: in FindManMax() empty input");
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
    min_p += obj->p();
    max_p += obj->p();
}

bool CheckOutOfBorders(const Vec2& p) {
    const Vec2& scr_half_size = Game::Instance()->GetHalfScreenSize();
    const int dead_band = 100;
    if (abs(p.x()) > (scr_half_size.x() + dead_band) ||
        abs(p.y()) > (scr_half_size.y() + dead_band)) {
        return true;
    }
    return false;
}

void RotateVector(Vec2& p, float angle) {
  float alpha = 0.0f;
  // compute alpha
  if (p.x() == 0) {
    // vector can be vertical
    // so dividing by zero will occur
    if (p.y() > 0)
      alpha = PI/2;
    else
      alpha = -PI/2;
  }
  else {
    alpha = atan(p.y() / p.x());
    if (p.x() < 0)
      alpha += PI;
  }
  alpha += angle;
  float rad = sqrt(p.x() * p.x() + p.y() * p.y());
  p.x() = rad * cos(alpha);
  p.y() = rad * sin(alpha);
}

}

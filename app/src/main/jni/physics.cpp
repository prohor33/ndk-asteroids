#include "physics.h"
#include "object.h"
#include "game.h"
#include <stdlib.h>

bool Physics::CheckCollision(Object* obj1, Object* obj2) {
    // TODO: to implement
    return false;
}

void Physics::PreventOutOfBorders(Vec2& pos, const std::vector<Vec2>& points) {
    // TODO: to implement
}

// TODO: make it more precisely
bool Physics::PointApproxInsidePolygon(const Vec2& p, const std::vector<Vec2>& polygon) {
    // TODO: to implement
    return true;
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
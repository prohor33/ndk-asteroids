#include "input.h"
#include "physics.h"
#include "game.h"
#include "ship.h"

Input::Input() :
    dragging_(false)
{};

void Input::Handle(InputType type, Vec2 p) {
    if (Game::Instance()->paused())
        return; // do not respond while on pause

    Ship* ship = Game::Instance()->obj_container()->GetShip();
    if (!ship)
        return;

    switch (type) {
        case DOWN: {
            // check whether it's start of dragging
            Vec2 touch_pos(p.x(), p.y());
            if (Physics::PointApproxInsidePolygon(touch_pos, ship->object_points(), ship->p())) {
                dragging_ = true;
                start_delta_ = ship->p() - p;
                break;
            }
            Physics::PreventOutOfBorders(p, ship->object_points());
            ship->GoTo(p);
            break;
        }
        case UP: {
            dragging_ = false;
            break;
        }
        case DRAG: {
            if (dragging_) {
                Vec2 dragging_pos = p + start_delta_;
                Physics::PreventOutOfBorders(dragging_pos, ship->object_points());
                ship->set_p(dragging_pos);
            }
            break;
        }
    }
}

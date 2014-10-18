#include "space_ship.h"
#include "game_logic.h"
#include "physics_engine.h"

bool SpaceShip::need_reinitializing = false;

SpaceShip::SpaceShip() :
    SpaceObject(Vec2(0.0f, -GLogic->getHScrSize().y() + 20.0f),
    Vec2(),
    Vec2(20.0f, 25.0f),
    50.0f,
    SpaceObject::SPACE_SHIP),
    delta_fire_t_(0.0f),
    have_target_(false),
    dragging_(false),
    triple_fire_(false) {

    // now, let's draw spaceship
    // this is counter clockwise order
    std::vector<Vec2> tmp_points;
    tmp_points.push_back(Vec2(30, 22));
    tmp_points.push_back(Vec2(30, 77));
    tmp_points.push_back(Vec2(20, 67));
    tmp_points.push_back(Vec2(20, 50));
    tmp_points.push_back(Vec2(0, 30));
    tmp_points.push_back(Vec2(0, 0));
    tmp_points.push_back(Vec2(30, 9));
    tmp_points.push_back(Vec2(60, 0));
    tmp_points.push_back(Vec2(60, 30));
    tmp_points.push_back(Vec2(40, 50));
    tmp_points.push_back(Vec2(40, 67));
    tmp_points.push_back(Vec2(30, 77));
    int size_x = 60;
    int size_y = 77;
    for (int i = 0; i < tmp_points.size(); i++) {
        AddObjectPoint(Vec2(tmp_points[i].x() / size_x * size_.x() - size_.x()/2,
            tmp_points[i].y() / size_y * size_.y() - size_.y()/2));
    }
    color_ = Color(0.0f, 0.0f, 1.0f, 0.0f);
};

void SpaceShip::Fire() {
    PEngine->AddObject(p_ + Vec2(0.0f, size_.y() / 2.0f), Vec2(0.0f, 70.0f), SpaceObject::BULLET);
    if (triple_fire_) {
        PEngine->AddObject(p_ + Vec2(-size_.x() / 2.0f, 0.0f), Vec2(0.0f, 70.0f), SpaceObject::BULLET);
        PEngine->AddObject(p_ + Vec2(size_.x() / 2.0f, 0.0f), Vec2(0.0f, 70.0f), SpaceObject::BULLET);
    }
    return;
}

bool SpaceShip::Update(float dt) {
    if (!this->SpaceObject::Update(dt))
        return false;
    delta_fire_t_ += dt;
    if (delta_fire_t_ > 0.3f) {
        delta_fire_t_ = 0.0f;
        Fire();
    }
    // check whether ship reach
    // the target
    if (have_target_) {
        if ((target_p_ - p_).x() * v_.x() < 0.0f || (target_p_ - p_).y() * v_.y() < 0.0f) {
            have_target_ = false;
            v_ = Vec2();
        }
    }
    // check if triple fire is finished
    if (triple_fire_) {
        delta_triple_fire_t_ += dt;
        const float max_delta_triple_fire_t = 18;
        if (delta_triple_fire_t_ > max_delta_triple_fire_t)
          triple_fire_ = false;
    }
    return true;
}

void SpaceShip::Collide(ObjectType with_obj) {
    switch (with_obj) {
    case SpaceObject::OBSTACLE:
        GLogic->gameOver();
        break;
    }
}

void SpaceShip::GoTo(Vec2 target_p) {
    target_p_ = target_p;
    Vec2 delta = target_p_ - p_;
    delta.normalize();
    v_ = delta * velocity_;
    have_target_ = true;
}

void SpaceShip::PreventOutOfBorders(Vec2& pos) {
  if (pos.x() > GLogic->getHScrSize().x() - size_.x()/2)
    pos.x() = GLogic->getHScrSize().x() - size_.x()/2;
  if (pos.x() < -GLogic->getHScrSize().x() + size_.x()/2)
    pos.x() = -GLogic->getHScrSize().x() + size_.x()/2;
  if (pos.y() > GLogic->getHScrSize().y() - size_.y()/2)
    pos.y() = GLogic->getHScrSize().y() - size_.y()/2;
  if (pos.y() < -GLogic->getHScrSize().y() + size_.y()/2)
    pos.y() = -GLogic->getHScrSize().y() + size_.y()/2;
}

void SpaceShip::EventHandler(EventType event_type, Vec2 pos) {
    if (GLogic->getPaused())
        return;
    Vec2 dragging_pos;
    float down_touch_area = 10.0f;
    switch (event_type) {
    case DOWN:
        // check whether it's start of dragging
        if (pos.x() > p_.x() - size_.x() / 2.0f &&
            pos.x() < p_.x() + size_.x() / 2.0f &&
            pos.y() > p_.y() - size_.y() / 2.0f - down_touch_area &&
            pos.y() < p_.y() + size_.y() / 2.0f - down_touch_area / 2.0f) {

            dragging_ = true;
            have_target_ = false;
            v_ = Vec2();
            delta_dragging_ = p_ - pos;
            break;
        }
        PreventOutOfBorders(pos);
        GoTo(pos);
        break;
    case UP:
        dragging_ = false;
        break;
    case DRAG:
        if (dragging_) {
            dragging_pos = pos + delta_dragging_;
            PreventOutOfBorders(dragging_pos);
            set_p(dragging_pos);
        }
        break;
    }
}

void SpaceShip::TurnOnTripleFire() {
  triple_fire_ = true;
  delta_triple_fire_t_ = 0.0f;
}

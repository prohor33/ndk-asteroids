#include "ship.h"
#include "game.h"
#include "physics.h"
#include "utils.h"
#include "bullet.h"
#include <android/log.h>


Ship::Ship() :
    Object(Object::SHIP, Vec2(0.0f, -Game::Instance()->GetHalfScreenSize().y() + 20.0f)),
    delta_fire_t_(0.0f),
    have_target_(false),
    triple_fire_(false) {

    // now, let's draw spaceship
    // this is counter clockwise order
    std::vector<Vec2> tmp_points;
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
    int need_size_x = 25;
    int need_size_y = 30;
    for (int i = 0; i < tmp_points.size(); i++) {
        AddObjectPoint(Vec2(tmp_points[i].x() / size_x * need_size_x - need_size_x / 2,
            tmp_points[i].y() / size_y * need_size_y - need_size_y / 2));
    }
    color_ = utils::Color(0.0f, 0.0f, 1.0f, 0.0f);
};

void Ship::Fire() {
    // TODO: fix hard code
    const float fire_shift_x = 10.0f;
    const float fire_shift_y = 15.0f;
    Game::Instance()->obj_container()->AddObject(new Bullet(p_ + Vec2(0.0f, fire_shift_y), Vec2(0.0f, 70.0f)));
    if (triple_fire_) {
        Game::Instance()->obj_container()->AddObject(new Bullet(p_ + Vec2(-fire_shift_x, 0.0f), Vec2(0.0f, 70.0f)));
        Game::Instance()->obj_container()->AddObject(new Bullet(p_ + Vec2(fire_shift_x / 2.0f, 0.0f), Vec2(0.0f, 70.0f)));
    }
    return;
}

void Ship::Update(float dt, bool& delete_obj) {
    this->Object::Update(dt, delete_obj);
    if (delete_obj)
        return;
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
}

void Ship::Collide(Object* with_obj) {
    switch (with_obj->type()) {
    case Object::OBSTACLE:
        Game::Instance()->GameOver();
        break;
    }
}

void Ship::GoTo(Vec2 target_p) {
    target_p_ = target_p;
    Vec2 delta = target_p_ - p_;
    delta.normalize();
    v_ = delta * 50.0f; // TODO: fix velocity
    have_target_ = true;
}

void Ship::TurnOnTripleFire() {
  triple_fire_ = true;
  delta_triple_fire_t_ = 0.0f;
}

#include "obstacle.h"
#include "object.h"
#include "game.h"
#include "physics.h"
#include "ship.h"
#include "utils.h"
#include <stdlib.h>

Obstacle::Obstacle(ObstacleType obstacle_type, Vec2 p) :
    Object(Object::OBSTACLE, p),
    obstacle_type_(obstacle_type),
    have_bonus_(false) {

    if (obstacle_type_ == COMPOUND) {
        GenerateCompound();
    }
};

void Obstacle::GenerateCompound() {
    // random position and velocity
    p_ = Vec2(Game::Instance()->GetHalfScreenSize().x() * (rand() % 100 - 50.0f) / 50.0f,
        Game::Instance()->GetHalfScreenSize().y() + 10.0f);
    float v_y[] = { -10.0f, -15.0f, -20.0f, -22.0f, -24.0f };
    v_ = Vec2(utils::RandMinusXtoX(4.0f),
        (0.7f + utils::Rand0toX(0.3f)) * v_y[Game::Instance()->level()]);

    // random polygon
    const float average_obstacle_size = 10.0f;
    float size = average_obstacle_size * (1.0f + utils::RandMinusXtoX(0.3f));
    float size_ratio = 1.0 + utils::RandMinusXtoX(0.1f);
    const float min_rad = size * size_ratio;
    const float max_rad = size * size_ratio;
    const int points_quantity = rand() % 3 + 7;
    float start_rand = min_rad + (max_rad-min_rad) * utils::Rand0toX();

    // add points (counterclockwise order)
    float alpha = 0;
    for (int k = 0; k < points_quantity; k++) {
        float rand_rad = min_rad + (max_rad - min_rad) * utils::Rand0toX();
        // first and last radius must be equal
        if (k == 0 || k == points_quantity - 1 ) {
            rand_rad = start_rand;
            alpha = 0;
        }
        AddObjectPoint(Vec2(rand_rad * cos(alpha), rand_rad * sin(alpha)));
        alpha += 2.0f * PI / points_quantity;
    }

    // random color and angle velocity
    color_ = utils::Color(0.1f + utils::Rand0toX(0.9f),
                          0.1f + utils::Rand0toX(0.9f),
                          0.1f + utils::Rand0toX(0.9f), 0.0f);
    angle_velocity_ = utils::RandMinusXtoX(0.2f);
    have_bonus_ = utils::RandOneOf(10);
}

void Obstacle::Update(float dt, bool& delete_obj) {
    Object::Update(dt, delete_obj);
}

void Obstacle::Collide(Object* with_obj) {
    switch (with_obj->type()) {
    case Object::BULLET:
        if (obstacle_type_ == COMPOUND) {
            BlowUp();
        } else if (obstacle_type_ == PIECE) {
            DeleteMyself();
        }
        break;
    }
}

void Obstacle::BlowUp() {
    // create a bunch of new obstacles (triangles)
    float alpha = 0;
    for (int k = 0; k < (object_points_.size() - 1); k++) {
        Vec2 p0;
        Vec2 p1 = GetObjectPoint(k);
        Vec2 p2 = GetObjectPoint(k + 1);
        p1 = utils::RotateVector(p1, angle_);
        p2 = utils::RotateVector(p2, angle_);
        Vec2 center = (p1 + p2) / 2.0f;
        // move triangle
        p0 -= center;
        p1 -= center;
        p2 -= center;
        center += p_;
        Obstacle* obj = new Obstacle(PIECE, center);
        obj->AddObjectPoint(p0);
        obj->AddObjectPoint(p1);
        obj->AddObjectPoint(p2);
        obj->AddObjectPoint(p0);

        const float angle_tmp = alpha + angle_;
        const float blow_up_velocity = 5.0f;
        Vec2 blow_up_vel(blow_up_velocity * cos(angle_tmp),
                         blow_up_velocity * sin(angle_tmp));
        obj->set_v(v_ + blow_up_vel);
        obj->set_color(color_);
        Game::Instance()->obj_container()->AddObject(obj);

        alpha += 2.0f * PI / object_points_.size();
    }

    if (have_bonus_)
        Game::Instance()->obj_container()->AddObject(new Bonus(p_));

    DeleteMyself();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Bonus::Bonus(Vec2 p) :
    Object(Object::BONUS, p),
    lifetime_(0.0f) {

    int half_size_x = 60;
    int half_size_y = 77;
    // add points (counter clockwise order)
    const float size = 30.0f;
    const float half_size = size / 2.0f;
    AddObjectPoint(Vec2(-half_size, -half_size));
    AddObjectPoint(Vec2(half_size, -half_size));
    AddObjectPoint(Vec2(half_size, half_size));
    AddObjectPoint(Vec2(-half_size, half_size));
    AddObjectPoint(Vec2(-half_size, -half_size));

    color_ = utils::Color(43.0f/255.0f, 194.0f/255.0f, 164.0f/255.0f, 0.0f);
    angle_velocity_ = PI;
}

void Bonus::Collide(Object* with_obj) {
    switch (with_obj->type()) {
    case Object::SHIP:
        Game::Instance()->obj_container()->GetShip()->TurnOnTripleFire();
        DeleteMyself();
        break;
    }
}

void Bonus::Update(float dt, bool& delete_obj) {
    Object::Update(dt, delete_obj);
    lifetime_ += dt;
    const float max_bonus_time = 15.0f;
    if (lifetime_ > max_bonus_time)
        delete_obj = true;
}

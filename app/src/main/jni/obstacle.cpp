#include "obstacle.h"
#include "object.h"
#include "game.h"
#include "physics.h"
#include "ship.h"
#include "utils.h"
#include <stdlib.h>

Obstacle::Obstacle() :
    Object(Object::OBSTACLE),
    obstacle_type_(WHOLE),
    have_bonus_(false) {

    p_ = Vec2(Game::Instance()->GetHalfScreenSize().x() * (rand() % 100 - 50.0f) / 50.0f,
        Game::Instance()->GetHalfScreenSize().y() + 10.0f);
    float v_y[] = { -10.0f, -15.0f, -20.0f, -22.0f, -24.0f };
    v_ = Vec2((rand() % 100 - 50.0f) / 50.0f * 4.0f,
        (rand() % 30 + 70.0f) / 100.0 * v_y[Game::Instance()->level()]);

    // here we generate random polygon
    const float average_obstacle_size = 30.0f;
    float size = average_obstacle_size * (1.0f + (rand() % 100 - 50.0f) / 50.0f * 0.3f);
    float size_ratio = 0.5 + (rand() % 100 - 50.0f) / 50.0f * 0.1f;
    float min_rad = size * (1.0f - size_ratio) / 2.0f;
    float max_rad = size * (1.0f + size_ratio) / 2.0f;
    int points_quantity = rand() % 3 + 7; // real quantity of pieces is points_quantity - 2
    float alpha = 0;
    float start_rand = min_rad + (max_rad-min_rad) * (rand() % 100) / 100.0f;

    // this is counterclockwise order too
    AddObjectPoint(Vec2(0.0f, 0.0f));   // start point
    for (int k = 1; k <= points_quantity - 1; k++) {
        float rand_rad = min_rad + (max_rad-min_rad) * (rand() % 100) / 100.0f;
        // make the polygon to be closed
        // first and last radius must be equal
        if (k == 1 || k == points_quantity - 1 ) {
            rand_rad = start_rand;
            alpha = 0;
        }
        AddObjectPoint(Vec2(rand_rad * cos(alpha), rand_rad * sin(alpha)));
        alpha += 2 * PI / (points_quantity - 2);
    }
    // generate random obstacles color and angle velocity
    color_ = utils::Color((rand() % 90 + 10.0f) / 100.0f,
        (rand() % 90 + 10.0f) / 100.0f, (rand() % 90 + 10.0f) / 100.0f, 0.0f);
    angle_velocity_ = (rand() % 100 - 50.0f) / 50.0f * 0.2f;
    have_bonus_ = rand() % 10 == 0;
};

void Obstacle::Update(float dt, bool& delete_obj) {
    Object::Update(dt, delete_obj);
}

void Obstacle::Collide(Object* with_obj) {
  if (with_obj->type() == Object::BULLET)
    BlowUp();
}

// the most complicated function in that project =)
void Obstacle::BlowUp() {
    if (obstacle_type_ == PIECE)
        return;
    int k = 2;  // because k=0 and k=1 is Vec2(0,0) point
    // and we use [k*2-2] in this loop
    float vel = 5;  // velocity of expansion
    float angle_now;
    float rand_rad;
    Vec2 delta_p;
    // create a bunch of new obstacles (triangles)
    for (float alpha = 2.0f * PI / (object_points_array().size() - 2); alpha <= 2.0f * PI;
        alpha += 2.0f * PI / (object_points_array().size() - 2)) {
        // angle considering rotation
        angle_now = alpha + angle_;
        Obstacle* obj = new Obstacle();
        // delta_p is vector between position of new triangle
        // and position of an old obj
        const float obstacle_size = 30.0f;  // TODO: fix this
        delta_p = Vec2(obstacle_size / 4 * cos(angle_now),
            obstacle_size / 4 * sin(angle_now));
        obj->set_p(p_ + delta_p);
        obj->set_v(v_ + Vec2(vel * cos(angle_now),
            vel * sin(angle_now)));
        obj->set_angle_velocity(0.0f);
        obj->set_obstacle_type(PIECE);
        // set triangle vertices
        AddObjectPoint(Vec2(0 - delta_p.x(), 0 - delta_p.y()));
        // we will compute rand_rad in order
        // to get rotate it
        rand_rad = GetObjectPoint(k - 1).length();
        AddObjectPoint(Vec2(rand_rad * cos(angle_now - 2 * PI / (object_points_array().size() - 2)) - delta_p.x(),
            rand_rad * sin(angle_now-2*PI/(object_points_array().size() - 2)) - delta_p.y()));
        rand_rad = GetObjectPoint(k).length();
        AddObjectPoint(Vec2(rand_rad * cos(angle_now) - delta_p.x(),
            rand_rad * sin(angle_now) - delta_p.y()));
        // and we should loop the triangle
        AddObjectPoint(GetObjectPoint(0));
        // just keep parent color
        obj->set_color(color_);
        Game::Instance()->obj_container()->AddObject(obj);
        k++;
    }
    if (have_bonus_)
        Game::Instance()->obj_container()->AddObject(new Bonus(p_));
}


Bonus::Bonus(Vec2 p) :
    Object(Object::BONUS, p),
    lifetime_(0.0f) {

    int half_size_x = 60;
    int half_size_y = 77;
    // counter clockwise order
    const float size = 30.0f;
    const float half_size = size / 2.0f;
    AddObjectPoint(Vec2(0.0f, 0.0f));
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

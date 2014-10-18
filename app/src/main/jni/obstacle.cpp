#include "obstacle.h"
#include "space_object.h"
#include "game_logic.h"
#include "physics_engine.h"
#include "space_ship.h"

Obstacle::Obstacle() :
    SpaceObject (
    Vec2(),
    Vec2(),
    Vec2(20.0f, 20.0f),
    2.0f,
    SpaceObject::OBSTACLE),
    obstacle_type_(WHOLE),
    have_bonus_(false) {

    p_ = Vec2(GLogic->getHScrSize().x() * (rand() % 100 - 50.0f) / 50.0f,
        GLogic->getHScrSize().y() + 10.0f);
    float v_y[] = { -10.0f, -15.0f, -20.0f, -22.0f, -24.0f };
    v_ = Vec2((rand() % 100 - 50.0f) / 50.0f * 4.0f,
        (rand() % 30 + 70.0f) / 100.0 * v_y[GLogic->getLevel()]);

    // here we generate random polygon
    float size = size_.x() * (1.0f + (rand() % 100 - 50.0f) / 50.0f * 0.3f);
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
    color_ = Color((rand() % 90 + 10.0f) / 100.0f,
        (rand() % 90 + 10.0f) / 100.0f, (rand() % 90 + 10.0f) / 100.0f, 0.0f);
    angle_velocity_ = (rand() % 100 - 50.0f) / 50.0f * 0.2f;
    have_bonus_ = rand() % 10 == 0;
};

bool Obstacle::Update(float dt) {
  // firstly we should invoke superclass method
  return SpaceObject::Update(dt);
}

void Obstacle::Collide(ObjectType with_obj) {
  if (with_obj == SpaceObject::BULLET)
    BlowUp();
}

// the most complicated function in that project =)
void Obstacle::BlowUp() {
    if (obstacle_type_ == PIECE)
        return;
    std::shared_ptr<SpaceObject> obj;
    int k = 2;  // because k=0 and k=1 is Vec2(0,0) point
    // and we use [k*2-2] in this loop
    float vel = 5;  // velocity of expansion
    float angle_now;
    float rand_rad;
    Vec2 delta_p;
    // create a bunch of new obstacles (triangles)
    for (float alpha = 2.0f * PI / (object_points().size() - 2); alpha <= 2.0f * PI;
        alpha += 2.0f * PI / (object_points().size() - 2)) {
        // angle considering rotation
        angle_now = alpha + angle_;
        obj = shared_ptr<SpaceObject>(new Obstacle());
        // delta_p is vector between position of new triangle
        // and position of an old obstacle
        delta_p = Vec2(size_.x() / 4 * cos(angle_now),
            size_.y() / 4 * sin(angle_now));
        obj->set_p(p_ + delta_p);
        obj->set_v(v_ + Vec2(vel * cos(angle_now),
            vel * sin(angle_now)));
        obj->set_angle_velocity(0.0f);
        Obstacle* obstacle = static_cast<Obstacle*>(obj.get());
        obstacle->set_obstacle_type(PIECE);
        // set triangle vertices
        AddObjectPoint(Vec2(0 - delta_p.x(), 0 - delta_p.y()));
        // we will compute rand_rad in order
        // to get rotate it
        rand_rad = GetObjectPoint(k - 1).length();
        AddObjectPoint(Vec2(rand_rad * cos(angle_now - 2 * PI / (object_points().size() - 2)) - delta_p.x(),
            rand_rad * sin(angle_now-2*PI/(object_points().size() - 2)) - delta_p.y()));
        rand_rad = GetObjectPoint(k).length();
        AddObjectPoint(Vec2(rand_rad * cos(angle_now) - delta_p.x(),
            rand_rad * sin(angle_now) - delta_p.y()));
        // and we should loop the triangle
        AddObjectPoint(GetObjectPoint(0));
        // this is triangle
        obj->set_size(size_ / 2.0f);
        // just keep parent color
        obj->set_color(color_);
        PEngine->objContainer.push_back(obj);
        k++;
    }
    if (have_bonus_) {
        PEngine->AddObject(p_, Vec2(), SpaceObject::BONUS);
    }
}


Bonus::Bonus(Vec2 p) :
    SpaceObject (p, Vec2(),
    Vec2(20, 20),
    2,
    SpaceObject::BONUS),
    lifetime_(0.0f) {

    int half_size_x = 60;
    int half_size_y = 77;
    // ok, this is counter clockwise order
    float x_tmp = size_.x() / 2.0f;
    float y_tmp = size_.y() / 2.0f;
    AddObjectPoint(Vec2(0.0f, 0.0f));
    AddObjectPoint(Vec2(-x_tmp, -y_tmp));
    AddObjectPoint(Vec2(x_tmp, -y_tmp));
    AddObjectPoint(Vec2(x_tmp, y_tmp));
    AddObjectPoint(Vec2(-x_tmp, y_tmp));
    AddObjectPoint(Vec2(-x_tmp, -y_tmp));

    color_ = Color(43.0f/255.0f, 194.0f/255.0f, 164.0f/255.0f, 0.0f);
    angle_velocity_ = PI;
}

void Bonus::Collide(ObjectType with_obj) {
  switch (with_obj) {
  case SpaceObject::SPACE_SHIP:
    Ship->TurnOnTripleFire();
    break;
  }
}

bool Bonus::Update(float dt) {
  if (!SpaceObject::Update(dt))
    return false;
  lifetime_ += dt;
  const float max_bonus_time = 15.0f;
  if (lifetime_ > max_bonus_time)
    return false;
  return true;
}

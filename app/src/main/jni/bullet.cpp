#include "bullet.h"
#include "utils.h"

Bullet::Bullet(Vec2 p, Vec2 v) :
    Object(Object::BULLET, p, v) {

    // let it be a triangle
    float l = 5.0f;
    float x_tmp = sqrt(3.0f) * l / 2.0f;
    float y_tmp = l / 2.0f;

    // counterclockwise order
    AddObjectPoint(Vec2(-x_tmp, -y_tmp));
    AddObjectPoint(Vec2(x_tmp, -y_tmp));
    AddObjectPoint(Vec2(0, 2.0f * y_tmp));
    AddObjectPoint(Vec2(-x_tmp, -y_tmp));
    color_ = utils::Color(0.0f, 1.0f, 0.0f, 0.0f);
    angle_velocity_ = 8.0f * PI;
};

void Bullet::Update(float dt, bool& delete_obj) {
    this->Object::Update(dt, delete_obj);
}

#include "bullet.h"
#include "game_logic.h"

Bullet::Bullet(Vec2 p, Vec2 v) :
 SpaceObject (p, v, Vec2(6.0f, 6.0f), -1, SpaceObject::BULLET) {
    // let it be a triangle
    float l = size_.x() / 2.0f;
    float x_tmp = sqrt(3.0f) * l / 2.0f;
    float y_tmp = l / 2.0f;
    // counterclockwise order
    AddObjectPoint(Vec2(-x_tmp, -y_tmp));
    AddObjectPoint(Vec2(x_tmp, -y_tmp));
    AddObjectPoint(Vec2(0, 2.0f * y_tmp));
    AddObjectPoint(Vec2(-x_tmp, -y_tmp));
    color_ = Color(0.0f, 1.0f, 0.0f, 0.0f);
    angle_velocity_ = 8.0f * PI;
};

bool Bullet::Update(float dt) {
    return this->SpaceObject::Update(dt);
}

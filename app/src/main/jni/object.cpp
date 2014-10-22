#include "object.h"
#include "graphic.h"


Object::Object(ObjectType type, Vec2 p, Vec2 v) :
    type_(type),
    p_(p),
    v_(v) {};

void Object::Update(float dt, bool& delete_obj) {
    p_ += v_ * dt;
    angle_ += angle_velocity_ * dt;
    if (angle_ > 2.0f * PI)
        angle_ = 0.0f;
}

//float* Object::GetObjectPointsArray() {
//    return &object_points_[0];
//};
//
//int Object::GetObjectPointsArraySize() const {
//    return object_points_.size() / 2;
//}

void Object::AddObjectPoint(Vec2 p) {
    object_points_.push_back(p);
    object_points_array_.push_back(p.x());
    object_points_array_.push_back(p.y());
}

Vec2 Object::GetObjectPoint(int i) const {
    if (i < 0 || i >= object_points_.size())
        return Vec2();
    return object_points_[i];
}

void Object::Draw() {
    Graphic::DrawPolygon(object_points_array_, p_, angle_, color_);
}
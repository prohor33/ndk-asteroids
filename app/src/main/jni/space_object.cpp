#include "space_object.h"

bool SpaceObject::Update(float dt) {
    p_ += v_ * dt;
    angle_ += angle_velocity_ * dt;
    if (angle_ > 2.0f * PI)
        angle_ = 0.0f;
    // return false if this object should be deleted
    return true;
}

float* SpaceObject::GetObjectPointsArray() {
    return &object_points_[0];
};

int SpaceObject::GetObjectPointsArraySize() const {
    return object_points_.size();
}

void SpaceObject::AddObjectPoint(Vec2 p) {
    object_points_.push_back(p.x());
    object_points_.push_back(p.y());
}

Vec2 SpaceObject::GetObjectPoint(int i) const {
    int i_array = i * 2;
    if (i_array < 0 || (i_array + 1) >= object_points_.size())
        return Vec2();
    return Vec2(object_points_[i_array], object_points_[i_array + 1]);
}

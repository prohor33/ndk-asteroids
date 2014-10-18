#pragma once

#include "main.h"

class SpaceObject {
public:
    enum ObjectType { NOT_DEFINED, OBSTACLE, BULLET, SPACE_SHIP, BONUS };

    SpaceObject(Vec2 p, Vec2 v, Vec2 size, float velocity, ObjectType obj_type) :
        p_(p),
        v_(v),
        size_(size),
        velocity_(velocity),
        obj_type_(obj_type),
        angle_(0.0f),
        angle_velocity_(0.0f) {};
    virtual ~SpaceObject() {};

    const Vec2& p() const { return p_; };
    void set_p(const Vec2& p) { p_ = p; };
    const Vec2& v() const { return v_; };
    void set_v(const Vec2& v) { v_ = v; };
    const Vec2& size() const { return size_; };
    void set_size(const Vec2& size) { size_ = size; };
    float angle() const { return angle_; };
    void set_angle(float angle) { angle_ = angle; };
    void set_angle_velocity(float x) { angle_velocity_ = x; };
    ObjectType obj_type() const { return obj_type_; };
    const Color& color() const { return color_; };
    void set_color(Color x) { color_ = x; };

    virtual bool Update(float dt);
    virtual void Collide(ObjectType with_obj) = 0;

    const std::vector<float>& object_points() const { return object_points_; };
    float* GetObjectPointsArray();
    int GetObjectPointsArraySize() const;
    Vec2 GetObjectPoint(int i) const;

protected:
    void AddObjectPoint(Vec2 p);

    Vec2 p_;
    Vec2 v_;
    Vec2 size_;
    float velocity_;    // TODO: ?
    Color color_;
    float angle_;
    float angle_velocity_;
    ObjectType obj_type_;
    std::vector<float> object_points_;
};

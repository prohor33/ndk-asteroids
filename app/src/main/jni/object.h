#pragma once

#include "utils.h"
#include <vector>

class Object {
friend class ObjContainer;
public:
    enum ObjectType { OBSTACLE, BULLET, SHIP, BONUS };
    Object(ObjectType type, Vec2 p = Vec2(), Vec2 v = Vec2());
    virtual ~Object() {};

    virtual void Collide(class Object* with_obj) = 0;
    virtual void Update(float dt, bool& delete_obj);
    virtual void Draw();
    Vec2 GetObjectPoint(int i) const;

    const Vec2& p() const { return p_; }
    void set_p(const Vec2& p) { p_ = p; }
    const Vec2& v() const { return v_; }
    void set_v(const Vec2& v) { v_ = v; }
    float angle() const { return angle_; }
    void set_angle(float angle) { angle_ = angle; }
    void set_angle_velocity(float x) { angle_velocity_ = x; }
    ObjectType type() const { return type_; }
    const utils::Color& color() const { return color_; }
    void set_color(utils::Color x) { color_ = x; }
    const std::vector<Vec2>& object_points() const { return object_points_; }
    const std::vector<float>& object_points_array() const { return object_points_array_; }
    int id() const { return id_; }

protected:
    void AddObjectPoint(Vec2 p);
    void DeleteMyself();
    void set_id(int id) { id_ = id; }

    Vec2 p_;
    Vec2 v_;
    utils::Color color_;
    float angle_;
    float angle_velocity_;
    ObjectType type_;
    std::vector<Vec2> object_points_;
    std::vector<float> object_points_array_;
    int id_;
};

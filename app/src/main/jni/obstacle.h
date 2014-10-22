#pragma once

#include "object.h"

class Obstacle : public Object {
public:
    enum ObstacleType { NOT_DEFINED, PIECE, WHOLE };
    Obstacle();
    ~Obstacle() {};

    virtual void Update(float dt, bool& delete_obj);
    virtual void Collide(Object* with_obj);
    void BlowUp();
    ObstacleType obstacle_type() const { return obstacle_type_; };
    void set_obstacle_type(ObstacleType x) { obstacle_type_ = x; };

private:
    ObstacleType obstacle_type_;
    bool have_bonus_;
};

class Bonus : public Object {
public:
    Bonus(Vec2 p);
    ~Bonus() {};

    virtual void Update(float dt, bool& delete_obj);
    virtual void Collide(Object* with_obj);
    float lifetime() const { return lifetime_; }

private:
    float lifetime_;
};

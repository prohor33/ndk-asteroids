#pragma once

#include "main.h"
#include "space_object.h"

class Obstacle : public SpaceObject {
public:
    enum ObstacleType { NOT_DEFINED, PIECE, WHOLE };
    Obstacle();
    ~Obstacle() {};

    bool Update(float dt);
    void BlowUp();
    void Collide(ObjectType with_obj);
    ObstacleType obstacle_type() const { return obstacle_type_; };
    void set_obstacle_type(ObstacleType x) { obstacle_type_ = x; };

private:
    ObstacleType obstacle_type_;
    bool have_bonus_;
};

class Bonus : public SpaceObject {
public:
    Bonus(Vec2 p);
    ~Bonus() {};

    bool Update(float dt);
    void Collide(ObjectType with_obj);
    float lifetime() const { return lifetime_; }

private:
    float lifetime_;
};

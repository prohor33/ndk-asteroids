#pragma once

#include "vec2.h"
#include "object.h"

class Ship : public Object {
public:
    virtual ~Ship() {};
    Ship();
    void Update(float dt, bool& delete_obj);
    void Collide(class Object* with_obj);
    void GoTo(Vec2 target_p);
    void TurnOnTripleFire();

private:
    void Fire();

    Vec2 target_p_;
    bool have_target_;
    bool triple_fire_;
    float delta_fire_t_;
    float delta_triple_fire_t_;
};

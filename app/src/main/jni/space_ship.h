#pragma once

#include "main.h"
#include "space_object.h"

class SpaceShip : public SpaceObject {
public:
    static SpaceShip* Instance() {
        static SpaceShip SpaceShip_;
        if (need_reinitializing) {
            SpaceShip_ = SpaceShip();
            need_reinitializing = false;
        }
        return &SpaceShip_;
    };
    ~SpaceShip() {};

    enum EventType { NOT_DEFINED, DOWN, UP, DRAG };

    bool Update(float dt);
    void Collide(ObjectType with_obj);
    void GoTo(Vec2 target_p);

    void EventHandler(EventType event_type, Vec2 pos);
    void TurnOnTripleFire();
    static bool need_reinitializing;    // TODO: fix that
private:
    SpaceShip();
    void Fire();
    void PreventOutOfBorders(Vec2& pos);

    Vec2 target_p_;
    bool have_target_;
    bool dragging_;
    Vec2 delta_dragging_;
    bool triple_fire_;
    float delta_fire_t_;
    float delta_triple_fire_t_;
};

#define Ship SpaceShip::Instance()

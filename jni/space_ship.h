#ifndef SPACE_SHIP_H_
#define SPACE_SHIP_H_

#include "main.h"
#include "space_object.h"

class SpaceShip : public SpaceObject {
public:
  static SpaceShip* instance() {
    static SpaceShip SpaceShip_;
    if (needReinitializing) {
      SpaceShip_ = SpaceShip();
      __android_log_print(ANDROID_LOG_INFO, "Asteroids", "initialize ship");
      needReinitializing = false;
    }
    return &SpaceShip_;
  };
  void update(float dt);
  ~SpaceShip() {};
  void collide(ObjectType withObj);
  void goTo(Vec2 target_p);
  enum EventType { NOT_DEFINED, DOWN, UP, DRAG };
  void eventHandler(EventType eventType, Vec2 pos);
  //void setNeedReinitializing( bool x ) { needReinitializing = x; };
  static bool needReinitializing;
private:
  SpaceShip();
  void _fire();
  void _preventOutOfBorders(Vec2& pos);
  float deltaFire_t;
  Vec2 target_p;
  bool haveTarget;
  bool dragging;
  Vec2 deltaDragging;
};

#define Ship SpaceShip::instance()

#endif /* SPACE_SHIP_H_ */

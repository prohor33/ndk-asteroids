#ifndef SPACE_SHIP_H_
#define SPACE_SHIP_H_

#include "main.h"
#include "space_object.h"

class SpaceShip : public SpaceObject {
public:
  static SpaceShip* instance() {
    static SpaceShip SpaceShip_;
    return &SpaceShip_;
  };
  void update(float dt);
  ~SpaceShip() {};
  void collide(ObjectType withObj);
  void goTo(Vec2 target_p);
private:
  SpaceShip();
  void _fire();
  float deltaFire_t;
  Vec2 target_p;
  bool haveTarget;
};

#define Ship SpaceShip::instance()

#endif /* SPACE_SHIP_H_ */

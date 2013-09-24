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
private:
  SpaceShip();
  ~SpaceShip() {};
};

#define Ship SpaceShip::instance()

#endif /* SPACE_SHIP_H_ */

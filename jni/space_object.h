#ifndef SPACE_OBJECT_H_
#define SPACE_OBJECT_H_

#include "main.h"

class SpaceObject {
public:
  SpaceObject(Vec2 p, Vec2 v, Vec2 size) :
    p(p), v(v), size(size) {};
  virtual ~SpaceObject() {};
  Vec2& getPos() { return p; };
  Vec2& getVel() { return v; };
  Vec2& getSize() { return size; };
private:
  Vec2 p;
  Vec2 v;
  Vec2 size;
};

#endif  /* SPACE_OBJECT_H_ */

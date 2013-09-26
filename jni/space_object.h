#ifndef SPACE_OBJECT_H_
#define SPACE_OBJECT_H_

#include "main.h"

class SpaceObject {
public:
  enum ObjectType { NOT_DEFINED, OBSTACLE, BULLET, SPACE_SHIP };
  SpaceObject(Vec2 p, Vec2 v, Vec2 size, float velocity, ObjectType objType) :
    p(p), v(v), size(size), velocity(velocity), objType(objType) {};
  virtual ~SpaceObject() {};
  Vec2& getPos() { return p; };
  Vec2& getVel() { return v; };
  Vec2& getSize() { return size; };
  void setVel(Vec2 v) { this->v = v; };
  void setPos(Vec2 p) { this->p = p; };
  void goTo(Vec2 target_p);
  virtual void update(float dt);
  virtual void collide(ObjectType withObj) {};
protected:
  Vec2 p;
  Vec2 v;
  Vec2 size;
  Vec2 target_p;
  const float velocity;
  ObjectType objType;
};

#endif  /* SPACE_OBJECT_H_ */

#ifndef SPACE_OBJECT_H_
#define SPACE_OBJECT_H_

#include "main.h"

class SpaceObject {
public:
  enum ObjectType { NOT_DEFINED, OBSTACLE, BULLET, SPACE_SHIP };
  SpaceObject(Vec2 p, Vec2 v, Vec2 size, float velocity, ObjectType objType) :
    p(p), v(v), size(size), velocity(velocity), objType(objType),
    erasable(true) {};
  virtual ~SpaceObject() {};
  const Vec2& getPos() { return p; };
  const Vec2& getVel() { return v; };
  const Vec2& getSize() { return size; };
  const ObjectType& getObjType() { return objType; };
  void setVel(Vec2 v) { this->v = v; };
  void setPos(Vec2 p) { this->p = p; };
  void goTo(Vec2 target_p);
  virtual void update(float dt);
  virtual void collide(ObjectType withObj) {};
  void setErasable(bool x) { erasable = x; };
  bool getErasable() { return erasable; };
protected:
  Vec2 p;
  Vec2 v;
  Vec2 size;
  Vec2 target_p;
  const float velocity;
  ObjectType objType;
  bool erasable;
};

#endif  /* SPACE_OBJECT_H_ */

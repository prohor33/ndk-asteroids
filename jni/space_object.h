#ifndef SPACE_OBJECT_H_
#define SPACE_OBJECT_H_

#include "main.h"

class SpaceObject {
public:
  enum ObjectType { NOT_DEFINED, OBSTACLE, BULLET, SPACE_SHIP };
  SpaceObject(Vec2 p, Vec2 v, Vec2 size, float velocity, ObjectType objType) :
    p(p), v(v), size(size), velocity(velocity), objType(objType),
    erasable(true), angle(0), angleVelocity(0) {};
  virtual ~SpaceObject() {};
  void setPos(const Vec2& p) { this->p = p; };
  const Vec2& getPos() { return p; };
  void setVel(const Vec2& v) { this->v = v; };
  const Vec2& getVel() { return v; };
  const Vec2& getSize() { return size; };
  void setSize(const Vec2& size) { this->size = size; };
  void setErasable(bool x) { erasable = x; };
  bool getErasable() { return erasable; };
  float getAngle() { return angle; };
  void setAngle(float x) { angle = x; };
  void setAngleVelocity(float x) { angleVelocity = x; };
  int setPolPointsSize(int x) { polPointsSize = x; };
  int getPolPointsSize() { return polPointsSize; };
  const ObjectType& getObjType() { return objType; };
  GLfloat* getPolPoints() { return polPoints.get(); };
  Color getColor() { return color; };
  void setColor(Color x) { color = x; };
  virtual void update(float dt);
  virtual void goTo(Vec2 target_p) = 0;
  virtual void collide(ObjectType withObj) = 0;
  shared_ptr<GLfloat[]> polPoints;
  // for debug
  ObjectType objType;
protected:
  Vec2 p;
  Vec2 v;
  Vec2 size;
  float velocity;
  bool erasable;
  int polPointsSize;
  Color color;
  float angle;
  float angleVelocity;
};

#endif  /* SPACE_OBJECT_H_ */

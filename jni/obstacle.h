#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include "main.h"
#include "space_object.h"

class Obstacle : public SpaceObject {
public:
  enum ObstType { NOT_DEFINED, PIECE, WHOLE };
	Obstacle();
	~Obstacle() {};
  bool update(float dt);
  void blowUp();
  void setObstType(ObstType x) { obstType = x; };
  void collide(ObjectType withObj);
  ObstType getObstType() { return obstType; };
private:
  ObstType obstType;
  bool haveBonus;
};

class Bonus : public SpaceObject {
public:
  Bonus(Vec2 p);
  ~Bonus() {};
  bool update(float dt);
  void collide(ObjectType withObj);
  float lifeTime_t;
};

#endif	/* OBSTACLE_H_ */

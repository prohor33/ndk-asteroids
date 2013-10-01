#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include "main.h"
#include "space_object.h"

class Obstacle : public SpaceObject {
public:
  enum ObstType { NOT_DEFINED, PIECE, WHOLE };
	Obstacle();
	~Obstacle() {};
  void update(float dt);
  void blowUp();
  void setObstType(ObstType x) { obstType = x; };
  void collide(ObjectType withObj);
private:
  ObstType obstType;
};

#endif	/* OBSTACLE_H_ */

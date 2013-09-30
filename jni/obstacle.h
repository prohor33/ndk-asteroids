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
  GLfloat* getPolPoints() { return polPoints.get(); };
  int getPolPointsSize() { return polPointsSize; };
  //static void blowUp(Obstacle *);
private:
  shared_ptr<GLfloat[]> polPoints;
  int polPointsSize;
  ObstType obstType;
};

#endif	/* OBSTACLE_H_ */

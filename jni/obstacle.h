#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include "main.h"
#include "space_object.h"

class Obstacle : public SpaceObject {
public:
	Obstacle();
	~Obstacle() {};
  void update(float dt);
  GLfloat* getPolPoints() { return polPoints.get(); };
  int getPolPointsSize() { return polPointsSize; };
private:
  shared_ptr<GLfloat[]> polPoints;
  int polPointsSize;
};

#endif	/* OBSTACLE_H_ */

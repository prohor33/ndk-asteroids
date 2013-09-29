#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include "main.h"
#include "space_object.h"


class Obstacle : public SpaceObject {
public:
	Obstacle(Vec2 p, Vec2 v);
	~Obstacle() {};
  void update(float dt);
private:
};

#endif	/* OBSTACLE_H_ */

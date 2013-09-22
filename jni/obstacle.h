#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include "main.h"

class Obstacle {
public:
	Obstacle( Vec2 p, Vec2 v ) : p(p), v(v) {};
	~Obstacle() {};
	Vec2 getPos() { return p; };
	Vec2 getVel() { return v; };
private:
	Vec2 p;
	Vec2 v;
};

#endif	/* OBSTACLE_H_ */

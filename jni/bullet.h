#ifndef BULLET_H_
#define BULLET_H_

#include "main.h"

class Bullet {
public:
	Bullet( Vec2 p, Vec2 v ) : p(p), v(v) {};
	~Bullet() {};
	Vec2 getPos() { return p; };
	Vec2 getVel() { return v; };
private:
	Vec2 p;
	Vec2 v;
};

#endif	/* BULLET_H_ */

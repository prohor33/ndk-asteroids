#ifndef BULLET_H_
#define BULLET_H_

#include "main.h"
#include "space_object.h"

class Bullet : public SpaceObject {
public:
	Bullet(Vec2 p, Vec2 v);
	~Bullet() {};
	void update(float dt);
	void collide(ObjectType withObj) {};
private:
};

#endif	/* BULLET_H_ */

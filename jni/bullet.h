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
	void goTo(Vec2 target_p) {};
private:
};

#endif	/* BULLET_H_ */

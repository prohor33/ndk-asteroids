#pragma once

#include "object.h"

class Bullet : public Object {
public:
	Bullet(Vec2 p, Vec2 v);
	~Bullet() {};

	virtual void Update(float dt, bool& delete_obj);
	virtual void Collide(Object* with_obj) {};
};

#pragma once

#include "main.h"
#include "space_object.h"

class Bullet : public SpaceObject {
public:
	Bullet(Vec2 p, Vec2 v);
	~Bullet() {};
	bool Update(float dt);
	void Collide(ObjectType with_obj) {};
};

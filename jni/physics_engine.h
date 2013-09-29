#ifndef PHYSICS_ENGINE_H_
#define PHYSICS_ENGINE_H_

#include "main.h"
#include "space_object.h"

class PhysicsEngine {
public:
  static PhysicsEngine* instance() {
		static PhysicsEngine PhysicsEngine_;
		return &PhysicsEngine_;
	};
	void updateGameState(float dt);
	void addObject(Vec2 p, Vec2 v,
	    SpaceObject::ObjectType objectType);
	vector<shared_ptr<SpaceObject> > objContainer;
	bool intesects(shared_ptr<SpaceObject> o1,
	    shared_ptr<SpaceObject> o2);
private:
	PhysicsEngine() {};
	~PhysicsEngine() {};
	void update(float dt);
	void computeCollisions();
};

#define PEngine PhysicsEngine::instance()

#endif /* PHYSICS_ENGINE_H_ */

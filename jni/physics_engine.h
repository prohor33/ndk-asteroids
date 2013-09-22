#ifndef PHYSICS_ENGINE_H_
#define PHYSICS_ENGINE_H_

class PhysicsEngine {
public:
  static PhysicsEngine* instance() {
		static PhysicsEngine PhysicsEngine_;
		return &PhysicsEngine_;
	};
	void UpdateGameState( double dt );
private:
	PhysicsEngine() {};
	~PhysicsEngine() {};
	void UpdateObstacles( double dt );
	void UpdateBullets( double dt );
	void UpdateSpaceShip( double dt );
};

#define PEngine PhysicsEngine::instance()

#endif /* PHYSICS_ENGINE_H_ */

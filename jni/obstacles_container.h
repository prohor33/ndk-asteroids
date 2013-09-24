#ifndef OBSTACLES_CONTAINER_H_
#define OBSTACLES_CONTAINER_H_

#include"main.h"
class Obstacle;

class ObstaclesContainer {
public:
	static ObstaclesContainer* instance() {
		static ObstaclesContainer ObstaclesContainer_;
		return &ObstaclesContainer_;
	};
	vector<Obstacle*>& getMass() { return mObstacles; };
	vector<Obstacle*> mObstacles;
private:
	ObstaclesContainer() {};
	~ObstaclesContainer() {};
};

#define ObstCont ObstaclesContainer::instance()

#endif	/* OBSTACLES_CONTAINER_H_ */

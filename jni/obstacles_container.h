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
private:
	ObstaclesContainer() {};
	~ObstaclesContainer() {};
	vector<Obstacle*> mObstacles;
};

#endif	/* OBSTACLES_CONTAINER_H_ */

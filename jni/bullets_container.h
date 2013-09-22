#ifndef BULLETS_CONTAINER_H_
#define BULLETS_CONTAINER_H_

#include"main.h"
class Bullet;

class BulletsContainer {
public:
	static BulletsContainer* instance() {
		static BulletsContainer BulletsContainer_;
		return &BulletsContainer_;
	};
	void addBullet( Vec2 p, Vec2 v );
	vector<Bullet*> mBullets;
private:
	BulletsContainer() {};
	~BulletsContainer() {};
};

#define BulletsCont BulletsContainer::instance()

#endif	/* BULLETS_CONTAINER_H_ */

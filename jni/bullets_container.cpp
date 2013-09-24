#include "bullets_container.h"
#include "main.h"
#include "bullet.h"

void BulletsContainer::addBullet( Vec2 p, Vec2 v ) {
  __android_log_print(ANDROID_LOG_INFO, "Asteroids", "add bullet v(%f, %f)", v.x(), v.y());
	mBullets.push_back( new Bullet( p, v ) );
	return;
}

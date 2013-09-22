#include "bullets_container.h"
#include "main.h"
#include "bullet.h"

void BulletsContainer::addBullet( Vec2 p, Vec2 v ) {
	mBullets.push_back( new Bullet( p, v ) );
	return;
}

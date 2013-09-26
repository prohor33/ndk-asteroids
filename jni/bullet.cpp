#include "bullet.h"
#include "game_logic.h"

Bullet::Bullet(Vec2 p, Vec2 v) : SpaceObject (p, v, Vec2(5, 5), 5, SpaceObject::BULLET) {};


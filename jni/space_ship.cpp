#include "space_ship.h"
#include "game_logic.h"

SpaceShip::SpaceShip() : SpaceObject (Vec2(GLogic->getScreenSize().x()/2, 20),
    Vec2(), Vec2(30, 30)) {};

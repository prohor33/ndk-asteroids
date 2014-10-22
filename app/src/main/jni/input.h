#pragma once

#include "vec2.h"

class Input {
    friend class Game;
public:
    enum InputType { DOWN, UP, DRAG };
    void Handle(InputType type, Vec2 p);

protected:
    Input();

private:
    bool dragging_;
    Vec2 start_delta_;
};
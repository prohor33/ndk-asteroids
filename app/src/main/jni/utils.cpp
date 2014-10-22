#include "utils.h"
#include "game.h"
#include <stdlib.h>

namespace utils {

    Vec2 PixelsToNormal(Vec2 pix_p) {
        const Vec2& screen_size = Game::Instance()->screen_size();
        const Vec2& screen_size_in_pixels = Game::Instance()->screen_size_in_pixels();
        return Vec2(pix_p.x() * screen_size.x() / screen_size_in_pixels.x(),
            screen_size.y() - pix_p.y() * screen_size.y() /
            screen_size_in_pixels.y()) - screen_size / 2;
    }

    float RandMinusXtoX(float x) {
        return (rand() % 100 - 50) / 50.0f * x;
    }
    float Rand0toX(float x) {
        return rand() % 100 / 100.0f * x;
    }
    bool RandOneOf(int x) {
        return rand() % x == 0;
    }

    Vec2 RotateVector(Vec2 v, float angle) {
      float alpha;
      float rad;
      // compute alpha
      if (v.x() == 0.0f) {
        // vector can be vertical
        // so dividing by zero will occur
        if (v.y() > 0.0f)
          alpha = PI / 2.0f;
        else
          alpha = -PI / 2.0f;
      }
      else {
        alpha = atan(v.y() / v.x());
        if (v.x() < 0.0f)
          alpha += PI;
      }
      alpha += angle;
      rad = sqrt(v.x() * v.x() + v.y() * v.y());
      return Vec2(rad * cos(alpha), rad * sin(alpha));
    }
}
#include "utils.h"
#include "game.h"

namespace utils {

    Vec2 PixelsToNormal(Vec2 pix_p) {
        const Vec2& screen_size = Game::Instance()->screen_size();
        const Vec2& screen_size_in_pixels = Game::Instance()->screen_size_in_pixels();
        return Vec2(pix_p.x() * screen_size.x() / screen_size_in_pixels.x(),
            screen_size.y() - pix_p.y() * screen_size.y() /
            screen_size_in_pixels.y()) - screen_size / 2;
    }
}
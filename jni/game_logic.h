#ifndef GAME_LOGIC_H_
#define GAME_LOGIC_H_

#include "main.h"

class GameLogic {
public:
  void Initialize();
  void DeInitialize();
  void MainGameLoop(double dt);
  static GameLogic* instance() {
    static GameLogic GameLogic_;
    return &GameLogic_;
  };
  const Vec2& getScrSize() { return screen_size; };
  const Vec2 getHScrSize() { return screen_size/2; };
  void setPaused(bool x) { paused = x; };
  bool getPaused() { return paused; };
  void setScreenSize(Vec2 screen_size) { this->screen_size = screen_size; };
  const Vec2& getScrSizeInPixels() { return screen_size_in_pixels; };
  void setScreenSizeInPixels(Vec2 screen_size_in_pixels) {
    this->screen_size_in_pixels = screen_size_in_pixels;
  };
  Vec2 pixCoordToNormal( Vec2 pix_c ) {
    return Vec2(pix_c.x() * screen_size.x() / screen_size_in_pixels.x(),
        screen_size.y() - pix_c.y() * screen_size.y() /
        screen_size_in_pixels.y()) - screen_size / 2;
  }
  void newGame();
  void gameOver();
  void restartGame();
private:
  GameLogic() :
    // this is only default screen sizes
    // it will be changed in appResize()
    screen_size(100, 150),
    screen_size_in_pixels(480, 720),
    justResume(false), shouldDeinitialise(false),
    paused(false) {};
  ~GameLogic() {};
  Vec2 screen_size;
  Vec2 screen_size_in_pixels;
  bool justResume;
  bool shouldDeinitialise;
  bool paused;
};

#define GLogic GameLogic::instance()

#endif /* GAME_LOGIC_H_ */

#ifndef GAME_LOGIC_H_
#define GAME_LOGIC_H_

#include "main.h"

class GameLogic {
public:
  void Initialize();
  void DeInitialize() {};
  void MainGameLoop(double dt);
  static GameLogic* instance() {
    static GameLogic GameLogic_;
    return &GameLogic_;
  };
  const Vec2& getScreenSize() { return screen_size; };
  void setScreenSize(Vec2 screen_size) { this->screen_size = screen_size; };
private:
  GameLogic() {};
  ~GameLogic() {};
  Vec2 screen_size;
};

#define GLogic GameLogic::instance()

#endif /* GAME_LOGIC_H_ */

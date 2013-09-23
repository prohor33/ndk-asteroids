#ifndef GAME_LOGIC_H_
#define GAME_LOGIC_H_

class GameLogic {
public:
  void Initialize();
  void DeInitialize() {};
  void MainGameLoop(double dt);
  static GameLogic* instance() {
    static GameLogic GameLogic_;
    return &GameLogic_;
  };
private:
  GameLogic() {};
  ~GameLogic() {};
};

#define GLogic GameLogic::instance()

#endif /* GAME_LOGIC_H_ */

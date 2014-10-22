#pragma once

#include "vec2.h"
#include "input.h"
#include "object.h"
#include <memory>
#include <vector>
#include <map>
#include <queue>

class ObjContainer {
    friend class Game;
    typedef std::map<int, std::shared_ptr<class Object>> ObjectMap;

public:
    void AddObject(Object* obj);
    void DeleteAllObjects();
    void DeleteObject(int id);
    Object* GetObjByID(int id);
    class Ship* GetShip();

protected:
    ObjContainer() : ship_id_(-1) {};
    void DoActualDeletion();
    int GenerateNewObjID();
    ObjectMap& objects() { return objects_; }

private:
    ObjectMap objects_;
    std::queue<int> objects_to_delete_;
    int ship_id_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

class Game {
public:
    static Game* Instance() {
        if (!instance_) {
            instance_ = std::shared_ptr<Game>(new Game());
        }
        return instance_.get();
    };
    ~Game() {};

    void New();
    void MainGameLoop(double dt);
    void AddScore(int x) { score_ += x; }
    void GameOver();
    const Vec2 GetHalfScreenSize() { return screen_size_/2; };

    const Vec2& screen_size() { return screen_size_; };
    void set_screen_size(Vec2 screen_size) { screen_size_ = screen_size; };
    const Vec2& screen_size_in_pixels() { return screen_size_in_pixels_; };
    void set_screen_size_in_pixels(Vec2 screen_size_in_pixels) {
        screen_size_in_pixels_ = screen_size_in_pixels;
    }
    void set_paused(bool paused) { paused_ = paused; }
    bool paused() { return paused_; }
    void set_need_restart() { need_restart_ = true; }
    int level() { return level_; };
    Input* input() { return input_.get(); }
    ObjContainer* obj_container() { return obj_container_.get(); }

private:
    Game();
    void UpdateObjects(float dt);
    void CheckCollisions();
    void SpawnObstacles(float dt);
    void CheckLevelUp();
    void DrawObjects();
    void CheckOutOgBorders();

    static std::shared_ptr<Game> instance_;
    Vec2 screen_size_;
    Vec2 screen_size_in_pixels_;
    bool paused_;
    bool need_restart_;
    int level_;
    int score_;
    std::vector<float> levels_time_;
    float time_passed_;
    std::shared_ptr<Input> input_;
    std::shared_ptr<ObjContainer> obj_container_;
};

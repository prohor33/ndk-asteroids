#include "game.h"
#include "graphic.h"
#include "physics.h"
#include "ship.h"
#include "app.h"
#include "object.h"
#include "obstacle.h"
#include "intersection.h"
#include <stdlib.h>
#include <algorithm>
#include <android/log.h>

std::shared_ptr<Game> Game::instance_ = NULL;

void ObjContainer::DeleteAllObjects() {
    objects_.clear();
    ship_id_ = -1;
}

void ObjContainer::DeleteObject(int id) {
    objects_to_delete_.push(id);
}

void ObjContainer::DoActualDeletion() {
    while (!objects_to_delete_.empty()) {
        objects_.erase(objects_to_delete_.front());
        objects_to_delete_.pop();
    }
}

void ObjContainer::AddObject(Object* obj) {
    int new_id = GenerateNewObjID();
    objects_[new_id] = std::shared_ptr<class Object>(obj);
    objects_[new_id]->set_id(new_id);
    if (objects_[new_id]->type() == Object::SHIP)
        ship_id_ = new_id;
}

int ObjContainer::GenerateNewObjID() {
    while (true) {
        int max_id = 1000;
        if (objects_.size() >= max_id) {
            max_id += 1000;
        }
        int id_tmp = rand() % max_id;
        if (!GetObjByID(id_tmp))
            return id_tmp;
    }
}

Object* ObjContainer::GetObjByID(int id) {
    auto it = objects_.find(id);
    if (it == objects_.end())
        return NULL;
    return (*it).second.get();
}

Ship* ObjContainer::GetShip() {
    return static_cast<Ship*>(GetObjByID(ship_id_));
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Game::Game() :
    screen_size_(100, 150),  // default size, will be changed in appResize()
    screen_size_in_pixels_(480, 720),
    paused_(false),
    need_restart_(false),
    level_(0),
    score_(0),
    time_passed_(0.0f),
    input_(new Input()),
    obj_container_(new ObjContainer())
{
    // init level_ switch time
    float level_time_tmp = 0;
    levels_time_.push_back(level_time_tmp += 30);
    levels_time_.push_back(level_time_tmp += 30);
    levels_time_.push_back(level_time_tmp += 30);
    levels_time_.push_back(level_time_tmp += 45);
};

void Game::New() {

    obj_container_->DeleteAllObjects();
    obj_container_->AddObject(new Ship());

    level_ = 0;
    score_ = 0;
    time_passed_ = 0;

    if (paused_) {
        app_android::_resume();
        paused_ = false;
    }
    need_restart_ = false;
}

void Game::GameOver() {
    if (paused_)
        return;
    paused_ = true;
    app_android::_pause();
}

void Game::MainGameLoop(double dt) {
    if (need_restart_)
        New();

    time_passed_ += dt;
    CheckLevelUp();
    SpawnObstacles(dt);
    UpdateObjects(dt);
    CheckCollisions();
    CheckOutOgBorders();
    obj_container_->DoActualDeletion();
    DrawObjects();
}

void Game::UpdateObjects(float dt) {
    for (auto obj : obj_container_->objects()) {
        bool delete_obj = false;
        obj.second->Update(dt, delete_obj);
        if (delete_obj)
            obj_container_->DeleteObject(obj.first);
    }
}

void Game::CheckCollisions() {
    for (auto obj1 : obj_container_->objects()) {
        for (auto obj2 : obj_container_->objects()) {
            bool collision = intersection::CheckObjectIntersection(obj1.second.get(),
                obj2.second.get());
            if (collision) {
                obj1.second->Collide(obj2.second.get());
                obj2.second->Collide(obj1.second.get());
            }
        }
    }
}

void Game::CheckOutOgBorders() {
    for (auto obj : obj_container_->objects()) {
        if (physics::CheckOutOfBorders(obj.second->p()))
            obj_container_->DeleteObject(obj.first);
    }
}

void Game::SpawnObstacles(float dt) {
    static float spawn_obstacle_dt_ = 0.0f;
    spawn_obstacle_dt_ += dt;
    float maxDeltaSpawnObstacles[] = { 2.0, 1.5, 1.0, 0.8, 0.3 };
    if (spawn_obstacle_dt_ > maxDeltaSpawnObstacles[Game::Instance()->level()]) {
        spawn_obstacle_dt_ = 0;
        // spawn new obstacle
        obj_container_->AddObject(new Obstacle(Obstacle::COMPOUND));
    }
}

void Game::CheckLevelUp() {
    if (time_passed_ > levels_time_[level_]) {
        if (level_ < levels_time_.size()) {
            // level_ up!
            level_++;
        }
    }
}

void Game::DrawObjects() {
    for (auto obj : obj_container_->objects()) {
        obj.second->Draw();
    }
}

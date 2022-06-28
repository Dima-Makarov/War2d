
#include "model.h"

Model::Model(int width, int height) : weapon_handler_(&vehicles_, &bullets_),
                                      tank_(Vec2f(100, 100), Vec2f(1, 0)),
                                      plane_(Vec2f(100, 400), Vec2f(1, 0)),
                                      ship_(Vec2f(100, 700), Vec2f(1, 0)) {
  width = 1500;
  height = 700;
  tanks_.push_back(&tank_);
  planes_.push_back(&plane_);
  ships_.push_back(&ship_);
  vehicles_.push_back(&tank_);
  vehicles_.push_back(&plane_);
  vehicles_.push_back(&ship_);
  weapon_handler_.Connect();
}

void Model::Update(int millis) {
  weapon_handler_.Update();
  for (auto vehicle : vehicles_) {
    vehicle->Update(millis);
  }
  for (auto bullet : bullets_) {
    bullet->Update(millis);
  }
}

void Model::HandleKeyPressEvent(QKeyEvent* event) {
  ship_.keyPressEvent(event);
}

void Model::HandleKeyReleaseEvent(QKeyEvent* event) {
  ship_.keyReleaseEvent(event);
}

void Model::HandleMousePressEvent(QMouseEvent* event) {
  ship_.mousePressEvent(event);
}

void Model::HandleMouseReleaseEvent(QMouseEvent* event) {
  ship_.mouseReleaseEvent(event);
}

void Model::HandleMouseMoveEvent(QMouseEvent* event) {
  ship_.mouseMoveEvent(event);
}

std::vector<GameObject*> Model::GetGameObjects() const {
  std::vector<GameObject*> result;
  for (auto i : vehicles_) {
    result.push_back(i);
  }
  for (auto i : bullets_) {
    result.push_back(i);
  }
  return result;
}

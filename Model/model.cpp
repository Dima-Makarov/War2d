
#include "model.h"

Model::Model(int width, int height) : weapon_handler_(&tanks_, &planes_, &bullets_), tank_(Vec2f(100, 100)), plane_(Vec2f(100,400)) {
  width = 1500;
  height = 700;
  tanks_.resize(1);
  planes_.resize(1);
  tanks_[0] = &tank_;
  planes_[0] = &plane_;
  srand(time(nullptr));
  weapon_handler_.Connect();
}


void Model::Update(int millis) {
  weapon_handler_.Update();
  for (auto& tank : tanks_) {
    tank->Update(millis);
  }
  for (auto& plane : planes_) {
    plane->Update(millis);
  }
  for(auto bullet : bullets_) {
    bullet->Update(millis);
  }
}

void Model::HandleKeyPressEvent(QKeyEvent* event) {
  plane_.keyPressEvent(event);
}

void Model::HandleKeyReleaseEvent(QKeyEvent* event) {
  plane_.keyReleaseEvent(event);
}
void Model::HandleMousePressEvent(QMouseEvent* event) {
  plane_.mousePressEvent(event);
}
void Model::HandleMouseReleaseEvent(QMouseEvent* event) {
  plane_.mouseReleaseEvent(event);
}
void Model::HandleMouseMoveEvent(QMouseEvent* event) {
  // plane_.mouseMoveEvent(event);
}

std::vector<GameObject*> Model::GetGameObjects() const {
  std::vector<GameObject*> result;
  for(auto i : tanks_) {
    result.push_back(i);
  }
  for(auto i : planes_) {
    result.push_back(i);
  }
  for(auto i : bullets_) {
    result.push_back(i);
  }
  return result;
}


#include <GameObjects/bot_tank.h>
#include "model.h"

void Model::Update(int millis) {
  weapon_handler_.Update();
  for (auto& soldier : soldiers_) {
    soldier->Update(millis);
  }
  for(auto bullet : bullets_) {
    bullet->Update(millis);
  }
}


Model::Model(int width, int height) : weapon_handler_(&soldiers_, &bullets_), player_(Vec2f(100,100)) {
  width = 1500;
  height = 700;
  soldiers_.resize(1);
  soldiers_[0] = &player_;
  srand(time(nullptr));
  weapon_handler_.Connect();
}

void Model::HandleKeyPressEvent(QKeyEvent* event) {
  player_.keyPressEvent(event);
}

void Model::HandleKeyReleaseEvent(QKeyEvent* event) {
  player_.keyReleaseEvent(event);
}
void Model::HandleMousePressEvent(QMouseEvent* event) {
  player_.mousePressEvent(event);
}
void Model::HandleMouseReleaseEvent(QMouseEvent* event) {
  player_.mouseReleaseEvent(event);
}
void Model::HandleMouseMoveEvent(QMouseEvent* event) {
  player_.mouseMoveEvent(event);
}

std::vector<GameObject*> Model::GetGameObjects() const {
  std::vector<GameObject*> result;
  for(auto i : soldiers_) {
    result.push_back(i);
  }
  for(auto i : bullets_) {
    result.push_back(i);
  }
  return result;
}


#include "model.h"

Model::Model(int, int) : weapon_handler_(&vehicles_, &bullets_),
                                      tank_(Vec2f(100, 100), Vec2f(1, 0)),
                                      plane_(Vec2f(100, 200), Vec2f(1, 0)),
                                      ship_(Vec2f(100, 300), Vec2f(1, 0)) {
  tanks_.push_back(&tank_);
  planes_.push_back(&plane_);
  ships_.push_back(&ship_);
  vehicles_.push_back(&tank_);
  vehicles_.push_back(&plane_);
  vehicles_.push_back(&ship_);
  weapon_handler_.Connect();
  auto* player = Player::Instance();
  if(player->GetCurrentVehicleId() == "tank") {
    player->SetVehicle(&tank_);
  }
  if(player->GetCurrentVehicleId() == "plane") {
    player->SetVehicle(&plane_);
  }
  if(player->GetCurrentVehicleId() == "ship") {
    player->SetVehicle(&ship_);
  }
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
  Player::Instance()->GetVehicle()->keyPressEvent(event);
}

void Model::HandleKeyReleaseEvent(QKeyEvent* event) {
  Player::Instance()->GetVehicle()->keyReleaseEvent(event);
}

void Model::HandleMousePressEvent(QMouseEvent* event) {
  Player::Instance()->GetVehicle()->mousePressEvent(event);
}

void Model::HandleMouseReleaseEvent(QMouseEvent* event) {
  Player::Instance()->GetVehicle()->mouseReleaseEvent(event);
}

void Model::HandleMouseMoveEvent(QMouseEvent* event) {
  Player::Instance()->GetVehicle()->mouseMoveEvent(event);
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


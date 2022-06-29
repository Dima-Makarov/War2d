#include "player.h"

Player* Player::instance = nullptr;

QString Player::GetNickname() const {
  return nickname_;
}

void Player::SetNickname(const QString& nickname) {
  nickname_ = nickname;
}

QString Player::GetCurrentVehicleId() const {
  return vehicle_id_;
}

QString Player::GetCurrentVehicleId() {
  return vehicle_id_;
}

void Player::SetCurrentVehicleId(const QString& vehicle_id) {
  vehicle_id_ = vehicle_id;
}

Vehicle* Player::GetVehicle() const {
  return vehicle_;
}

void Player::SetVehicle(Vehicle* vehicle) {
  vehicle_ = vehicle;
}


#include "player.h"

size_t Player::GetId() const {
  return id_;
}

void Player::SetId(size_t id) {
  id_ = id;
}

Vehicle* Player::GetCurrentVehicle() const {
  return current_vehicle_;
}

Vehicle* Player::GetCurrentVehicle() {
  return current_vehicle_;
}

void Player::SetCurrentVehicle(Vehicle* vehicle) {
  current_vehicle_ = vehicle;
}

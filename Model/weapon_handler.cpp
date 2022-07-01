
#include <iostream>
#include "weapon_handler.h"

WeaponHandler::WeaponHandler(std::vector<Vehicle*>* vehicles,
                             std::vector<Bullet*>* bullets)
    : QObject(nullptr), vehicles_(vehicles), bullets_(bullets) {
}

void WeaponHandler::Update() {
  for (size_t i = 0 ; i < bullets_->size() ; i++) {
    for (auto vehicle : *vehicles_) {
      Vec2f b_pos = (*bullets_)[i]->GetPosition();
      Vec2f s_pos = vehicle->GetPosition();
      if (std::hypot(b_pos.GetX() - s_pos.GetX(), b_pos.GetY() - s_pos.GetY()) < vehicle_radius) {
        if (vehicle->IsAlive()) {
          vehicle->TakeDamage((*bullets_)[i]->GetDamage());
          bullets_->erase(bullets_->begin() + i);
          i--;
          break;
        }
      }
    }
  }
  if (bullets_->size() > 50) {
    for (size_t i = 0 ; i < bullets_->size() ; i++) {
      Vec2f pos = (*bullets_)[i]->GetPosition();
      if (pos.GetX() > 20000
          || pos.GetX() < -20000
          || pos.GetY() > 20000
          || pos.GetY() < -20000) {
        bullets_->erase(bullets_->begin() + i);
        i--;
      }
    }
  }
}

void WeaponHandler::AddBullet(Vec2f position, Vec2f orientation, double speed, double damage, double bullet_length) {
  auto* bullet = new Bullet(position, orientation, speed, damage, bullet_length);
  bullets_->push_back(bullet);
}

void WeaponHandler::Connect() {
  for (auto vehicle : *vehicles_) {
    connect(vehicle, &Vehicle::Shoot, this, &WeaponHandler::AddBullet, Qt::DirectConnection);
  }
}

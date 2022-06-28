
#include <iostream>
#include "weapon_handler.h"

WeaponHandler::WeaponHandler(std::vector<Tank*>* tanks,std::vector<Plane*>* planes, std::vector<Bullet*>* bullets)
    : QObject(nullptr), tanks_(tanks), planes_(planes), bullets_(bullets) {
}

void WeaponHandler::Update() {
  for (size_t i = 0 ; i < bullets_->size() ; i++) {
    for (auto tank : *tanks_) {
      Vec2f b_pos = (*bullets_)[i]->GetPosition();
      Vec2f s_pos = tank->GetPosition();
      if (std::hypot(b_pos.GetX() - s_pos.GetX(), b_pos.GetY() - s_pos.GetY()) < soldier_radius) {
        if (tank->IsAlive()) {
          tank->TakeDamage();
          bullets_->erase(bullets_->begin() + i);
          i--;
          break;
        }
      }
    }

    for (auto plane : *planes_) {
      Vec2f b_pos = (*bullets_)[i]->GetPosition();
      Vec2f s_pos = plane->GetPosition();
      if (std::hypot(b_pos.GetX() - s_pos.GetX(), b_pos.GetY() - s_pos.GetY()) < soldier_radius) {
        if (plane->IsAlive()) {
          plane->TakeDamage();
          bullets_->erase(bullets_->begin() + i);
          i--;
          break;
        }
      }
    }
  }
  if(bullets_->size() > 50) {
    for (size_t i = 0 ; i < bullets_->size() ; i++) {
      Vec2f pos = (*bullets_)[i]->GetPosition();
      if (pos.GetX() > 2000
          || pos.GetX() < 0
          || pos.GetY() > 2000
          || pos.GetY() < 0) {
        bullets_->erase(bullets_->begin() + i);
        i--;
      }
    }
  }
}

void WeaponHandler::AddBullet(Vec2f position, Vec2f orientation) {
  auto* bullet = new Bullet(position, orientation);
  bullets_->push_back(bullet);
}

void WeaponHandler::Connect() {
  for (auto tank : *tanks_) {
    connect(tank, &Tank::Shoot, this, &WeaponHandler::AddBullet, Qt::DirectConnection);
  }
  for (auto plane : *planes_) {
    connect(plane, &Plane::Shoot, this, &WeaponHandler::AddBullet, Qt::DirectConnection);
  }
}

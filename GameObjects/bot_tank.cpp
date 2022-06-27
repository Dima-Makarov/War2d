#include "bot_tank.h"

QPixmap BotTank::GetPixmap() const {
  if(!is_alive_) {
    return QPixmap{};
  }
  return QPixmap{"red_soldier.png"};
}

void BotTank::Update(int millis) {
  if (!is_alive_) {
    return;
  }
  double threshold = 1000;
  Tank* soldier = FindNearestEnemySoldier();
  if (soldier == nullptr) {
    return;
  }
  double distance = std::hypot(soldier->GetPosition().GetX() - position_.GetX(),
                               soldier->GetPosition().GetY() - position_.GetY());
  orientation_.Set(soldier->GetPosition().GetX() - position_.GetX(),
                   soldier->GetPosition().GetY() - position_.GetY());
  orientation_.Normalize();
  if (distance < threshold) {
    if (!recoil_timer.isActive()) {
      recoil_timer.start(1000);
      Shoot(position_ + orientation_ * 20, orientation_);
    }
  } else {
    // position_ += orientation_ * speed_ * (static_cast<double>(millis) / 1000);
  }
}

Tank* BotTank::FindNearestEnemySoldier() {
  double distance;
  bool there_is_an_enemy_soldier = false;
  Tank* nearest_soldier = nullptr;
  for (auto soldier : *soldiers_) {
    if (soldier->GetTeam() != team_ && soldier->IsAlive()) {
      there_is_an_enemy_soldier = true;
      nearest_soldier = soldier;
      distance = std::hypot(soldier->GetPosition().GetX() - position_.GetX(),
                            soldier->GetPosition().GetY() - position_.GetY());
    }
  }
  if (!there_is_an_enemy_soldier) {
    return nullptr;
  }
  for (auto soldier : *soldiers_) {
    if (soldier->GetTeam() != team_ && soldier->IsAlive()) {
      double new_distance = std::hypot(soldier->GetPosition().GetX() - position_.GetX(),
                                       soldier->GetPosition().GetY() - position_.GetY());
      if (new_distance < distance) {
        distance = new_distance;
        nearest_soldier = soldier;
      }
    }
  }
  return nearest_soldier;
}

BotTank::BotTank(const Vec2f& position, std::vector<Tank*>* soldiers)
    : Tank(Tank::bot, position), soldiers_(soldiers) {}

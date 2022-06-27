#include "tank.h"

Tank::Team Tank::GetTeam() const {
  return team_;
}

double Tank::GetHp() const {
  return hp_;
}

bool Tank::IsAlive() const {
  return is_alive_;
}

Tank::Tank(Tank::Team team, const Vec2f& position)
    : GameObject(position, Vec2f(1,0)),
      team_(team),
      hp_(100),
      speed_(50),
      is_alive_(true) {
  recoil_timer.setSingleShot(true);
}

void Tank::TakeDamage() {
  hp_ -= 21;
  if(hp_ < 0) {
    is_alive_ = false;
  }
}

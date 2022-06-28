#include "plane.h"

QPixmap Plane::GetPixmap() const {
  if (!is_alive_) {
    return QPixmap();
  }
  return QPixmap("plane");
}

Plane::Plane(const Vec2f& position, const Vec2f& orientation) : Vehicle(position, orientation) {
  speed_ = kMaxSpeed;
}

void Plane::Update(int millis) {
  if (!is_alive_) {
    return;
  }

  if (up_pressed_) {
  }
  if (down_pressed_) {
  }
  if (left_pressed_) {
    orientation_.Rotate(-kAngularRotatingSpeed * millis / 1000);
  }
  if (right_pressed_) {
    orientation_.Rotate(kAngularRotatingSpeed * millis / 1000);
  }

  position_ += orientation_ * speed_ * (static_cast<double>(millis) / 1000);
  if (is_shooting_) {
    if (!recoil_timer.isActive()) {
      recoil_timer.start(kRecoilTime * 1000);
      Shoot(position_ + orientation_ * 20, orientation_);
    }
  }
}

#include "ship.h"

Ship::Ship(const Vec2f& position, const Vec2f& orientation)
    : Vehicle(position, orientation),
      turret_orientation_(orientation) {
}

QPixmap Ship::GetPixmap() const {
  if (!is_alive_) {
    return QPixmap{};
  }
  return PixmapLoader::Instance()->ship;

}

void Ship::Update(int millis) {
  if (!is_alive_) {
    return;
  }
  Vec2f vector_to_mouse = Vec2f(mouse_coordinates_.x() - position_.GetX(),
                                mouse_coordinates_.y() - position_.GetY());
  double angle = vector_to_mouse.AngleBetween(turret_orientation_);
  double angle_to_rotate;
  if (std::abs(angle) > M_PI / 12) {
    angle_to_rotate = kTurretAngularRotatingSpeed / 1'000 * millis;
  } else {
    angle_to_rotate = kTurretAngularRotatingSpeed / 1'000 * millis * std::abs(angle) / M_PI * 12;
  }
  turret_orientation_.Rotate(angle > 0 ? angle_to_rotate : -angle_to_rotate);
  if (up_pressed_) {
    if (speed_ < 0) {
      speed_ += kForwardAcceleration * millis / 1000;
    } else {
      if (kForwardAcceleration * millis / 1000 > std::abs(kMaxSpeed - std::abs(speed_))) {
        speed_ = kMaxSpeed;
      } else {
        speed_ += kForwardAcceleration * millis / 1000;
      }
    }
  }
  if (down_pressed_) {
    if (speed_ > 0) {
      speed_ -= kForwardAcceleration * millis / 1000;
    } else {
      if (kForwardAcceleration * millis / 1000 > std::abs(kMaxSpeed - std::abs(speed_))) {
        speed_ = -kMaxSpeed;
      } else {
        speed_ -= kForwardAcceleration * millis / 1000;
      }
    }
  }
  if (left_pressed_) {
    orientation_.Rotate(-kHullAngularRotatingSpeed * millis / 1000 * std::abs(speed_) / kMaxSpeed);
    turret_orientation_.Rotate(
        -kHullAngularRotatingSpeed * millis / 1000 * std::abs(speed_) / kMaxSpeed);
  }
  if (right_pressed_) {
    orientation_.Rotate(kHullAngularRotatingSpeed * millis / 1000 * std::abs(speed_) / kMaxSpeed);
    turret_orientation_.Rotate(
        kHullAngularRotatingSpeed * millis / 1000 * std::abs(speed_) / kMaxSpeed);
  }

  position_ += orientation_ * speed_ * (static_cast<double>(millis) / 1000);
  if (is_shooting_) {
    if (!recoil_timer.isActive()) {
      recoil_timer.start(kRecoilTime * 1000);
      Shoot(position_ + turret_orientation_ * 20, turret_orientation_, 800, 50);
    }
  }
}

Vec2f Ship::GetTurretOrientation() {
  return turret_orientation_;
}

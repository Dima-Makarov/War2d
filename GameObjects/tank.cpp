#include "tank.h"

Tank::Tank(const Vec2f& position, const Vec2f& orientation)
    : Vehicle(position, orientation),
      turret_orientation_(orientation) {
}

QPixmap Tank::GetPixmap() const {
  if (!is_alive_) {
    return QPixmap{};
  }
  return PixmapLoader::Instance()->tank;
}

void Tank::Update(int millis) {
  if (!is_alive_) {
    return;
  }
  Vec2f vector_to_mouse = Vec2f(mouse_coordinates_.x(),
                                mouse_coordinates_.y());
  double angle = vector_to_mouse.AngleBetween(turret_orientation_);
  double angle_to_rotate;
  if (std::abs(angle) > M_PI / 12) {
    angle_to_rotate = kTurretAngularRotatingSpeed / 1'000 * millis;
  } else {
    angle_to_rotate = kTurretAngularRotatingSpeed / 1'000 * millis * std::abs(angle) / M_PI * 12;
  }
  turret_orientation_.Rotate(angle > 0 ? angle_to_rotate : -angle_to_rotate);

  if (!up_pressed_ && !down_pressed_) {
    if (std::abs(speed_) < 1) {
      speed_ = 0;
    } else if (speed_ > 0) {
      speed_ -= kForwardAcceleration * millis / 1000;
    } else if (speed_ < 0) {
      speed_ += kForwardAcceleration * millis / 1000;
    }
  }

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
    orientation_.Rotate(-kHullAngularRotatingSpeed * millis / 1000);
    turret_orientation_.Rotate(-kHullAngularRotatingSpeed * millis / 1000);
  }

  if (right_pressed_) {
    orientation_.Rotate(kHullAngularRotatingSpeed * millis / 1000);
    turret_orientation_.Rotate(kHullAngularRotatingSpeed * millis / 1000);
  }

  position_ += orientation_ * speed_ * (static_cast<double>(millis) / 1000);
  if (is_shooting_) {
    if (!recoil_timer.isActive()) {
      recoil_timer.start(kRecoilTime * 1000);
      Shoot(position_ + turret_orientation_ * 20, turret_orientation_, 900, 20);
    }
  }
}

Vec2f Tank::GetTurretOrientation() {
  return turret_orientation_;
}

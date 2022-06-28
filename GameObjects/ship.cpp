#include "ship.h"


double Ship::GetHp() const {
  return hp_;
}

bool Ship::IsAlive() const {
  return is_alive_;
}

QPixmap Ship::GetPixmap() const {
  if (!is_alive_) {
    return QPixmap{};
  }
  return QPixmap{"ship"};
}

void Ship::Update(int millis) {
  if (!is_alive_) {
    return;
  }
  double angle = vector_to_mouse_.AngleBetween(turret_orientation_);
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
    turret_orientation_.Rotate(-kHullAngularRotatingSpeed * millis / 1000 * std::abs(speed_) / kMaxSpeed);
  }
  if (right_pressed_) {
    orientation_.Rotate(kHullAngularRotatingSpeed * millis / 1000 * std::abs(speed_) / kMaxSpeed);
    turret_orientation_.Rotate(kHullAngularRotatingSpeed * millis / 1000 * std::abs(speed_) / kMaxSpeed);
  }

  position_ += orientation_ * speed_ * (static_cast<double>(millis) / 1000);
  if (is_shooting_) {
    if (!recoil_timer.isActive()) {
      recoil_timer.start(kRecoilTime * 1000);
      Shoot(position_ + turret_orientation_ * 20, turret_orientation_);
    }
  }
}

void Ship::keyPressEvent(QKeyEvent* event) {
  int key = event->key();
  if (key == Qt::Key_W) {
    up_pressed_ = true;
  }
  if (key == Qt::Key_S) {
    down_pressed_ = true;
  }
  if (key == Qt::Key_A) {
    left_pressed_ = true;
  }
  if (key == Qt::Key_D) {
    right_pressed_ = true;
  }
}

void Ship::keyReleaseEvent(QKeyEvent* event) {
  int key = event->key();
  if (key == Qt::Key_W) {
    up_pressed_ = false;
  }
  if (key == Qt::Key_S) {
    down_pressed_ = false;
  }
  if (key == Qt::Key_A) {
    left_pressed_ = false;
  }
  if (key == Qt::Key_D) {
    right_pressed_ = false;
  }
}

void Ship::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    is_shooting_ = true;
  }
  mouseMoveEvent(event);
}

void Ship::mouseReleaseEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    is_shooting_ = false;
  }
  mouseMoveEvent(event);
}

void Ship::mouseMoveEvent(QMouseEvent* event) {
  int mouse_x = event->pos().x();
  int mouse_y = event->pos().y();
  vector_to_mouse_ = Vec2f(mouse_x - position_.GetX(), mouse_y - position_.GetY());
}

Ship::Ship(const Vec2f& position)
    : GameObject(position, Vec2f(1,0)),
      hp_(100),
      speed_(0),
      turret_orientation_(orientation_),
      is_alive_(true){
  recoil_timer.setSingleShot(true);
}

void Ship::TakeDamage() {
  hp_ -= 21;
  if(hp_ < 0) {
    is_alive_ = false;
  }
}

Vec2f Ship::GetTurretOrientation() {
  return turret_orientation_;
}
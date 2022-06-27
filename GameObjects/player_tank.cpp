#include "player_tank.h"

QPixmap PlayerTank::GetPixmap() const {
  if (!is_alive_) {
    return QPixmap{};
  }
  return QPixmap{"hull"};
}

void PlayerTank::Update(int millis) {
  if (!is_alive_) {
    return;
  }
  double angle = vector_to_mouse_.AngleBetween(turret_orientation_);
  double angle_to_rotate = kTurretAngularRotatingSpeed / 360 * 2 * M_PI / 1'000 * millis;
  turret_orientation_.Rotate(angle > 0 ? angle_to_rotate : -angle_to_rotate);
  if (up_pressed_) {
    speed_ += kForwardAcceleration * millis / 1000;
    if(speed_ > kMaxSpeed / 3.6) {
      speed_ = kMaxSpeed;
    }
  }
  if (down_pressed_) {
    speed_ -= kForwardAcceleration * millis / 1000;
    if(speed_ < -kMaxSpeed / 3.6) {
      speed_ = -kMaxSpeed;
    }
  }
  if (left_pressed_) {
    orientation_.Rotate(-kHullAngularRotatingSpeed / 360 * 2 * M_PI * millis / 1000);
  }
  if (right_pressed_) {
    orientation_.Rotate(kHullAngularRotatingSpeed / 360 * 2 * M_PI * millis / 1000);
  }

  position_ += orientation_ * speed_ * (static_cast<double>(millis) / 1000);
  if (is_shooting_) {
    if (!recoil_timer.isActive()) {
      recoil_timer.start(kRecoilTime * 1000);
      Shoot(position_ + turret_orientation_ * 20, turret_orientation_);
    }
  }
}

void PlayerTank::keyPressEvent(QKeyEvent* event) {
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

void PlayerTank::keyReleaseEvent(QKeyEvent* event) {
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

void PlayerTank::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    is_shooting_ = true;
  }
  mouseMoveEvent(event);
}

void PlayerTank::mouseReleaseEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    is_shooting_ = false;
  }
  mouseMoveEvent(event);
}

void PlayerTank::mouseMoveEvent(QMouseEvent* event) {
  int mouse_x = event->pos().x();
  int mouse_y = event->pos().y();
  vector_to_mouse_ = Vec2f(mouse_x - position_.GetX(), mouse_y - position_.GetY());
}

PlayerTank::PlayerTank(const Vec2f& position) : Tank(Tank::player, position) {}

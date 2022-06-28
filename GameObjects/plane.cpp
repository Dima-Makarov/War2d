#include "plane.h"

QPixmap Plane::GetPixmap() const {
  if(!is_alive_) {
    return QPixmap();
  }
  return QPixmap("plane");
}

Plane::Plane(const Vec2f& position) : GameObject(position, Vec2f(1,0)),
                                                  hp_(100),
                                                  speed_(100) {
  recoil_timer.setSingleShot(true);
}

void Plane::TakeDamage() {
  hp_ -= 21;
  if(hp_ < 0) {
    is_alive_ = false;
  }
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

void Plane::keyPressEvent(QKeyEvent* event) {
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

void Plane::keyReleaseEvent(QKeyEvent* event) {
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

void Plane::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    is_shooting_ = true;
  }
}

void Plane::mouseReleaseEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    is_shooting_ = false;
  }
}

bool Plane::IsAlive() const {
  return is_alive_;
}

double Plane::GetHp() const {
  return hp_;
}

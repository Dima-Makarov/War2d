#include "vehicle.h"


Vehicle::Vehicle(Vec2f position, Vec2f orientation) : GameObject(position, orientation) {
recoil_timer.setSingleShot(true);
}

void Vehicle::keyPressEvent(QKeyEvent* event) {
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

void Vehicle::keyReleaseEvent(QKeyEvent* event) {
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

void Vehicle::mousePressEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    is_shooting_ = true;
  }
  mouseMoveEvent(event);
}

void Vehicle::mouseReleaseEvent(QMouseEvent* event) {
  if (event->button() == Qt::LeftButton) {
    is_shooting_ = false;
  }
  mouseMoveEvent(event);
}

void Vehicle::mouseMoveEvent(QMouseEvent* event) {
  mouse_coordinates_ = QPoint(event->pos().x() ,event->pos().y());
}

void Vehicle::TakeDamage(double damage) {
  hp_ -= damage;
  if (hp_ < 0) {
    is_alive_ = false;
  }
}

bool Vehicle::IsAlive() const {
  return is_alive_;
}

double Vehicle::GetHp() const {
  return hp_;
}

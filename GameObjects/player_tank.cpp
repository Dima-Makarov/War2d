#include "player_tank.h"

QPixmap PlayerTank::GetPixmap() const {
  if(!is_alive_) {
    return QPixmap{};
  }
  return QPixmap{"blue_soldier"};
}

void PlayerTank::Update(int millis) {
  speed_ = 130;
  if(!is_alive_) {
    return;
  }
  Vec2f dir_vec = {0,0};
  if(up_pressed_) {
    dir_vec += Vec2f(0,-1);
  }
  if(down_pressed_) {
    dir_vec += Vec2f(0,1);
  }
  if(left_pressed_) {
    dir_vec += Vec2f(-1,0);
  }
  if(right_pressed_) {
    dir_vec += Vec2f(1,0);
  }
  position_ += dir_vec * speed_ * (static_cast<double>(millis) / 1000);
  if(is_shooting_) {
    if (!recoil_timer.isActive()) {
      recoil_timer.start(500);
      Shoot(position_ + orientation_ * 20, orientation_);
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
  if(event->button() == Qt::LeftButton) {
    is_shooting_ = true;
  }
  mouseMoveEvent(event);
}

void PlayerTank::mouseReleaseEvent(QMouseEvent* event) {
  if(event->button() == Qt::LeftButton) {
    is_shooting_ = false;
  }
  mouseMoveEvent(event);
}

void PlayerTank::mouseMoveEvent(QMouseEvent* event) {
  int mouse_x = event->pos().x();
  int mouse_y = event->pos().y();
  orientation_.Set(mouse_x - position_.GetX(), mouse_y-position_.GetY());
  orientation_.Normalize();
}

PlayerTank::PlayerTank(const Vec2f& position) : Tank(Tank::player, position) {}

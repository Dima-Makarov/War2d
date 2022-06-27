#include <iostream>
#include "bullet.h"


void Bullet::Update(int millis) {
  position_ += orientation_ * speed_ * (static_cast<double>(millis) / 1000);
}


Bullet::Bullet(const Vec2f& position, const Vec2f& orientation)
    : GameObject(position, orientation) {}

QPixmap Bullet::GetPixmap() const {
  return QPixmap{"bullet.png"};
}

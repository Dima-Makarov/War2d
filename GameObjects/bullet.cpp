#include <iostream>
#include "bullet.h"


void Bullet::Update(int millis) {
  position_ += orientation_ * speed_ * (static_cast<double>(millis) / 1000);
}


Bullet::Bullet(const Vec2f& position, const Vec2f& orientation, double speed, double damage)
    : GameObject(position, orientation), speed_(speed), damage_(damage) {}

QPixmap Bullet::GetPixmap() const {
  return QPixmap{"bullet.png"};
}

double Bullet::GetDamage() const {
  return damage_;
}

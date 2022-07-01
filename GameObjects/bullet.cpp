#include <iostream>
#include "Utils/pixmap_loader.h"
#include "bullet.h"

void Bullet::Update(int millis) {
  position_ += orientation_ * speed_ * (static_cast<double>(millis) / 1000);
}

Bullet::Bullet(const Vec2f& position,
               const Vec2f& orientation,
               double speed,
               double damage,
               double length)
    : GameObject(position, orientation),
      speed_(speed),
      damage_(damage),
      length_(length),
      initial_position_(position) {}

QPixmap Bullet::GetPixmap() const {
  return PixmapLoader::Instance()->bullet;
}

double Bullet::GetDamage() const {
  return damage_;
}

double Bullet::GetLength() const {
  return length_;
}

const Vec2f& Bullet::GetInitialPosition() const {
  return initial_position_;
}

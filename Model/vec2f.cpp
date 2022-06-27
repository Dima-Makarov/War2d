//  https://github.com/abainbridge/car_sim
#include "vec2f.h"

Vec2f Vec2f::operator+(Vec2f const& b) const {
  return Vec2f(x_ + b.x_, y_ + b.y_);
}

Vec2f Vec2f::operator-(Vec2f const& b) const {
  return Vec2f(x_ - b.x_, y_ - b.y_);
}

Vec2f Vec2f::operator*(double const b) const {
  return Vec2f(x_ * b, y_ * b);
}

Vec2f const& Vec2f::Normalize() {
  double length_squared = x_ * x_ + y_ * y_;
  if (length_squared > 0.0f) {
    double inverted_length = 1.0f / sqrt(length_squared);
    x_ *= inverted_length;
    y_ *= inverted_length;
  } else {
    x_ = 0.0f;
    y_ = 0.0f;
  }

  return *this;
}

void Vec2f::SetLen(double len) {
  double scalar = len / GetLength();
  x_ *= scalar;
  y_ *= scalar;
}

void Vec2f::Rotate(double radians) {
  double tmp = x_;
  double cs = cos(radians);
  double sn = sin(radians);
  x_ = x_ * cs - y_ * sn;
  y_ = tmp * sn + y_ * cs;
}

double Vec2f::AngleBetween(Vec2f const& other) const {
  Vec2f this_normalized = *this;
  this_normalized.Normalize();
  Vec2f other_normalized = other;
  other_normalized.Normalize();
  return this_normalized.y_ * other_normalized.x_
      - this_normalized.x_ * other_normalized.y_;
}

Vec2f Vec2f::GetPerpendicular() const {
  return Vec2f(y_, -x_);
}

double Vec2f::GetLength() const {
  return sqrt(x_ * x_ + y_ * y_);
}

double Vec2f::GetAngleDegrees() const {
  double angle = atan(y_ / x_) * 360 / (2 * M_PI);
  if (x_ < 0) {
    angle += 180;
  }
  return angle;
}

double Vec2f::GetX() const {
  return x_;
}

double Vec2f::GetY() const {
  return y_;
}

Vec2f& Vec2f::operator*=(double b) {
  x_ *= b;
  y_ *= b;
  return *this;
}

Vec2f& Vec2f::operator+=(const Vec2f& b) {
  x_ += b.x_;
  y_ += b.y_;
  return *this;
}

Vec2f& Vec2f::operator-=(const Vec2f& b) {
  x_ -= b.x_;
  y_ -= b.y_;
  return *this;
}

Vec2f& Vec2f::operator/=(const Vec2f& b) {
  x_ /= b.x_;
  y_ /= b.y_;
  return *this;
}

void Vec2f::Set(double _x, double _y) {
  x_ = _x;
  y_ = _y;
}

bool Vec2f::operator==(const Vec2f& rhs) const {
  return x_ == rhs.x_ && y_ == rhs.y_;
}

bool Vec2f::operator!=(const Vec2f& rhs) const {
  return !(rhs == *this);
}

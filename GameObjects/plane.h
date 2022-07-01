#pragma once

#include <QTimer>
#include <QPixmap>
#include <QKeyEvent>
#include <QMouseEvent>

#include "vehicle.h"

class Plane : public Vehicle {
 Q_OBJECT
 public:
  Plane(const Vec2f& position, const Vec2f& orientation);

  void Update(int millis) override;
  QPixmap GetPixmap() const override;
  double GetLength() const override;

 private:
  static constexpr double kAngularRotatingSpeed = 50.0 / 360 * 2 * M_PI; // rad/s
  static constexpr double kForwardAcceleration = 30; // m/s^2
  static constexpr double kMaxSpeed = 500/3.6; // m/s
  static constexpr double kRecoilTime = 0.05; // s
};




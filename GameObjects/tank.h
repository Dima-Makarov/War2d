#pragma once

#include <QObject>
#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>
#include <Utils/vec2f.h>
#include "bullet.h"
#include "vehicle.h"

class Tank : public Vehicle {
  Q_OBJECT
 public:
  Tank(const Vec2f& position, const Vec2f& orientation);

  void Update(int millis) override;
  Vec2f GetTurretOrientation();
  QPixmap GetPixmap() const override;

 private:
  static constexpr double kHullAngularRotatingSpeed = 40.0 / 360 * 2 * M_PI; // rad/s
  static constexpr double kTurretAngularRotatingSpeed = 60.0 / 360 * 2 * M_PI; // rad/s
  static constexpr double kForwardAcceleration = 10; // m/s^2
  static constexpr double kMaxSpeed = 50/3.6; // m/s
  static constexpr double kRecoilTime = 1; // s

  Vec2f turret_orientation_;
};




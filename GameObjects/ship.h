#pragma once

#include <QObject>
#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>
#include <Utils/vec2f.h>
#include "bullet.h"
#include "vehicle.h"

class Ship : public Vehicle {
 Q_OBJECT
 public:
  Ship(const Vec2f& position, const Vec2f& orientation);

  void Update(int millis) override;
  Vec2f GetTurretOrientation();
  QPixmap GetPixmap() const override;

 private:
  static constexpr double kHullAngularRotatingSpeed = 10.0 / 360 * 2 * M_PI; // rad/s
  static constexpr double kTurretAngularRotatingSpeed = 40.0 / 360 * 2 * M_PI; // rad/s
  static constexpr double kForwardAcceleration = 2; // m/s^2
  static constexpr double kMaxSpeed = 100/3.6; // m/s
  static constexpr double kRecoilTime = 4; // s

  Vec2f turret_orientation_;
};






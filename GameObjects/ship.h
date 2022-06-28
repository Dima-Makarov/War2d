#pragma once

#include <QObject>
#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>
#include <Model/vec2f.h>
#include "bullet.h"
#include "game_object.h"

class Ship : public GameObject {
 Q_OBJECT
 public:
  Ship(const Vec2f& position);

  void Update(int millis) override;
  Vec2f GetTurretOrientation();
  double GetHp() const;
  bool IsAlive() const;
  void TakeDamage();
  QPixmap GetPixmap() const override;


  void keyPressEvent(QKeyEvent* event);
  void keyReleaseEvent(QKeyEvent*);
  void mousePressEvent(QMouseEvent* event);
  void mouseReleaseEvent(QMouseEvent* event);
  void mouseMoveEvent(QMouseEvent* event);

 signals:
  void Shoot(Vec2f position, Vec2f orientation);

 private:
  static constexpr double kHullAngularRotatingSpeed = 10.0 / 360 * 2 * M_PI; // rad/s
  static constexpr double kTurretAngularRotatingSpeed = 40.0 / 360 * 2 * M_PI; // rad/s
  static constexpr double kForwardAcceleration = 2; // m/s^2
  static constexpr double kMaxSpeed = 100/3.6; // m/s
  static constexpr double kRecoilTime = 4; // s

  bool is_shooting_ = false;
  bool up_pressed_ = false;
  bool down_pressed_ = false;
  bool left_pressed_ = false;
  bool right_pressed_ = false;

  Vec2f vector_to_mouse_;
  QTimer recoil_timer;
  double hp_;
  double speed_;
  Vec2f turret_orientation_;
  bool is_alive_ = true;
};






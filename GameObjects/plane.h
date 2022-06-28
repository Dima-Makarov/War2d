#pragma once

#include <QTimer>
#include <QPixmap>
#include <QKeyEvent>
#include <QMouseEvent>

#include "game_object.h"

class Plane : public GameObject {
 Q_OBJECT
 public:
  Plane(const Vec2f& position);

  void Update(int millis) override;
  double GetHp() const;
  bool IsAlive() const;
  void TakeDamage();
  QPixmap GetPixmap() const override;

  void keyPressEvent(QKeyEvent* event);
  void keyReleaseEvent(QKeyEvent*);
  void mousePressEvent(QMouseEvent* event);
  void mouseReleaseEvent(QMouseEvent* event);

 signals:
  void Shoot(Vec2f position, Vec2f orientation);

 private:
  static constexpr double kAngularRotatingSpeed = 50.0 / 360 * 2 * M_PI; // rad/s
  static constexpr double kForwardAcceleration = 30; // m/s^2
  static constexpr double kMaxSpeed = 500/3.6; // m/s
  static constexpr double kRecoilTime = 0.1; // s

  bool is_shooting_ = false;
  bool up_pressed_ = false;
  bool down_pressed_ = false;
  bool left_pressed_ = false;
  bool right_pressed_ = false;

  QTimer recoil_timer;
  double hp_;
  double speed_;
  bool is_alive_ = true;
};




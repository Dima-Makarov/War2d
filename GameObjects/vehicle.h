#pragma once
#include "GameObjects/game_object.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QTimer>

class Vehicle : public GameObject {
 Q_OBJECT
 public:
  Vehicle(Vec2f position, Vec2f orientation);
  void Update(int millis) override = 0;
  double GetHp() const;
  bool IsAlive() const;
  void TakeDamage();
  QPixmap GetPixmap() const override = 0;

 public:
  void keyPressEvent(QKeyEvent* event);
  void keyReleaseEvent(QKeyEvent*);
  void mousePressEvent(QMouseEvent* event);
  void mouseReleaseEvent(QMouseEvent* event);
  void mouseMoveEvent(QMouseEvent* event);

 signals:
  void Shoot(Vec2f position, Vec2f orientation);

 protected:
  bool is_shooting_ = false;
  bool up_pressed_ = false;
  bool down_pressed_ = false;
  bool left_pressed_ = false;
  bool right_pressed_ = false;
  QPoint mouse_coordinates_;
  QTimer recoil_timer;
  double hp_ = 100;
  double speed_ = 0;
  bool is_alive_ = true;
};




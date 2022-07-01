#pragma once
#include "GameObjects/game_object.h"
#include "Utils/pixmap_loader.h"
#include <QKeyEvent>
#include <QMouseEvent>
#include <QTimer>

class Vehicle : public GameObject {
 Q_OBJECT
 public:
  struct TurretData {
    TurretData(const QPixmap& pixmap,
               const Vec2f& offset_from_center,
               const Vec2f& orientation,
               double length_,
               double bullet_length_)
        : pixmap(pixmap),
          initial_offset(offset_from_center),
          offset(initial_offset),
          orientation(orientation),
          length(length_),
          bullet_length(bullet_length_) {}

    QPixmap pixmap;
    Vec2f initial_offset;
    Vec2f offset;
    Vec2f orientation;
    double length;
    double bullet_length;
  };

  Vehicle(Vec2f position, Vec2f orientation);
  void Update(int millis) override = 0;
  double GetHp() const;
  bool IsAlive() const;
  void TakeDamage(double damage);
  QPixmap GetPixmap() const override = 0;
  double GetLength() const override = 0;
  virtual std::vector<TurretData> GetTurrets() const;

 public:
  void keyPressEvent(QKeyEvent* event);
  void keyReleaseEvent(QKeyEvent*);
  void mousePressEvent(QMouseEvent* event);
  void mouseReleaseEvent(QMouseEvent* event);
  void mouseMoveEvent(QMouseEvent* event);

 signals:
  void Shoot(Vec2f position, Vec2f orientation, double speed, double damage, double bullet_length);

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
  std::vector<TurretData> turrets_;
};

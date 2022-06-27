#pragma once

#include <GameObjects/tank.h>
#include <QPixmap>
#include <QKeyEvent>

class PlayerTank : public Tank {
 public:
  explicit PlayerTank(const Vec2f& position);
  QPixmap GetPixmap() const override;
  void Update(int millis) override;

 public:
  void keyPressEvent(QKeyEvent* event);
  void keyReleaseEvent(QKeyEvent*);
  void mousePressEvent(QMouseEvent* event);
  void mouseReleaseEvent(QMouseEvent* event);
  void mouseMoveEvent(QMouseEvent* event);

 private:
  bool is_shooting_ = false;
  bool up_pressed_ = false;
  bool down_pressed_ = false;
  bool left_pressed_ = false;
  bool right_pressed_ = false;
};





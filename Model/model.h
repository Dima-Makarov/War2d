
#pragma once

#include <QKeyEvent>
#include "GameObjects/tank.h"
#include "weapon_handler.h"
#include "GameObjects/player_tank.h"

class Model : public QObject {
  Q_OBJECT

 public:
  Model(int width, int height);
  void Update(int millis);
  void HandleKeyPressEvent(QKeyEvent* event);
  void HandleKeyReleaseEvent(QKeyEvent* event);
  void HandleMousePressEvent(QMouseEvent* event);
  void HandleMouseReleaseEvent(QMouseEvent* event);
  void HandleMouseMoveEvent(QMouseEvent* event);
  std::vector<GameObject*> GetGameObjects() const;

 private:
  WeaponHandler weapon_handler_;
  PlayerTank player_;
  std::vector<Tank*> soldiers_;
  std::vector<Bullet*> bullets_;
};

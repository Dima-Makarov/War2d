
#pragma once

#include <QKeyEvent>
#include <GameObjects/plane.h>
#include "GameObjects/tank.h"
#include "GameObjects/ship.h"
#include "weapon_handler.h"

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
  Tank tank_;
  Plane plane_;
  Ship ship_;
  std::vector<Tank*> tanks_;
  std::vector<Plane*> planes_;
  std::vector<Ship*> ships_;
  std::vector<Bullet*> bullets_;
};

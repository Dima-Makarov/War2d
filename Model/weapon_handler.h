#pragma once
#include <QObject>
#include "GameObjects/tank.h"
#include "GameObjects/bullet.h"

class WeaponHandler : public QObject {
  Q_OBJECT
 public:
  WeaponHandler(std::vector<Tank*>* soldiers, std::vector<Bullet*>* bullets);
  void Update();
  void Connect();

 private:
  std::vector<Tank*>* soldiers_;
  std::vector<Bullet*>* bullets_;
  void AddBullet(Vec2f position, Vec2f orientation);
  double soldier_radius = 20;
};




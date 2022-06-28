#pragma once
#include <QObject>
#include "GameObjects/tank.h"
#include "GameObjects/bullet.h"
#include "GameObjects/plane.h"

class WeaponHandler : public QObject {
  Q_OBJECT
 public:
  WeaponHandler(std::vector<Tank*>* tanks, std::vector<Plane*>* planes, std::vector<Bullet*>* bullets);
  void Update();
  void Connect();

 private:
  std::vector<Tank*>* tanks_;
  std::vector<Plane*>* planes_;
  std::vector<Bullet*>* bullets_;
  void AddBullet(Vec2f position, Vec2f orientation);
  double soldier_radius = 20;
};




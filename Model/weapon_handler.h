#pragma once
#include <QObject>
#include "GameObjects/tank.h"
#include "GameObjects/bullet.h"
#include "GameObjects/plane.h"
#include "GameObjects/ship.h"

class WeaponHandler : public QObject {
 Q_OBJECT
 public:
  WeaponHandler(std::vector<Vehicle*>* vehicles,
                std::vector<Bullet*>* bullets);
  void Update();
  void Connect();

 private:
  std::vector<Vehicle*>* vehicles_;
  std::vector<Bullet*>* bullets_;
  void AddBullet(Vec2f position, Vec2f orientation, double speed, double damage);
  double vehicle_radius = 20;
};

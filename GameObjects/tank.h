#pragma once

#include <QObject>
#include <QTimer>
#include <Model/vec2f.h>
#include "bullet.h"
#include "game_object.h"

class Tank : public GameObject {
  Q_OBJECT
 public:
  enum Team {
    bot,
    player
  };

  Tank(Team team, const Vec2f& position);

  void Update(int millis) override = 0;
  Team GetTeam() const;
  double GetHp() const;
  bool IsAlive() const;
  void TakeDamage();
  signals:
  void Shoot(Vec2f position, Vec2f orientation);

 protected:
  QTimer recoil_timer;
  Team team_;
  double hp_;
  double speed_;
  Vec2f turret_orientation_;
  bool is_alive_ = true;
};




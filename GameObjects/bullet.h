#pragma once

#include <QObject>

#include <Utils/vec2f.h>
#include <QPixmap>
#include "game_object.h"

class Bullet : public GameObject {
 public:
  Bullet(const Vec2f& position, const Vec2f& orientation, double speed, double damage);
  void Update(int millis) override;
  QPixmap GetPixmap() const override;
  double GetDamage() const;
 private:
  double speed_;
  double damage_;
};

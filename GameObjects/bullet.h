#pragma once

#include <QObject>

#include <Utils/vec2f.h>
#include <QPixmap>
#include "game_object.h"

class Bullet : public GameObject {
 public:
  Bullet(const Vec2f& position, const Vec2f& orientation, double speed, double damage, double length);
  void Update(int millis) override;
  QPixmap GetPixmap() const override;
  double GetDamage() const;
  double GetLength() const override;
  const Vec2f& GetInitialPosition() const;

 private:
  double speed_;
  double damage_;
  double length_;
  const Vec2f initial_position_;
};

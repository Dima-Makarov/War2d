#pragma once

#include <QObject>

#include <Model/vec2f.h>
#include <QPixmap>
#include "game_object.h"

class Bullet : public GameObject {
 public:
  Bullet(const Vec2f& position, const Vec2f& orientation);
  void Update(int millis) override;
  QPixmap GetPixmap() const override;

 private:
  double speed_ = 300;
  double damage_ = 20;
};

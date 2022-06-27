
#pragma once

#include "tank.h"
#include <QPixmap>

class BotTank : public Tank {
 public:
  BotTank(const Vec2f& position, std::vector<Tank*>* soldiers);
  QPixmap GetPixmap() const override;
  void Update(int millis) override;

 private:
  std::vector<Tank*>* soldiers_;
  Tank* FindNearestEnemySoldier();
};




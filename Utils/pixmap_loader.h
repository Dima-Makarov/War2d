#pragma once

#include <QPixmap>

class PixmapLoader {
 private:
  static PixmapLoader* instance;

 private:
  PixmapLoader() = default;

 public:
  PixmapLoader(const PixmapLoader&) = delete;
  PixmapLoader& operator=(PixmapLoader&) = delete;

 public:
  static PixmapLoader* Instance() {
    if (!instance)
      instance = new PixmapLoader();
    return instance;
  }

  const QPixmap tank = QPixmap("../Pictures/tank");
  const QPixmap tank_turret = QPixmap("../Pictures/tank_turret");
  const QPixmap ship_turret = QPixmap("../Pictures/ship_turret");
  const QPixmap plane = QPixmap("../Pictures/plane");
  const QPixmap ship = QPixmap("../Pictures/ship");
  const QPixmap bullet = QPixmap("../Pictures/bullet");
};

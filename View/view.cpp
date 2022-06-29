#include "view.h"
#include <iostream>

View::View(Model* model)
    : model_(model) {}

void View::Update(QPainter* painter) {
  std::vector<GameObject*> game_objects = model_->GetGameObjects();
  QPixmap buffer(painter->window().size());
  QPainter buffer_painter;
  buffer_painter.begin(&buffer);

  // temporary code, need to draw map instead
  buffer_painter.fillRect(0, 0, painter->window().width(), painter->window().height(), Qt::black);

  for (auto game_object: game_objects) {
    int pos_x = game_object->GetPosition().GetX();
    int pos_y = game_object->GetPosition().GetY();
    buffer_painter.save();
    buffer_painter.translate(pos_x, pos_y);
    buffer_painter.rotate(game_object->GetOrientation().GetAngleDegrees());
    QSize pixmap_size = game_object->GetPixmap().size() * scale_;
    QPixmap pixmap = game_object->GetPixmap().scaled(pixmap_size);
    int pix_width = pixmap.width();
    int pix_height = pixmap.height();
    buffer_painter.drawPixmap(-pix_width / 2, -pix_height / 2, pixmap);
    auto* tank = dynamic_cast<Tank*>(game_object);
    buffer_painter.rotate(-game_object->GetOrientation().GetAngleDegrees());

    QSize turret_size = PixmapLoader::Instance()->turret.size() * scale_;
    QPixmap turret = PixmapLoader::Instance()->turret.scaled(turret_size);
    if (tank) {
      buffer_painter.rotate(tank->GetTurretOrientation().GetAngleDegrees());
      buffer_painter.drawPixmap(-turret.width() / 2, -turret.height() / 2, turret);
      buffer_painter.rotate(-tank->GetTurretOrientation().GetAngleDegrees());
    }
    auto* ship = dynamic_cast<Ship*>(game_object);
    if (ship) {
      buffer_painter.rotate(ship->GetTurretOrientation().GetAngleDegrees());
      buffer_painter.drawPixmap(-turret.width() / 2, -turret.height() / 2, turret);
      buffer_painter.rotate(-ship->GetTurretOrientation().GetAngleDegrees());
    }
    buffer_painter.restore();
  }
  buffer_painter.end();
  painter->drawPixmap(0, 0, buffer);
}

void View::Zoom(int steps_number) {
  scale_ += steps_number * scale_step_;
  if (scale_ > max_scale_) {
    scale_ = max_scale_;
  } else if (scale_ < min_scale_) {
    scale_ = min_scale_;
  }
}

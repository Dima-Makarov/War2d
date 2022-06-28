#include <iostream>
#include "view.h"

View::View(Model* model)
    : model_(model) {}

void View::Update(QPainter* painter) {
  std::vector<GameObject*> game_objects = model_->GetGameObjects();
  QPixmap buffer(painter->window().size());
  QPainter buffer_painter;
  buffer_painter.begin(&buffer);
  for (auto game_object : game_objects) {
    int pos_x = game_object->GetPosition().GetX();
    int pos_y = game_object->GetPosition().GetY();
    buffer_painter.save();
    buffer_painter.translate(pos_x, pos_y);
    buffer_painter.rotate(game_object->GetOrientation().GetAngleDegrees());
    QPixmap pixmap = game_object->GetPixmap();
    int pix_width = pixmap.width();
    int pix_height = pixmap.height();
    buffer_painter.drawPixmap(-pix_width / 2, -pix_height / 2, pixmap);
    auto* tank = dynamic_cast<Tank*>(game_object);
    buffer_painter.rotate(-game_object->GetOrientation().GetAngleDegrees());
    QPixmap turret = PixmapLoader::Instance()->turret;
    if(tank) {
      buffer_painter.rotate(tank->GetTurretOrientation().GetAngleDegrees());
      buffer_painter.drawPixmap(-turret.width()/2,-turret.height()/2,turret);
      buffer_painter.rotate(-tank->GetTurretOrientation().GetAngleDegrees());
    }
    auto* ship = dynamic_cast<Ship*>(game_object);
    if(ship) {
      buffer_painter.rotate(ship->GetTurretOrientation().GetAngleDegrees());
      buffer_painter.drawPixmap(-turret.width()/2,-turret.height()/2,turret);
      buffer_painter.rotate(-ship->GetTurretOrientation().GetAngleDegrees());
    }
    buffer_painter.restore();
  }
  buffer_painter.end();
  painter->drawPixmap(0,0,buffer);
}

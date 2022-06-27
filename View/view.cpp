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
    buffer_painter.restore();
    Tank* soldier;
    soldier = dynamic_cast<Tank*>(game_object);
    if (soldier && soldier->IsAlive()) {
      buffer_painter.save();
      buffer_painter.translate(pos_x, pos_y);
      buffer_painter.setPen(QPen(QBrush(Qt::green), 3));
      buffer_painter.drawLine(-20, -20, -20 + soldier->GetHp() / 3, -20);
      buffer_painter.setPen(QPen(QBrush(Qt::red), 3));
      buffer_painter.drawLine(-20 + soldier->GetHp() / 3, -20, -20 + 100 / 3, -20);
      buffer_painter.restore();
    }
  }
  buffer_painter.end();
  painter->drawPixmap(0,0,buffer);
}

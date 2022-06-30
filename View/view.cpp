#include "view.h"
#include <iostream>

View::View(Model* model)
    : model_(model) {}

void View::Update(QPainter* painter) {
  std::vector<GameObject*> game_objects = model_->GetGameObjects();
  QPixmap buffer(painter->window().size());
  QPainter buffer_painter;
  buffer_painter.begin(&buffer);

  Vec2f center = Vec2f((double)buffer.width() / 2, (double)buffer.height() / 2);
  if(Player::Instance()->GetVehicle() == nullptr) {
    return;
  }
  Vec2f player_vehicle_pos = Player::Instance()->GetVehicle()->GetPosition();

  // temporary code, need to draw map instead
  buffer_painter.fillRect(0, 0, painter->window().width(), painter->window().height(), Qt::white);
  for (auto game_object: game_objects) {

    double pos_x = game_object->GetPosition().GetX()*scale_ - player_vehicle_pos.GetX()*scale_;
    double pos_y = game_object->GetPosition().GetY()*scale_ - player_vehicle_pos.GetY()*scale_;
    buffer_painter.save();
    buffer_painter.scale(scale_, scale_);
    buffer_painter.translate((pos_x + center.GetX())/scale_, (pos_y + center.GetY())/scale_);
    buffer_painter.rotate(game_object->GetOrientation().GetAngleDegrees());

    QPixmap pixmap = game_object->GetPixmap();
    int pix_width = pixmap.width();
    int pix_height = pixmap.height();
    double scale_coef = pixmap.width() / (game_object->GetLength());
    buffer_painter.scale(1.0/scale_coef, 1.0/scale_coef);
    buffer_painter.drawPixmap(-pix_width / 2, -pix_height / 2, pixmap);
    buffer_painter.scale(scale_coef, scale_coef);
    buffer_painter.rotate(-game_object->GetOrientation().GetAngleDegrees());
    auto* vehicle = dynamic_cast<Vehicle*>(game_object);
    if (vehicle) {
      for(const auto& turret : vehicle->GetTurrets()) {
        scale_coef = (double)turret.pixmap.width() / (turret.length);
        buffer_painter.translate(turret.offset.GetX(), turret.offset.GetY());
        buffer_painter.rotate(turret.orientation.GetAngleDegrees());
        buffer_painter.scale(1.0/scale_coef, 1.0/scale_coef);
        buffer_painter.drawPixmap(-turret.pixmap.width() / 2, -turret.pixmap.height() / 2, turret.pixmap);
        buffer_painter.scale(scale_coef, scale_coef);
        buffer_painter.rotate(-turret.orientation.GetAngleDegrees());
        buffer_painter.translate(-turret.offset.GetX(), -turret.offset.GetY());
      }
    }
    buffer_painter.restore();
  }
  buffer_painter.end();
  painter->drawPixmap(0, 0, buffer);
}

void View::Zoom(int steps_number) {
  double inc = steps_number * kScaleStep;
  inc *= scale_ / kMaxScale;
  scale_ += inc;
  if (scale_ > kMaxScale) {
    scale_ = kMaxScale;
  } else if (scale_ < kMinScale) {
    scale_ = kMinScale;
  }
}

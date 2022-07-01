#include "view.h"
#include <iostream>

View::View(Model* model)
    : model_(model) {}

void View::Update(QPainter* painter) {
  std::vector<GameObject*> game_objects = model_->GetGameObjects();
  QPixmap buffer(painter->window().size());
  QPainter buffer_painter;
  buffer_painter.begin(&buffer);

  Vec2f center = Vec2f((double) buffer.width() / 2, (double) buffer.height() / 2);
  if (Player::Instance()->GetVehicle() == nullptr) {
    return;
  }
  Vec2f player_vehicle_pos = Player::Instance()->GetVehicle()->GetPosition();

  // temporary code, need to draw map instead
  buffer_painter.fillRect(0, 0, painter->window().width(), painter->window().height(), Qt::white);
  for (auto game_object : game_objects) {
    Vec2f pos = game_object->GetPosition() * scale_ - player_vehicle_pos * scale_;
    buffer_painter.save();
    buffer_painter.scale(scale_, scale_);

    buffer_painter.translate((pos.GetX() + center.GetX()) / scale_,
                             (pos.GetY() + center.GetY()) / scale_);

    DrawScaledPixmap(buffer_painter,
                     game_object->GetOrientation(),
                     game_object->GetPixmap(),
                     game_object->GetLength());

    auto* vehicle = dynamic_cast<Vehicle*>(game_object);
    if (vehicle) {
      DrawTurrets(buffer_painter, vehicle);
    }

    buffer_painter.restore();
  }
  buffer_painter.end();
  painter->drawPixmap(0, 0, buffer);
}

void View::DrawTurrets(QPainter& buffer_painter, const Vehicle* vehicle) const {
  for (const auto& turret : vehicle->GetTurrets()) {
    buffer_painter.translate(turret.offset.GetX(), turret.offset.GetY());
    DrawScaledPixmap(buffer_painter, turret.orientation, turret.pixmap, turret.length);
    buffer_painter.translate(-turret.offset.GetX(), -turret.offset.GetY());
  }
}

void View::DrawScaledPixmap(QPainter& buffer_painter,
                            const Vec2f& orientation,
                            const QPixmap& pixmap,
                            double length) const {
  double scale_coef = (double) pixmap.width() / length;
  buffer_painter.rotate(orientation.GetAngleDegrees());
  buffer_painter.scale(1.0 / scale_coef, 1.0 / scale_coef);
  buffer_painter.drawPixmap(-pixmap.width() / 2,
                            -pixmap.height() / 2,
                            pixmap);
  buffer_painter.scale(scale_coef, scale_coef);
  buffer_painter.rotate(-orientation.GetAngleDegrees());
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

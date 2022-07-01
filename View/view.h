
#pragma once

#include "Model/model.h"
#include <QPainter>

class View {
 public:
  static constexpr double kScaleStep = 5;
  static constexpr double kMaxScale = 62.5;
  static constexpr double kMinScale = 1;

 public:
  explicit View(Model* model);
  void Update(QPainter* painter);

  void Zoom(int steps_number);

 private:
  Model* model_;
  double scale_ = 1;
  void DrawTurrets(QPainter& buffer_painter, const Vehicle* vehicle) const;
  void DrawScaledPixmap(QPainter& buffer_painter,
                        const Vec2f& orientation,
                        const QPixmap& pixmap,
                        double length) const;
};

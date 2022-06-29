
#pragma once

#include "Model/model.h"
#include <QPainter>

class View {
 public:
  static constexpr double scale_step_ = 0.1;
  static constexpr double max_scale_ = 5;

 public:
  explicit View(Model* model);
  void Update(QPainter* painter);

  void Zoom(int steps_number);

 private:
  Model* model_;
  double scale_ = 1;
};

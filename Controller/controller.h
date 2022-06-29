
#pragma once

#include <QKeyEvent>
#include <QMainWindow>
#include <QPainter>
#include <QTimer>
#include <QWidget>
#include <QWheelEvent>

#include "Model/model.h"
#include "View/view.h"

class Controller : public QWidget {
  Q_OBJECT
 public:
  explicit Controller(QWidget* parent);
  ~Controller() override;
  void keyPressEvent(QKeyEvent*) override;
  void keyReleaseEvent(QKeyEvent*) override;
  void paintEvent(QPaintEvent*) override;
  void mousePressEvent(QMouseEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* event) override;
  void mouseMoveEvent(QMouseEvent* event) override;
  void wheelEvent(QWheelEvent* event) override;

 private:
  void TimerEvent();
  Model* model_;
  View* view_;
  QTimer tick_timer_;
  long long prev_millis_;
  static constexpr int kMillisPerTick = 16;
  double current_fps_ = 0;
};

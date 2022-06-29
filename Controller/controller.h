
#pragma once

#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QTimer>
#include <QMainWindow>

#include "View/view.h"
#include "Model/model.h"

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

 private:
  void TimerEvent();
  Model* model_;
  View* view_;
  QTimer tick_timer_;
  long long prev_millis_;
  static constexpr int kMillisPerTick = 16;
  double current_fps_ = 0;
};

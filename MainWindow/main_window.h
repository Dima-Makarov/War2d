#pragma once

#include <QMainWindow>
#include <QStackedWidget>
#include "Controller/controller.h"
#include "hangar.h"

class MainWindow : public QMainWindow {
  Q_OBJECT
 public:
  MainWindow();
  void StartGame();
  void resizeEvent(QResizeEvent*) override;

 private:
  QStackedWidget stacked_widget_;
  Controller* controller_ = nullptr;
  Hangar* hangar_ = nullptr;
};

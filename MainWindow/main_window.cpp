#include "main_window.h"

MainWindow::MainWindow() : QMainWindow(nullptr), stacked_widget_(this), hangar_(new Hangar()) {
  resize(1500, 700);
  setFocusPolicy(Qt::StrongFocus);
  setCentralWidget(&stacked_widget_);
  stacked_widget_.addWidget(hangar_);
  connect(hangar_, &Hangar::ToBattle, this, &MainWindow::StartGame);
}

void MainWindow::resizeEvent(QResizeEvent*) {
  stacked_widget_.setGeometry(0, 0, width(), height());
}

void MainWindow::StartGame() {
  controller_ = new Controller(this);
  stacked_widget_.addWidget(controller_);
  stacked_widget_.setCurrentWidget(controller_);
}

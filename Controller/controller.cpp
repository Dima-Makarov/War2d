
#include "controller.h"

using namespace std::chrono;

Controller::Controller() : QWidget(nullptr),
                           model_(new Model(window()->width(), window()->height())),
                           view_(new View(model_)),
                           tick_timer_(),
                           prev_millis_(duration_cast<milliseconds>(
                               high_resolution_clock::now()
                                   - high_resolution_clock::from_time_t(0)).count()) {
  tick_timer_.start(kMillisPerTick);
  connect(&tick_timer_,
          &QTimer::timeout,
          this,
          &Controller::TimerEvent);
  resize(1500, 700);
  setMouseTracking(true);
}

void Controller::TimerEvent() {
  auto epoch = high_resolution_clock::from_time_t(0);
  auto now = high_resolution_clock::now();
  auto mseconds = duration_cast<milliseconds>(now - epoch).count();

  model_->Update(mseconds - prev_millis_);
  prev_millis_ = mseconds;
  repaint();
}

void Controller::paintEvent(QPaintEvent*) {
  QPainter qp(this);
  view_->Update(&qp);
}

Controller::~Controller() {
  delete view_;
  delete model_;
}

void Controller::keyPressEvent(QKeyEvent* event) {
  model_->HandleKeyPressEvent(event);
}

void Controller::keyReleaseEvent(QKeyEvent* event) {
  model_->HandleKeyReleaseEvent(event);
}

void Controller::mousePressEvent(QMouseEvent* event) {
  model_->HandleMousePressEvent(event);
}

void Controller::mouseReleaseEvent(QMouseEvent* event) {
  model_->HandleMouseReleaseEvent(event);
}

void Controller::mouseMoveEvent(QMouseEvent* event) {
  model_->HandleMouseMoveEvent(event);
}

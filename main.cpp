#include <iostream>
#include <QMainWindow>
#include <QApplication>
#include "Controller/controller.h"

int main(int argc, char* argv[]) {
  QApplication qapp(argc, argv);
  Controller controller;
  controller.show();
  return QApplication::exec();
}

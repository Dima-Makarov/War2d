#include <iostream>
#include <QMainWindow>
#include <QApplication>
#include "MainWindow/main_window.h"

int main(int argc, char* argv[]) {
  QApplication qapp(argc, argv);
  MainWindow main_window;
  main_window.show();
  return QApplication::exec();
}

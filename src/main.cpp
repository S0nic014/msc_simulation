#include <QtWidgets/QApplication>
#include <QtWidgets/QStyleFactory>
#include <iostream>
#include "MainWindow.h"

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  app.setStyle(QStyleFactory::create("fusion"));
  app.setPalette(*MainWindow::darkPalette());
  // Main window
  MainWindow mainWin;
  mainWin.resize(1024, 720);
  mainWin.show();

  return app.exec();
}

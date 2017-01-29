#include <iostream>
#include "front_end.h"
#include <QApplication>

using namespace std;

int main(int argc, char* argv[])
{

  QApplication app(argc, argv);
  FrontEnd mainWindow(argv[1]);
  mainWindow.show();
  return app.exec();
}
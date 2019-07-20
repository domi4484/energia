
// Project includes ---------------------------------------
#include "MainWindow.h"

// Qt includes --------------------------------------------
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication qApplication(argc, argv);
  qApplication.setApplicationName("Energia");
  qApplication.setOrganizationDomain("customcut.ch");
  qApplication.setApplicationVersion("0.1.0");

  MainWindow mainWindow;
  mainWindow.show();

  return qApplication.exec();
}

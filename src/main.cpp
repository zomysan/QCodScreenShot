#include "mainwindow.h"
#include "settings.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QTranslator>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);

  // translate
  QTranslator translator;
  QString lang = Settings::value(Settings::Language);
  translator.load(QString("translate/qcss_") + lang);
  a.installTranslator(&translator);

  MainWindow w;
  w.initialize();

  // get screen that shows this app window
  QRect screen = QApplication::desktop()->availableGeometry(&w);
  QRect geometry = w.geometry();

  // Show at bottom-left of screen
  int margin = 10;
  w.move(screen.right() - geometry.width() - margin,
         screen.bottom() - geometry.height() - margin);
  w.show();

  return a.exec();
}

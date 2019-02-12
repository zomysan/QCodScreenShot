#ifndef SAVE_H
#define SAVE_H

#include <QtCore>

class ScreenShotSaver
{
  Q_DECLARE_TR_FUNCTIONS(MyClass)
public:
  ScreenShotSaver();
  static void save(QPixmap pixmap);

private:
  static bool checkSaveOk(QString filepath);
};

#endif // SAVE_H

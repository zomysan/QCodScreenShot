#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class SettingDialog;
class ScreenShotDialog;
class CountDownAction;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT
private:
  Ui::MainWindow *ui;
  SettingDialog *settingDialog_;
  ScreenShotDialog *screenShotDialog_;
  CountDownAction *countDownAction_;
  QPoint clickedPos_;

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  void initialize();

protected:
  void mousePressEvent(QMouseEvent *e);
  void mouseReleaseEvent(QMouseEvent *e);
  void mouseMoveEvent(QMouseEvent *e);

private slots:
  void beginTimerScreenShot();
  void updateTimerLabel(int restSec);
  void takeScreenShot();
};

#endif // MAINWINDOW_H

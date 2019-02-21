#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QDialog>
#include <QMouseEvent>

class ScreenShotDialog : public QDialog
{
  Q_OBJECT
private:
  QPixmap screenShotPixmap_;
  QPoint startPos_;
  QPoint endPos_;
  QPoint cursolPos_;
  bool arrowPosSelecting_;
  QPoint arrowAbsolutePos_;

public:
  explicit ScreenShotDialog(QWidget *parent = 0);

public slots:
  void beginSelectArea();
  void storeScreenShot();

protected:
  void paintEvent(QPaintEvent *);

protected:
  void mouseMoveEvent(QMouseEvent *e);
  void mousePressEvent(QMouseEvent *e);
  void mouseReleaseEvent(QMouseEvent *e);

private:
  void takePartShot();
  QRect getCorrectedRect();
};

#endif // SCREENSHOT_H

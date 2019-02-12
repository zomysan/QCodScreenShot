#include "screenshotdialog.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QGuiApplication>
#include <QScreen>
#include <QPainter>
#include <QDebug>
#include "screenshotsaver.h"

ScreenShotDialog::ScreenShotDialog(QWidget *parent) :
  QDialog(parent)
{
  setMouseTracking(true);
}

void ScreenShotDialog::beginSelectArea()
{
  startPos_ = QPoint(0, 0);
  endPos_ = QPoint(0, 0);

  setGeometry(QApplication::desktop()->screenGeometry());
  showFullScreen();
}

void ScreenShotDialog::storeScreenShot()
{
  screenShotPixmap_ = QGuiApplication::screens().at(0)->
      grabWindow(QApplication::desktop()->winId());
}

void ScreenShotDialog::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
  painter.setPen(Qt::NoPen);

  // create rect that size is same to screen size
  QRect screenRect = QApplication::desktop()->screen(0)->rect();
  painter.drawPixmap(screenRect,screenShotPixmap_);

  // draw rect path
  QPainterPath path;
  path.addRect(screenRect);
  if(startPos_.isNull() == false && endPos_.isNull() == false){
    path.addRect(QRect(startPos_, endPos_));
  }
  painter.setBrush(QBrush(QColor(0,0,0,100)));
  painter.drawPath(path);

  // draw cursor
  if(startPos_.isNull()) {
    painter.setPen(QPen(Qt::white, 1, Qt::DashLine, Qt::RoundCap));
    painter.drawLine(0, cursolPos_.y(), width(), cursolPos_.y());
    painter.drawLine(cursolPos_.x(), 0, cursolPos_.x(), height());
  }
}

void ScreenShotDialog::mouseMoveEvent(QMouseEvent *e)
{
  // set cursol pos(before dragging)
  if(e->buttons() == Qt::NoButton){
    cursolPos_ = e->pos();
  }
  // set end pos(while dragging)
  if(e->buttons() == Qt::LeftButton){
    endPos_ = e->pos();
  }
  repaint();
}

void ScreenShotDialog::mousePressEvent(QMouseEvent *e)
{
  if(e->button() == Qt::RightButton){
    close();
    return;
  }

  if(e->button() == Qt::LeftButton){
    // left click: fix start pos
    startPos_ = e->pos();
    return;
  }
}

void ScreenShotDialog::mouseReleaseEvent(QMouseEvent *e)
{
  // end of dragging: fix end pos
  endPos_ = e->pos();
  takePartShot();
}

void ScreenShotDialog::takePartShot()
{
  // left/right, top/bottom correction
  int left = startPos_.x();
  int right = endPos_.x();
  if(endPos_.x() < startPos_.x()) {
    left = endPos_.x();
    right = startPos_.x();
  }
  int top = startPos_.y();
  int bottom = endPos_.y();
  if(endPos_.y() < startPos_.y()) {
    top = endPos_.y();
    bottom = startPos_.y();
  }

  // copy selected area
  QPixmap pixmap = screenShotPixmap_.copy(
        QRect(QPoint(left, top), QPoint(right, bottom)));

  close();

  // save screenshot image
  ScreenShotSaver::save(pixmap);
}

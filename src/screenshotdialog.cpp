#include "screenshotdialog.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QGuiApplication>
#include <QScreen>
#include <QPainter>
#include "settings.h"
#include <QDebug>
#include <QFontMetrics>
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
  arrowPosSelecting_ = false;
  arrowAbsolutePos_ = QPoint(0, 0);

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
  if(startPos_.isNull() || arrowPosSelecting_) {
    painter.setPen(QPen(QColor(255, 255, 255, 100), 1, Qt::DashLine, Qt::RoundCap));
    if(arrowPosSelecting_){
      painter.setPen(QPen(QColor(0, 0, 0, 100), 1, Qt::DashLine, Qt::RoundCap));
    }
    painter.drawLine(0, cursolPos_.y(), width(), cursolPos_.y());
    painter.drawLine(cursolPos_.x(), 0, cursolPos_.x(), height());
  }

  // draw guide text
  if(arrowPosSelecting_) {
    painter.translate(getCorrectedRect().topLeft());
    painter.translate(5, 5);

    QFont font("Tahoma", 10);
    QString text = tr("Click cursor position.");
    painter.setFont(font);

    QFontMetrics m(font);
    QRect textRect = m.boundingRect(text);
    textRect = textRect.marginsAdded(QMargins(3,3,3,3));
    textRect.moveTopLeft(QPoint(0, 0));

    QColor bgColor = QColor(255, 255, 255, 200);
    painter.setBrush(bgColor);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(textRect, 3, 3);

    painter.setPen(Qt::black);
    painter.drawText(textRect, Qt::AlignCenter, text);
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
    if(arrowPosSelecting_){
      // abort add arrow
      arrowAbsolutePos_ = QPoint(0, 0);
      takePartShot();
    }
    close();
    return;
  }

  if(e->button() == Qt::LeftButton){
    // left click: fix start pos
    if(arrowPosSelecting_){
      arrowAbsolutePos_ = e->pos();
      return;
    }
    startPos_ = e->pos();
    return;
  }
}

void ScreenShotDialog::mouseReleaseEvent(QMouseEvent *e)
{
  if(arrowPosSelecting_){
    if(arrowAbsolutePos_ == e->pos()){
      // clicked -> fix
      takePartShot();
      return;
    }
    // dragged -> retry
    arrowAbsolutePos_ = QPoint(0, 0);
    return;
  }

  // end of dragging: fix end pos
  endPos_ = e->pos();

  // draw arrow pos?
  if(Settings::getInstance().drawArrow()){
    arrowPosSelecting_ = true;
  } else {
    takePartShot();
  }
}

void ScreenShotDialog::takePartShot()
{
  QRect rect = getCorrectedRect();

  // copy selected area
  QPixmap pixmap = screenShotPixmap_.copy(rect);

  close();

  // save screenshot image
  QPoint arrowPos = arrowAbsolutePos_ - rect.topLeft();
  ScreenShotSaver::save(pixmap, arrowPos);
}

QRect ScreenShotDialog::getCorrectedRect()
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

  return QRect(left, top, (right-left), (bottom-top));
}

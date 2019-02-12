#include "countdownaction.h"
#include <QTimer>

CountDownAction::CountDownAction(QObject *parent) : QObject(parent)
{

}

void CountDownAction::start(int delayTimeSec)
{
  countSec_ = delayTimeSec;
  elapsedSec_ = 0;

  QTimer::singleShot(1000, this, SLOT(timeout()));
}

void CountDownAction::timeout()
{
  elapsedSec_ += 1;
  if(countSec_ <= elapsedSec_){
    emit fired();
    return;
  }

  emit countDownTicked(countSec_ - elapsedSec_);
  QTimer::singleShot(1000, this, SLOT(timeout()));
}

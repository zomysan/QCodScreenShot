#ifndef SELFTIMERSCREENSHOT_H
#define SELFTIMERSCREENSHOT_H

#include <QObject>

class CountDownAction : public QObject
{
  Q_OBJECT
private:
  int countSec_;
  int elapsedSec_;

public:
  explicit CountDownAction(QObject *parent = 0);
  void start(int delayTimeSec);

signals:
  void fired();
  void countDownTicked(int rest);

private slots:
  void timeout();
};

#endif // SELFTIMERSCREENSHOT_H

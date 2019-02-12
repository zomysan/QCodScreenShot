#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "screenshotdialog.h"
#include "settingdialog.h"
#include "countdownaction.h"
#include "settings.h"
#include <QDebug>
#include <QToolTip>
#include <QTimer>
#include <QThread>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  settingDialog_(new SettingDialog(this)),
  screenShotDialog_(new ScreenShotDialog(this)),
  countDownAction_(new CountDownAction(this))
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::initialize()
{
  settingDialog_->initialize();

  setWindowFlags(Qt::FramelessWindowHint);
  if(Settings::getInstance().stayOnTop()){
    setWindowFlags(Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);
  }

  connect(ui->b_screenshot, SIGNAL(clicked()),
          SLOT(takeScreenShot()));
  connect(ui->b_setting, SIGNAL(clicked()),
          this->settingDialog_, SLOT(showDialog()));
  connect(ui->b_exit, SIGNAL(clicked()),
          SLOT(close()));
  connect(ui->b_timer, SIGNAL(clicked()),
          SLOT(beginTimerScreenShot()));
  connect(countDownAction_, SIGNAL(countDownTicked(int)),
          SLOT(updateTimerLabel(int)));
  connect(countDownAction_, SIGNAL(fired()),
          SLOT(takeScreenShot()));
}

// for window drag move
void MainWindow::mousePressEvent(QMouseEvent *e)
{
  if(ui->label->geometry().contains(e->pos())){
    clickedPos_ = e->pos();
  }
}

// for window drag move
void MainWindow::mouseReleaseEvent(QMouseEvent */*e*/)
{
  clickedPos_ = QPoint();
}

// for window drag move
void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
  if(clickedPos_.isNull() == false){
    move(e->globalPos() - clickedPos_);
  }
}

void MainWindow::beginTimerScreenShot()
{
  int time = Settings::getInstance().delaySecs();
  ui->b_timer->setText(QString("%1").arg(time));
  countDownAction_->start(time);
}

void MainWindow::updateTimerLabel(int restSec)
{
  ui->b_timer->setText(QString("%1").arg(restSec));
}

void MainWindow::takeScreenShot()
{
  ui->b_timer->setText("");
  screenShotDialog_->storeScreenShot();
  screenShotDialog_->beginSelectArea();
}

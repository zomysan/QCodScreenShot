#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
  Q_OBJECT

public:
  explicit SettingDialog(QWidget *parent = 0);
  ~SettingDialog();
  void initialize();

public slots:
  void selectFolder(void);
  void showDialog();

private slots:
  void finish(void);
  void updateSample();
  void updatePngSettingShowState();

private:
  Ui::SettingDialog *ui;
  void loadSettings();
  QString getLanguageFromUi();
  void setLanguageToUi(QString language);
};

#endif // SETTINGDIALOG_H

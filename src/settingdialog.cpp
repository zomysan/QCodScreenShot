#include "settingdialog.h"
#include "ui_settingdialog.h"

#include <QFileDialog>
#include "settings.h"

SettingDialog::SettingDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::SettingDialog)
{
  ui->setupUi(this);
}

SettingDialog::~SettingDialog()
{
  delete ui;
}

void SettingDialog::initialize()
{
  connect(ui->b_finish, SIGNAL(clicked()), SLOT(finish()));
  connect(ui->b_cancel, SIGNAL(clicked()), SLOT(close()));
  connect(ui->b_folder, SIGNAL(clicked()), SLOT(selectFolder()));
  connect(ui->le_filename, SIGNAL(textChanged(QString)), SLOT(updateSample()));
  connect(ui->cb_filetype, SIGNAL(currentIndexChanged(int)),
          SLOT(updatePngSettingShowState()));
  connect(ui->cb_filetype, SIGNAL(currentIndexChanged(int)),
          SLOT(updateSample()));

  // settingsクラスから設定を読み込む
  loadSettings();

  // ファイル名サンプル更新
  updateSample();
}

void SettingDialog::showDialog()
{
  // 設定を読み込んでから表示する
  loadSettings();
  show();
  setFixedSize(size());
}

void SettingDialog::selectFolder()
{
  // QFileDialogによってユーザにフォルダを選択させる
  QString folder = QFileDialog::getExistingDirectory(this,"screenshot save folder");

  // pathラベルのテキストに、ユーザが選択したフォルダへのパスを設定する
  ui->l_path->setText(folder);
}

void SettingDialog::finish()
{
  Settings &instance = Settings::getInstance();

  // Settingsクラスに設定を反映する
  Settings::getInstance().setFilename(ui->le_filename->text());
  Settings::getInstance().setLanguage(getLanguageFromUi());
  Settings::getInstance().setFiletype(ui->cb_filetype->currentText());
  Settings::getInstance().setPath(ui->l_path->text());
  Settings::getInstance().setOpenDialog(
        ui->cb_openDialog->isChecked());
  Settings::getInstance().setDrawArrow(
        ui->cb_drawArrow->isChecked());
  Settings::getInstance().setOverwriteConfirm(
        ui->cb_overwriteConfirm->isChecked());
  Settings::getInstance().setAggressivePngCompress(
        ui->cb_aggressivePngCompress->isChecked());
  Settings::getInstance().setForcePngAlpha(
        ui->cb_forcePngAlpha->isChecked());
  Settings::getInstance().setStayOnTop(
        ui->cb_stayOnTop->isChecked());
  Settings::getInstance().setDelaySecs(ui->sb_delaySecs->value());
  Settings::getInstance().setQuality(ui->sb_quality->value());

  // Setting書出
  Settings::getInstance().writeData();

  this->close();
}

void SettingDialog::updateSample()
{
  QString format = ui->le_filename->text();
  QString sampleName = QDateTime::currentDateTime().toString(format);
  ui->lb_filenameSample->setText(
        sampleName + "." + ui->cb_filetype->currentText());
}

void SettingDialog::updatePngSettingShowState()
{
  if(ui->cb_filetype->currentText() == "png"){
    ui->gb_png_setting->show();
  } else {
    ui->gb_png_setting->hide();
  }
}

void SettingDialog::loadSettings()
{
  // Settingsクラスから設定を読み込み、初期状態とする
  ui->l_path->setText(Settings::getInstance().path());
  setLanguageToUi(Settings::getInstance().language());
  ui->le_filename->setText(Settings::getInstance().filename());
  ui->cb_filetype->setCurrentText(Settings::getInstance().filetype());
  ui->cb_openDialog->setChecked(Settings::getInstance().openDialog());
  ui->cb_drawArrow->setChecked(Settings::getInstance().drawArrow());
  ui->cb_overwriteConfirm->setChecked(Settings::getInstance().overwriteConfirm());
  ui->cb_aggressivePngCompress->setChecked(Settings::getInstance().aggressivePngCompress());
  ui->cb_forcePngAlpha->setChecked(Settings::getInstance().forcePngAlpha());
  ui->cb_stayOnTop->setChecked(Settings::getInstance().stayOnTop());
  ui->sb_delaySecs->setValue(Settings::getInstance().delaySecs());
  ui->sb_quality->setValue(Settings::getInstance().quality());

  // 表示状態の更新
  updatePngSettingShowState();
}

QString SettingDialog::getLanguageFromUi()
{
  QString lang = ui->cb_language->currentText();
  lang = lang.toLower();
  lang.resize(2);
  return lang;
}

void SettingDialog::setLanguageToUi(QString language)
{
  for(int i = 0; i < ui->cb_language->count(); i++) {
    QString lang = ui->cb_language->itemText(i);;
    lang = lang.toLower();
    lang.resize(2);
    if(lang == language){
      ui->cb_language->setCurrentIndex(i);
    }
  }
}

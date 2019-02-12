#include "screenshotsaver.h"

#include <qpixmap.h>
#include <QDesktopServices>
#include "settings.h"
#include "imageconverter.h"
#include <QMessageBox>

ScreenShotSaver::ScreenShotSaver()
{
}

void ScreenShotSaver::save(QPixmap pixmap)
{
  QString filepath = Settings::getInstance().path();
  QString filename = QDateTime::currentDateTime().toString(
        Settings::getInstance().filename());
  QString filetype = Settings::getInstance().filetype();

  filepath += "/";
  filepath += filename;
  filepath += "." + filetype;

  // confirm overwrite
  bool saveOk = checkSaveOk(filepath);

  if(saveOk == false){
    return;
  }

  // make image alpha channel
  if(Settings::getInstance().forcePngAlpha()){
    if(filetype == "png"){
      pixmap = ImageConverter::convertToAlphaSecretly(pixmap);
    }
  }

  pixmap.save(filepath, filetype.toStdString().c_str(),
              Settings::getInstance().quality());

  // png quant
  if(Settings::getInstance().aggressivePngCompress() == true){
    if(filetype == "png"){
      QString command = "./pngquant.exe";
      QStringList args;
      args << "--force" << "--output" << filepath << filepath;
      QProcess::execute(command, args);
    }
  }

  // show in explorer
  if(Settings::getInstance().openDialog()){
    QDesktopServices::openUrl(
          QUrl(Settings::getInstance().path(), QUrl::TolerantMode));
  }
}

bool ScreenShotSaver::checkSaveOk(QString filepath)
{
  if(QFile(filepath).exists() == false){
    return true;
  }
  if(Settings::getInstance().overwriteConfirm() == false){
    return true;
  }
  QMessageBox::StandardButton button =
      QMessageBox::question(
        nullptr, tr("Confirm"),
        tr("%1 is already exists.\nDo you want to replace it?").arg(filepath));
  return button == QMessageBox::Yes;
}

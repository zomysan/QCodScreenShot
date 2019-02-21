#include "screenshotsaver.h"

#include <qpixmap.h>
#include <QDesktopServices>
#include "settings.h"
#include "imageconverter.h"
#include <QMessageBox>

ScreenShotSaver::ScreenShotSaver()
{
}

void ScreenShotSaver::save(QPixmap pixmap, QPoint focusPoint)
{
  QString filepath = Settings::value(Settings::Path);
  QString filename = QDateTime::currentDateTime().toString(
        Settings::value(Settings::Filename));
  QString filetype = Settings::value(Settings::Filetype);

  filepath += "/";
  filepath += filename;
  filepath += "." + filetype;

  // confirm overwrite
  bool saveOk = checkSaveOk(filepath);

  if(saveOk == false){
    return;
  }

  // add arrow to image
  if(focusPoint.isNull() == false){
    pixmap = ImageConverter::addArrow(pixmap, focusPoint);
  }

  // make image alpha channel
  if(Settings::value(Settings::ForcePngAlpha)){
    if(filetype == "png"){
      pixmap = ImageConverter::convertToAlphaSecretly(pixmap);
    }
  }

  pixmap.save(filepath, filetype.toStdString().c_str(),
              Settings::value(Settings::Quality));

  // png quant
  if(Settings::value(Settings::AggressivePngCompress) == true){
    if(filetype == "png"){
      QString command = "./pngquant.exe";
      QStringList args;
      args << "--force" << "--output" << filepath << filepath;
      QProcess::execute(command, args);
    }
  }

  // show in explorer
  if(Settings::value(Settings::OpenDialog)){
    QDesktopServices::openUrl(
          QUrl(Settings::value(Settings::Path), QUrl::TolerantMode));
  }
}

bool ScreenShotSaver::checkSaveOk(QString filepath)
{
  if(QFile(filepath).exists() == false){
    return true;
  }
  if(Settings::value(Settings::OverwriteConfirm) == false){
    return true;
  }
  QMessageBox::StandardButton button =
      QMessageBox::question(
        nullptr, tr("Confirm"),
        tr("%1 is already exists.\nDo you want to replace it?").arg(filepath));
  return button == QMessageBox::Yes;
}

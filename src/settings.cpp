#include "settings.h"

Settings::StringKey Settings::Path = QString("path");
Settings::StringKey Settings::Language = QString("language");
Settings::StringKey Settings::Filetype = QString("filetype");
Settings::StringKey Settings::Filename = QString("filename");
Settings::RectKey Settings::Geometry = QString("geometry");
Settings::BoolKey Settings::OpenDialog = QString("openDialog");
Settings::BoolKey Settings::DrawArrow = QString("drawArrow");
Settings::BoolKey Settings::OverwriteConfirm = QString("overwriteConfirm");
Settings::BoolKey Settings::AggressivePngCompress = QString("aggressivePngCompress");
Settings::BoolKey Settings::ForcePngAlpha = QString("forcePngAlpha");
Settings::BoolKey Settings::StayOnTop = QString("stayOnTop");
Settings::IntKey Settings::DelaySecs = QString("delaySecs");
Settings::IntKey Settings::Quality = QString("quality");

QList<QString> Settings::Keys = QList<QString>()
    << Settings::Path
    << Settings::Language
    << Settings::Filetype
    << Settings::Filename
    << Settings::Geometry
    << Settings::OpenDialog
    << Settings::DrawArrow
    << Settings::OverwriteConfirm
    << Settings::AggressivePngCompress
    << Settings::ForcePngAlpha
    << Settings::StayOnTop
    << Settings::DelaySecs
    << Settings::Quality
       ;

Settings &Settings::getInstance()
{
  static Settings settings;
  return settings;
}

Settings::Settings(){
  readData();
}

void Settings::readData()
{
  // read data from .ini file
  QSettings settings("setting.ini", QSettings::IniFormat);
  settings.setIniCodec("UTF-8");

  foreach(QString key, Keys){
    data_.insert(key, settings.value("settings/" + key));
  }

}

void Settings::writeData()
{
  // write data to .ini file
  QSettings settings("setting.ini", QSettings::IniFormat);
  settings.setIniCodec("UTF-8");

  foreach(QString key, Keys){
    settings.setValue("settings/" + key, data_.value(key));
  }
}

Settings::~Settings(){
  writeData();
}

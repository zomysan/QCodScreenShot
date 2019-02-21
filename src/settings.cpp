#include "settings.h"

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

  filename_ = settings.value("settings/filename").toString();
  filetype_ = settings.value("settings/filetype").toString();
  path_ = settings.value("settings/path").toString();
  language_ = settings.value("settings/language").toString();
  geometry_ = settings.value("settings/geometry").toRect();
  openDialog_ = settings.value("settings/openDialog").toBool();
  drawArrow_ = settings.value("settings/drawArrow").toBool();
  overwriteConfirm_ = settings.value("settings/overwriteConfirm").toBool();
  aggressivePngCompress_ = settings.value("settings/aggressivePngCompress").toBool();
  forcePngAlpha_ = settings.value("settings/forcePngAlpha").toBool();
  stayOnTop_ = settings.value("settings/stayOnTop").toBool();
  delaySecs_ = settings.value("settings/delaySecs").toInt();
  quality_ = settings.value("settings/quality").toInt();
}

void Settings::writeData()
{
  // write data to .ini file
  QSettings settings("setting.ini", QSettings::IniFormat);
  settings.setIniCodec("UTF-8");

  settings.setValue("settings/filename", filename_);
  settings.setValue("settings/filetype", filetype_);
  settings.setValue("settings/path", path_);
  settings.setValue("settings/language", language_);
  settings.setValue("settings/geometry", geometry_);
  settings.setValue("settings/drawArrow", drawArrow_);
  settings.setValue("settings/overwriteConfirm", overwriteConfirm_);
  settings.setValue("settings/aggressivePngCompress", aggressivePngCompress_);
  settings.setValue("settings/forcePngAlpha", forcePngAlpha_);
  settings.setValue("settings/stayOnTop", stayOnTop_);
  settings.setValue("settings/delaySecs", delaySecs_);
  settings.setValue("settings/quality", quality_);
}

Settings::~Settings(){
  writeData();
}
